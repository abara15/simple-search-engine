#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Graph.h"
#include "readData.h"



// Gets a list of the URLs in collection.txt, and builds a graph with all the URLs and their links.
Graph GetGraph() {
    char *list_of_urls[1000];
    char string[1000];

    // Read through file and put the different URLs into an array of URLs.
    FILE *readFile = fopen("collection.txt", "r");
    for (int i = 0; fscanf(readFile, "%s", string) != EOF; i++) {
        list_of_urls[i] = malloc(strlen(string) + 1);
        strcpy(list_of_urls[i], string);
    }
    fclose(readFile);
    
    Graph urlGraph = newGraph(urlCount());
    char tempStr[1000];
    // Open each of the files in our array and put them into a graph
    for (int i = 0; list_of_urls[i] != NULL; i++) {
        char *urlStr = strcat(list_of_urls[i], ".txt");
        // Read through each file, get the links, get the position, and insert the edge into the graph.
        FILE *currFile = fopen(urlStr, "r");
        while (fscanf(currFile, "%s", tempStr) != EOF) {
            // If link, get position and inseert edge into graph.
            if (isLink(tempStr, list_of_urls) == true) {
                int position = outlinkPosition(urlCount(), tempStr, list_of_urls);
                insertEdge(urlGraph, i, position, 1);
            }
        }
        fclose(currFile);
    }
    showGraph(urlGraph, list_of_urls);
    return urlGraph;
}


// Returns the number of URLs in collections.txt
int urlCount(void) {
    FILE *readFile = fopen("collection.txt", "r");
    char string[1000];
    int i = 0;
    while (fscanf(readFile, "%s", string) != EOF) { i++; }
    fclose(readFile);
    return i;
}

// Checks if the string is a link to a page in our URL array.
bool isLink(char *string, char **array) {
    for (int i = 0; i < urlCount(); i++) {
        if (strcmp(string, array[i]) == 0) { return true; }
    }
    return false;
}

// Get the position of the outlink in the header of our file.
int outlinkPosition(int length, char *string, char **array) {
    int i = 0;
    for (; i < length; i++) {
        if (strcmp(string, array[i]) == 0) { return i; }
    }
    return i;
}
















































int main(int argc, char *argv[]) {
    // test();
    Graph g = GetGraph();
    return 0;
}