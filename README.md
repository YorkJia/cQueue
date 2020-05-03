# License
	MIT License,all the people can use it for free, and thanks for uC/OS.

# Usage
	cQueue is message queue, is written in ANSI C in order to support as many platforms and compilers as possible.
	
# Data Structure
	cQueue using the cQueue struct data type:
```C
/*---------------The cQueue structure ------------------------------------------------------------*/
typedef struct cQueue{          
    void            **QMemory;  /* pointer to message queue storage area                          */                                   
    void            **QStart;   /* pointer to start of queue data                                 */
    void            **QEnd;     /* pointer to end   of queue data                                 */
    void            **QIn;      /* pointer to where next message will be inserted in the queue    */
    void            **QOut;     /* pointer to where next message will be extracted from the queue */
    int             QSize;      /* size of queue -- max number of entries                         */
    int             QEntries;   /* current number of entries in the queue                         */
} cQueue_t;
```	
# API function
```C
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
cQueue_t *cQcreate(int size);

/*
 * Description  :   delete the queue, and free the stroage area
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @return      :   NULL
 */
void cQDelete(cQueue_t *pq);

/*
 * Description  :   flush the queue, the queue is like the new create state
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @return      :   NULL
 */
void cQFlush(cQueue_t *pq);

/*
 * Description  :   receive msg from queue, if queue is empty,return NULL
 *
 * @para[in]    :   pq      is the pointer to the queue
 *
 * @para[out]   :   perr    is the pointer to error return
 * 
 * @return      : the pointer to the receive msg.
 */
void *cQRcv(cQueue_t *pq, char *perr);

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
int cQPost(cQueue_t *pq, void *pmsg);
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
int cQPostFront(cQueue_t *pq, void *pmsg);
```
# Example
	the example.c show the cQueue'function.
	
# Attention
	because the type of element in the cQueue struct is (void ), so the message's type can be custom by youself.

