#ifndef SEARCHPAGERANK_H
#define SEARCHPAGERANK_H

#include <stdio.h>
#include "List.h"

// Add any of the files which any of the search terms appear in into the linked list.
void frequency (char **words, List l, int size);

// Add the PageRanks for each URL into the linked list.
void getPR (List l);

// Remove any commas of new line characters from string - adapted from AssignmentOne.
char *normaliseWord(char *string);

// Bubble sort into descending order of count, and within that, descending order of rank.
void sortList(List l);

// Swap nodes of linked list.
void swap(Node x, Node y);


#endif