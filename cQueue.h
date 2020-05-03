#ifndef cQUEUE_H
#define cQUEUE_H


#ifdef __cplusplus
extern "C"
{
#endif

#define cQueue_API_DECL extern

/*------------------------------------------------------------------------------------------------*/
typedef struct cQueue{          /* Queue control block  */    
    void            **QMemory;  /* pointer to message queue storage area                          */                                   
    void            **QStart;   /* pointer to start of queue data                                 */
    void            **QEnd;     /* pointer to end   of queue data                                 */
    void            **QIn;      /* pointer to where next message will be inserted in the queue    */
    void            **QOut;     /* pointer to where next message will be extracted from the queue */
    int             QSize;      /* size of queue -- max number of entries                         */
    int             QEntries;   /* current number of entries in the queue                         */
} cQueue_t;

#define ERR_Q_NONE      0
#define ERR_Q_FULL      1
#define ERR_Q_EMPTY     2

cQueue_API_DECL cQueue_t *cQcreate(int size);
cQueue_API_DECL void cQDelete(cQueue_t *pq);
cQueue_API_DECL void cQFlush(cQueue_t *pq);
cQueue_API_DECL void *cQRcv(cQueue_t *pq, char *perr);
cQueue_API_DECL int cQPost(cQueue_t *pq, void *pmsg);
cQueue_API_DECL int cQPostFront(cQueue_t *pq, void *pmsg);

/*--------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif
