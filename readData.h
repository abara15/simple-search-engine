#ifndef READDATA_H
#define READDATA_H

#include <stdio.h>
#include "Graph.h"

// Builds a directed graph of URLs.
Graph GetGraph(void);

// Returns the number of URLs in collection.txt.
int urlCount();

// Checks if the scanned word is a URL.
bool isLink(char *string, char **array);

// Returns the position which we will use for our insertion.
int outlinkPosition(int length, char *string, char **array);

// Made my own strdup function.
char *strdup(const char *str);

#endif
