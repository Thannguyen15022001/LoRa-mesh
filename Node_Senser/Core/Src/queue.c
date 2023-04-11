/*
 * queue.c
 *
 *  Created on: Mar 28, 2023
 *      Author: DELL
 */

#include "queue.h"




void initQueue(Queue_HandleTypedef *queue)
{
	queue->Front = queue->Rear = NULL ;
	queue->cnt = 0;
}

bool isEmpty(Queue_HandleTypedef *queue)
{
	if(queue->cnt == 0){
		return true ;
	}else {
		return false ;
	}
}

void pushQueue(Queue_HandleTypedef *queue,item x)
{
	struct Node *temp = (struct Node*)malloc(strlen((char*)x));
	temp->Data = x ;
	temp->Next = NULL;
	if(isEmpty(queue))
	{
		queue->Front=queue->Rear=temp;
	}else {
		queue->Rear->Next = temp;
		queue->Rear = temp;
	}
	queue->cnt ++;
}

uint8_t popQueue(Queue_HandleTypedef *queue,item buffer)
{
	if(isEmpty(queue))
	{
		return 0;
	}else {
		strncpy((char*)buffer,(char*)queue->Front->Data,strlen((char*)queue->Front->Data));
		if(queue->cnt==1){
			free(queue->Front);
			initQueue(queue);
		}else {
			free(queue->Front);
			queue->Front = queue->Front->Next;
			queue->cnt --;
		}


	}
	return 1;
}












