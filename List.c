// IntList.c - Lists of integers
// Written by John Shepherd, July 2008
// Taken from course material and adapted to fit my program.

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "List.h"

/** Create a new, empty IntList. */
List newList (void)
{
	struct ListRep *L = malloc (sizeof(struct ListRep));
	if (L == NULL) err (EX_OSERR, "couldn't allocate List");
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

/** Release all resources associated with an IntList. */
void freeList (List L)
{
	if (L == NULL) return;

	for (struct ListNode *curr = L->first; curr != NULL; curr = curr->next) {
		struct ListNode *temp = curr;
		free (temp);
	}

	free (L);
}

/** create a new ListNode with value v
 * (this function is local to this ADT) */
static struct ListNode *newListNode (char *word, int v)
{
	struct ListNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate IntList node");
	n->word = malloc(strlen(word) + 1);
	strcpy(n->word, word);
	n->data = v;
	n->count = 1;
	n->rank = 0;
	n->next = NULL;
	return n;
}

/** Apppend one integer to the end of an IntList. */
void ListInsert (List L, int v, char *word)
{
	assert (L != NULL);

	struct ListNode *n = newListNode (word, v);
	if (L->first == NULL)
		L->first = L->last = n;
	else {
		L->last->next = n;
		L->last = n;
	}
	L->size++;
}

/** Delete first occurrence of `v` from an IntList.
 * If `v` does not occur in IntList, no effect */
void ListDelete (List L, char *word)
{
	assert (L != NULL);

	// find where v occurs in list
	struct ListNode *prev = NULL;
	struct ListNode *curr = L->first;
	while (curr != NULL && curr->word != word) {
		prev = curr;
		curr = curr->next;
	}

	// not found; give up
	if (curr == NULL)
		return;

	// unlink curr
	if (prev == NULL)
		L->first = curr->next;
	else
		prev->next = curr->next;
	if (L->last == curr)
		L->last = prev;
	L->size--;

	// drop curr
	free (curr);
}

/** Return number of elements in an IntList. */
int ListLength (List L)
{
	assert (L != NULL);
	return L->size;
}

/** Make a copy of an IntList.
 * New list should look identical to the original list. */
List ListCopy (List L)
{
	assert (L != NULL);
	struct ListRep *Lnew = newList ();
	for (struct ListNode *curr = L->first;
		 curr != NULL; curr = curr->next)
		ListInsert (Lnew, curr->data, curr->word);
	return Lnew;
}

/** Check whether an IntList is sorted in ascending order.
 * Returns `false` if list is not sorted, `true` if it is. */
bool ListIsSorted (List L)
{
	assert (L != NULL);

	// trivial cases, 0 or 1 items
	if (L->size < 2)
		return true;

	// scan list, looking for out-of-order pair
	for (struct ListNode *curr = L->first;
		 curr->next != NULL; curr = curr->next)
		if (curr->next->data < curr->data)
			return false;

	// nothing out-of-order, must be sorted
	return true;
}

/** Check internal consistency of an IntList. */
bool ListOK (List L)
{
	if (L == NULL)
		return true;

	if (L->size == 0)
		return (L->first == NULL && L->last == NULL);

	// scan to (but not past) last node
	struct ListNode *p = L->first;
	int count = 1; // at least one node
	while (p->next != NULL) {
		count++;
		p = p->next;
	}

	return (count == L->size && p == L->last);
}

/** Display an IntList as one integer per line to a file.
 * Assume that the file is open for writing. */
void ListPrint (FILE *outf, List L)
{
	assert (L != NULL);
	int count = 0;
	for (struct ListNode *curr = L->first;
		curr != NULL; curr = curr->next)
		// This is so we only print the top 30 pages.
		if (count < 30) {
			fprintf (outf, "%s\n", curr->word);
			count++;
		}
}

// Return 0 if word is already in List, else return 1.
int inList(List L, char *word) {
	struct ListNode *curr = L->first;
	for (; curr != NULL; curr = curr->next) {
		// If the word is already in L, return 0.
		if (strcmp(word, curr->word) == 0) { 
			curr->count += 1;
			return 0;
		}
	}
	return 1;
}