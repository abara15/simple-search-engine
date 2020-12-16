#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Graph.h"
#include "readData.h"

// Builds a directed graph of URLs.
Graph GetGraph(void) {
    char *listOfURLs[1000];
    char string[1000];
    int N = 0;

    // Read through file and put different URLs into listOfURLs array
    FILE *collection = fopen("collection.txt", "r");
    for (int i = 0; fscanf(collection, "%s", string) != EOF; i++) {
        listOfURLs[i] = malloc(strlen(string) + 1);
        strcpy(listOfURLs[i], string);
        N++;
    }
    fclose(collection);

    Graph urlGraph = newGraph(N);
    char tempString[1000];

    // Open up each file, determine if there are links in it, and then add it to the graph.
    for (int i = 0; i < N; i++) {
        // Insert the URL into a new string filename.
        char *filename = strdup(listOfURLs[i]);

        // We need to reallocate extra space to fit in the .txt at the end.
        filename = realloc(filename, strlen(listOfURLs[i]) + strlen(".txt") + 1);

        // Now we have extra space we can concatenate the .txt to the end of filename.
        strcat(filename, ".txt");

        // Read through each file, get link and position, and insert into graph
        FILE *currFile = fopen(filename, "r");        
        while (fscanf(currFile, "%s", tempString) != EOF) {
            // Check if the word we have scanned is a URL.
            if (isLink(tempString, listOfURLs) == true) {
                // It is, so get its position in the URL array.
                int position = outlinkPosition(N, tempString, listOfURLs);

                // Insert an edge between the current file and its outlink file.
                insertEdge(urlGraph, i, position, 1);
            }
        }
        fclose(currFile);
    }

    // Return the graph we have just built.
    return urlGraph;
}

// Returns the number of URLs in collection.txt.
int urlCount(void) {
    int i = 0;
    char string[1000];
    // Opens up the file, count each URL, and return the count.
    FILE *collection = fopen("collection.txt", "r");
    while (fscanf(collection, "%s", string) != EOF) {
        i++;
    }
    fclose(collection);
    return i;
}

// Checks if the scanned word is a URL.
bool isLink(char *string, char **array) {
    for (int i = 0; i < urlCount(); i++) {
        // Check if the string is in the URL array.
        if (strcmp(string, array[i]) == 0) { return true; }
    }
    return false;
}

// Returns the position which we will use for our insertion.
int outlinkPosition(int length, char *string, char **array) {
    int i = 0;
    for (; i < length; i++) {
        // If the string is in the URL array, return our position i.
        if (strcmp(string, array[i]) == 0) { return i; }
    }
    return i;
}

// Made my own strdup function.
char *strdup(const char *str) {
    char *dup = malloc(strlen(str) + 1);
    if (dup) {
        strcpy(dup, str);
    }
    return dup;
}