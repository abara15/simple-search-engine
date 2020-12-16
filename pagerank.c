#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Graph.h"
#include "readData.h"
#include "pagerank.h"

int main(int argc, char *argv[]) {
    
    // Make sure that the correct number of arguments are input.
    if (argc != 4) {
        fprintf(stdout, "Error: The input 'dampingFactor differenceInPRSum maxIterations' are required.\n");
        exit(1);
    }

    // Read through collection.txt and put different URLs into listOfURLs array
    char *listOfURLs[1000], string[1000];
    FILE *collectionFile = fopen("collection.txt", "r");
    for (int i = 0; fscanf(collectionFile, "%s", string) != EOF; i++) {
        listOfURLs[i] = malloc(strlen(string) + 1);
        strcpy(listOfURLs[i], string);
    }
    fclose(collectionFile);

    // Convert our args into their respective data types -> double, double, int.
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    // Get our graph from readData.c.
    Graph urlGraph = GetGraph();
    
    // N = number of urls in the collection
    int N = urlCount();

    // We need a float or else our ranks will appear as integers.
    double floatN = (double)N;

    // Create two arrays for our pageRanks
    double pageRank[N], backupRank[N];

    // For each url p(i) in the collection, set the PR to 1/N.
    for (int i = 0; i < urlCount(); i++) {
        pageRank[i] = 1/floatN;
        backupRank[i] = 1/floatN;
    }

    int iteration = 0;
    double diff = diffPR;

    while (iteration < maxIterations && diff >= diffPR) {

        // Loop is so we can calculate the pageRank for every vertex in the graph.
        for (int i = 0; i < N; i++) {
            double weightedSumPrevPR = 0;
            // This loop is to check which other nodes link to our i vertex, which we need to calculate i's pageRank according to the given algorithm.
            for (int j = 0; j < N; j++) {
                // Finds the sum we use to calculate pageRank if there is a link from out iterative element to our current vertex.
                if (isAdjacent(urlGraph, j, i) == true && i != j) {
                    // inlinks = total inlinks of curr page / sum of inlinks of reference pages
                    // outlinks = total outlinks of curr page / sum of outlinks of reference pages
                    weightedSumPrevPR = weightedSumPrevPR + (backupRank[j] * inLinks(urlGraph, j, i) * outLinks(urlGraph, j, i));
                }
            }
            // PR(p(i);t+1) = ((1-d)/N) + (d * sum)
            pageRank[i] = ((1-d)/floatN) + (d * weightedSumPrevPR);
        }

        // diff = sum(i=1..N; abs(PR(pi;t+1) - PR(pi;t)))
        for (int i = 0; i < N; i++) {
            diff += fabs(pageRank[i] - backupRank[i]);
        }

        // Update our backupRank array to account for the new elements of pageRank.
        for (int k = 0; k < N; k++) {
            backupRank[k] = pageRank[k];
        }

        iteration++;
    }

    // Put the number of outlinks for each vertex of the graph in an array.
    int outLinkArray[N];
    for (int i = 0; i < N; i++) {
        outLinkArray[i] = (int)linksOutOfVertex(urlGraph, i);
    }

    // Write out our data to pageRankList.txt, in order of descending page ranks.
    FILE *write = fopen("pagerankList.txt", "w");
    for (int i = 0; i < N; i++) {
        double largest = 0.0;
        int largestIndex = 0;
        // Loop through all the elements in pageRank, and store the largest value and that value's index in the array.
        for (int j = 0; j < N; j++) {
            if (pageRank[j] >= largest) {
                largest = pageRank[j];
                largestIndex = j;
            }
        }
        fprintf(write, "%s, %d, %.7f\n", listOfURLs[largestIndex], outLinkArray[largestIndex], largest);
        // We have output our largest, so set it to a negative number so it isn't output again.
        pageRank[largestIndex] = -1;
    }
    fclose(write);

    // Terminate program.
    return 0;
}


// Calculate Win.
double inLinks(Graph g, Vertex v, Vertex w) {
    // inlinks = total inlinks of curr page / sum of inlinks of reference pages
    return linksIntoVertex(g, w) / totalReferenceInlinks(g, v);
}

// Get the total inlinks of our current page.
double linksIntoVertex(Graph g, Vertex v) {
    double total = 0;
    int N = urlCount();
    for (int i = 0; i < N; i++) {
        // If there is a link from vertice i to vertice v, increment inlink total.
        // v != i eliminates the possibility of counting loops.
        if (isAdjacent(g, i, v) == true && v != i) {
            total++;
        }
    }
    return total;
}

// Find the sum of all the pages inlinking to v.
double totalReferenceInlinks(Graph g, Vertex v) {
    double total = 0;
    int N = urlCount();
    for (int i = 0; i < N; i++) {
        // If there is a link curr page's child to i, calculate the total inlinks for all reference pages.
        // v != i eliminates the possibility of counting loops.
        if (isAdjacent(g, v, i) == true && v != i) {
            total += linksIntoVertex(g, i);
        }
    }
    return total;
}


// Calulate Wout.
double outLinks(Graph g, Vertex v, Vertex w) {
    // outlinks = total outlinks of curr page / sum of outlinks of reference pages.
    return linksOutOfVertex(g, w) / totalReferenceOutlinks(g, v);
}

// Get the total inlinks of our current page.
double linksOutOfVertex(Graph g, Vertex v) {
    double total = 0;
    int N = urlCount();
    for (int i = 0; i < N; i++) {
        // If there is a link from vertice i to vertice v, increment inlink total.
        // v != i eliminates the possibility of counting loops.
        if (isAdjacent(g, v, i) == true && v != i) {
            total++;
        }
    }

    // We redefine total if necessary to prevent division by zero errors.
    if (total == 0) {
        total = 0.5;
    }
    return total;
}

// Find the sum of all the pages which v links to.
double totalReferenceOutlinks(Graph g, Vertex v) {
    double total = 0;
    int N = urlCount();
    for (int i = 0; i < N; i++) {
        // If there is a link curr page's child to i, calculate the total Outlinks for all reference pages.
        // v != i eliminates the possibility of counting loops.
        if (isAdjacent(g, v, i) == true && v != i) {
            total += linksOutOfVertex(g, i);
        }
    }
    return total;
}