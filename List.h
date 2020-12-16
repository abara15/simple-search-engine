// IntList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008
// Taken from course material and adapted to fit my program.

#ifndef INTLIST_H
#define INTLIST_H

#include <stdbool.h>
#include <stdio.h>

/** External view of IntList ... implementation in IntList.c */
typedef struct ListRep *List;
typedef struct ListNode *Node;

// data structures representing IntList
struct ListNode {
	char *word;					// this will be the url
	int data;           		// 
	int count;					// this will count the number of times a url corresponds with a search word.
	double rank;				// will store the page rank for each url.
	struct ListNode *next;	    // pointer to node containing next element.
};

struct ListRep {
	int size;           		// number of elements in list
	struct ListNode *first;	    // node containing first value
	struct ListNode *last;	    // node containing last value
};

/** Create a new, empty IntList. */
List newList (void);

/** Release all resources associated with an IntList. */
void freeList (List);

/** Apppend one integer to the end of an IntList. */
void ListInsert (List, int, char*);

/** Delete first occurrence of `v` from an IntList.
 * If `v` does not occur in IntList, no effect. */
void ListDelete (List, char*);

/** Return number of elements in an IntList. */
int ListLength (List);

/** Make a copy of an IntList.
 * New list should look identical to the original list. */
List ListCopy (List);

/** Check whether an IntList is sorted in ascending order.
 * Returns `false` if list is not sorted, `true` if it is. */
bool ListIsSorted (List);

/** Check internal consistency of an IntList. */
bool ListOK (List);

// Prints out the words of the top 30 nodes in the linked list.
void ListPrint (FILE *, List);

// Return 0 if word is already in List, else return 1.
int inList(List L, char *word);

#endif
