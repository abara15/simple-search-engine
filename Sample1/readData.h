// readData.h function prototypes
#ifndef READDATA_H
#define READDATA_H

// Gets a list of the URLs in collection.txt, and builds a graph with all the URLs and their links
Graph GetGraph(void);

// Returns the number of URLs in collections.txt
int urlCount(void);

// Get the position of the outlink in the header of our file.
int outlinkPosition(int length, char *string, char **array);

// Checks if the string is a link to a page in our URL array.
bool isLink(char *string, char **array);

#endif
