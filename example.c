#include <stdio.h>
#include <stdlib.h>
#include "cQueue.h" 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char *argv[]) {

	int i,j;
	int *pmsg;
	char perr;
	cQueue_t *pq;
	int *prx;
	
	
	pq = cQcreate(110);
	
     	/* cQPost ...*/		
	for(i = 0; i < 100; i++){
		pmsg = (int *)malloc(10*sizeof(int));
		for(j = 0; j < 10; j++){
			pmsg[j] = i*10 + j;
		}
		cQPost(pq, (void *)pmsg);
	}
	
	/* cQPostFront...*/
	pmsg = (int *)malloc(10*sizeof(int));
	for(j = 0; j < 10; j++){
		pmsg[j] = 1000 + j;
	}
	cQPostFront(pq, (void *)pmsg);
	
	/* cQRcv...*/
	for(j = 0; j < 101; j++){
		prx = (int *)cQRcv(pq, &perr);
		printf("prx%3d:", j);
		for(i = 0; i < 10; i++){
			printf("<%4d>", prx[i]);
		}
		printf("\n");
	}
	
	
	cQDelete(pq);

	return 0;
}

