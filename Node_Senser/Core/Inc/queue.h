/*
 * queue.h
 *
 *  Created on: Mar 28, 2023
 *      Author: DELL
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef uint8_t *item ;

struct Node
{
    item Data;
    struct Node * Next;
};

typedef struct
{
	struct 	Node * Front, *Rear; //Node dau va Node cuoi
    uint8_t  cnt;
}Queue_HandleTypedef;

void initQueue(Queue_HandleTypedef *queue);
bool isEmpty(Queue_HandleTypedef *queue);
void pushQueue(Queue_HandleTypedef *queue,item x);
uint8_t popQueue(Queue_HandleTypedef *queue,item buffer);

#endif /* INC_QUEUE_H_ */
