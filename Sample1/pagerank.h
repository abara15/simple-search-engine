#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdio.h>

double *calculatePageRank(Graph urlGraph, double d, double diffPR, int maxIterations);

// Returns true if there is an edge between v1 and v2, false otherwise.
// int findPath(Graph g, Vertex v1, Vertex v2);
double calculateWIn(Graph g, Vertex v1, Vertex v2);
double calculateWOut(Graph g, Vertex v1, Vertex v2);
double sumW(Graph g, Vertex v);

// Writes out data to specified file.
void outputData(char *urls, double *pageRank);

#endif
