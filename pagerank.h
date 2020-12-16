#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdio.h>
#include "Graph.h"

// Calculate Win.
double inLinks(Graph g, Vertex v, Vertex w);

// Get the total inlinks of our current page.
double linksIntoVertex(Graph g, Vertex v);

// Find the sum of all the pages inlinking to v.
double totalReferenceInlinks(Graph g, Vertex v);

// Calculate Wout.
double outLinks(Graph g, Vertex v, Vertex w);

// Get the total inlinks of our current page.
double linksOutOfVertex(Graph g, Vertex v);

// Find the sum of all the pages which v links to.
double totalReferenceOutlinks(Graph g, Vertex v);

#endif