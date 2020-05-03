#include <stdlib.h>
#include <ctype.h>
#include "cQueue.h"


/*
 * Description  :   create and init the queue.
 *
 * @para[in]    :   start   is a pointer to the base address of the message queue 
 *                          storage area,the stroage area MUST be declare as an array
 *                          of pointers to 'void' as follows
 * 
 *                          void *messageStroage[size]
 *                            
 * @para[in]    :   size    is the number of elements in the storage area
 * 
 * @return      :   the pointer to the new queue
 */
cQueue_t *cQcreate(int size)
{
    cQueue_t *pq = NULL;
    pq = (cQueue_t *)malloc(sizeof(cQueue_t));
    if(pq != NULL){             /*      Initialize the queue    */
        pq->QMemory = (void **)malloc(size*sizeof(void *));
        pq->QStart      = pq->QMemory;
        pq->QEnd        = &pq->QMemory[size];
        pq->QIn         = pq->QMemory;
        pq->QOut        = pq->QMemory;
        pq->QSize       = size;
        pq->QEntries    = 0;
    }
    return pq;
}

/*
 * Description  :   delete the queue, and free the stroage area
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @return      :   NULL
 */
void cQDelete(cQueue_t *pq)
{
	free(pq->QMemory);
    free(pq);
}

/*
 * Description  :   flush the queue, the queue is like the new create state
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @return      :   NULL
 */
void cQFlush(cQueue_t *pq)
{
    pq->QIn = pq->QStart;
    pq->QOut = pq->QStart;
    pq->QEntries = 0;
}


/*
 * Description  :   receive msg from queue, if queue is empty,return NULL
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @para[out]   :   perr    is the pointer to error return
 * 
 * @return      : the pointer to the receive msg.
 */
void *cQRcv(cQueue_t *pq, char *perr)
{
    void *pmsg = NULL;
    
    if(pq->QEntries > 0){                   /* See if any messages in the queue                   */
    	pmsg = *pq->QOut++;                  /* Yes, extract oldest message from the queue         */
        pq->QEntries--;                     /* Update the number of entries in the queue          */
        if(pq->QOut == pq->QEnd){           /* Wrap OUT pointer if we are at the end of the queue */
            pq->QOut = pq->QStart;
        }    
        *perr = ERR_Q_NONE;
    }else{
        *perr = ERR_Q_EMPTY;                /* Queue is empty                                     */
    }

    return (pmsg);
}

/*
 * Description  :   send a message to the queue
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @para[in]    :   pmsg    is the pointer to new message to send
 * 
 * @return      :   ERR_Q_NONE      The call was successful and the message was sent
 *                  ERR_Q_FULL      If the queue cannot accept any more messages because it is full.
 */
int cQPost(cQueue_t *pq, void *pmsg)
{
    if(pq->QEntries >= pq->QSize){		/* Make sure queue is not full                   */
        return ERR_Q_FULL;
    }
	
    *pq->QIn++ = pmsg;
    
	pq->QEntries++;
 
    if(pq->QIn == pq->QEnd){
        pq->QIn = pq->QStart;
    }
   
    return ERR_Q_NONE;
}

/*
 * Description  :   send a message to the queue,the message is posted at the FRONT instead of
 *                  the end of the queue. Using cQPostFront() alllows you to send 'priority'
 *                  message.
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @para[in]    :   pmsg    is the pointer to new message to send
 * 
 * @return      :   ERR_Q_NONE      The call was successful and the message was sent
 *                  ERR_Q_FULL      If the queue cannot accept any more messages because it is full.
 */
int cQPostFront(cQueue_t *pq, void *pmsg)
{	
    if(pq->QEntries >= pq->QSize){      /* Make sure queue is not full                   */
        return ERR_Q_FULL;
    }

    if(pq->QOut == pq->QStart){         /* Wrap OUT ptr if we are at the 1st queue entry */
        pq->QOut = pq->QEnd;
    }

    pq->QOut--;                         
    *pq->QOut = pmsg;                   /* Insert message into queue                     */
    pq->QEntries++;                     /* Update the nbr of entries in the queue        */
    return ERR_Q_NONE;
}
