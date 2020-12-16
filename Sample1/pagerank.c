#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Graph.h"
#include "readData.h"
#include "pagerank.h"

void outputGraph(Graph urlGraph);
double returnWIn(Graph urlGraph, Vertex i, Vertex j);
double inLinkCount(Graph urlGraph, Vertex v);
double inLinkSum(Graph urlGraph, Vertex v);
double returnWOut(Graph urlGraph, Vertex i, Vertex j);
double outLinkCount(Graph urlGraph, Vertex v);
double outLinkSum(Graph urlGraph, Vertex v);


int main(int argc, char *argv[]) {
    if (argc != 4) {
        // error message goes here!!!!
        exit(1);
    }

    // Convert our args to their respective data types -> double, double, int.
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    // Array declarations for building our URL array.
    char *list_of_urls[1000];
    char string[1000];

    // Store all of the filenames listed in collection.txt into an array.
    FILE *readFile = fopen("collection.txt", "r");
    for (int i = 0; fscanf(readFile, "%s", string) != EOF; i++) {
        list_of_urls[i] = malloc(strlen(string) + 1);
        strcpy(list_of_urls[i], string);
    }
    fclose(readFile);

    // Read "web pages" from the collection in file "collection.txt" and build a graph structure using Adjacency List or Matrix Representation.
    Graph urlGraph = GetGraph();

    // N = number of urls in the collection
    int N = urlCount();
    int NFloat = (double)N;
    double *pageRank = malloc(sizeof(double) * N);
    double pastRank[N];

    // For each url pi in the collection {PR = 1/N;} End For
    for (int i = 0; i < N; i++) {
        double newWeight = 1/NFloat;
        pageRank[i] = newWeight;
        // updateWeight(urlGraph, newWeight);
    }

    int iteration = 0;
    double diff = diffPR;

    while (iteration < maxIterations && diff >= diffPR) {

        // Update the pastRank with the new weight we have just found.
        for (int i = 0; i < N; i++) {
            pastRank[i] = pageRank[i];
        }

        for (int i = 0; i < N; i++) {
            double sum = 0;
            // Calculate sumof(pj in M(pi))[PR(pj;t)*Win(pj,pi)*Wout(pj,pi)] in this loop
            for (int j = 0; j < N; j++) {
                // if link between j and i, get sum
                if (isAdjacent(urlGraph, j, i) == 1) {
                    // sumof(pj in M(pi))[PR(pj;t)*Win(pj,pi)*Wout(pj,pi)]
                    sum = sum + (pastRank[j] * returnWIn(urlGraph, i, j) * returnWOut(urlGraph, i, j));
                }
            }
            // PR(pi;t+1) = ((1-d)/N) + d * sumof(pj in M(pi))[PR(pj;t)*Win(pj,pi)*Wout(pj,pi)] 
            pageRank[i] = ((1-d)/NFloat) + (d * sum);

            // diff = sum(i=1 -> N)[Abs(PR(pi;t+1) - PR(pi;t))]
            for (int j = 0; j < N; j++) {
                diff = diff + fabs(pageRank[j] - pastRank[j]);
            }

            iteration++;
        }

    }

    for (int i = 0; i < urlCount(); i++) {
        printf("%.7f\n", pageRank[i]);
    }

    // printURLS(urlGraph, list_of_urls);

    // While (iteration < maxIteration AND diff >= diffPR)
    //     For each url pi in the collection
    //         PR(pi;t+1) = ((1-d)/N) + d * sumof(pj in M(pi))[PR(pj;t)*Win(pj,pi)*Wout(pj,pi)] 
    //     End For
    //     diff = sum(i=1 -> N)[Abs(PR(pi;t+1) - PR(pi;t))]
    //     iteration++;
    // End While

    // Output the graph in descending order of weight
    outputGraph(urlGraph);


    // Delete graph because we have written data to file already.
    dropGraph(urlGraph);

    return 0;
}

double returnWIn(Graph urlGraph, Vertex i, Vertex j) {
    return inLinkCount(urlGraph, i) / inLinkSum(urlGraph, j);
}

double inLinkCount(Graph urlGraph, Vertex v) {
    double inLinks = 0;
    for (int i = 0; i < urlCount(); i++) {
        if (isAdjacent(urlGraph, i, v) == 1) { inLinks++; }
    }
    return inLinks;
}

double inLinkSum(Graph urlGraph, Vertex v) {
    double sum = 0;
    // If inlink, sum all the inlinks for the vertices.
    for (int i = 0; i < urlCount(); i++) {
        if (isAdjacent(urlGraph, v, i) == 1) { sum = sum + inLinkCount(urlGraph, v); }
    }
    return sum;
}

double returnWOut(Graph urlGraph, Vertex i, Vertex j) {
    return outLinkCount(urlGraph, i) / outLinkSum(urlGraph, j);
}

double outLinkCount(Graph urlGraph, Vertex v) {
    double inLinks = 0;
    for (int i = 0; i < urlCount(); i++) {
        if (isAdjacent(urlGraph, i, v) == 1) { inLinks++; }
    }
    return inLinks;
}

double outLinkSum(Graph urlGraph, Vertex v) {
    double sum = 0;
    // If inlink, sum all the inlinks for the vertices.
    for (int i = 0; i < urlCount(); i++) {
        if (isAdjacent(urlGraph, v, i) == 1) { sum = sum + outLinkCount(urlGraph, v); }
    }
    // To prevent division by zero error.
    if (sum == 0) { sum = 0.5; }
    return sum;
}







void outputGraph(Graph urlGraph) {
    char url;
    FILE *write = fopen("pagerankList.txt", "w");
    double topWeight = 0.0;

    for (int i = 0; i < urlCount(); i++) {
        double topWeight = 0.0;
        for (int j = 0; j < urlCount(); j++) {
            // if weight at page j is > topWeight, then set it to the top page and weight.
        }
    }
    fclose(write);
}