// Queue.h ... interface to Queue ADT
// Written by John Shepherd, March 2013
// Taken from course material - never changed but it was needed for Item.h.

#ifndef QUEUE_H
#define QUEUE_H

#include "Item.h"

typedef struct QueueRep *Queue;

Queue newQueue (void);			// create new empty queue
void dropQueue (Queue);			// free memory used by queue
void showQueue (Queue);			// display as 3 > 5 > 4 > ...
void QueueJoin (Queue, Item);	// add item on queue
Item QueueLeave (Queue);		// remove item from queue
int QueueIsEmpty (Queue);		// check for no items

#endif
