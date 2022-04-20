# Simple Search Engine(s)

## Introduction
This simple search engine uses a simplified version of the well-known algorithm (Weighted) PageRank.

We will build a graph structure and calculate Weighted PageRanks, and rank pages based on these values. This will be done using a collection of "web pages" in an easy to use format. Each page has two sections:
* Section-1 contains URLs representing outgoing links. URLs are separated by one or more blanks, across multiple lines.
* Section-2 contains selected words extracted from the URL. Words are separated by one or more spaces, spread across multiple lines.

Here is an example of one of these files:
```
// Example file url31.txt

#start Section-1

url2  url34  url1 url26
url52 url21
url74  url6 url82

#end Section-1

#start Section-2

Mars has long been the subject of human interest. Early telescopic observations
revealed color changes on the surface that were attributed to seasonal vegetation
and apparent linear features were ascribed to intelligent design.

#end Section-2
```

## Summary
In Part-2: Search Engine : Graph structure-based search engine.

In Part-3: Rank Aggregation (Hybrid search engine), you need to combine multiple ranks (for example, PageRank and tf-idf
values) in order to rank pages.

Additional files: You can submit additional supporting files, *.cand *.h, for this assignment. For example, you may implement your graph adt in files graph.c and graph.h and submit these two files along with other required files as mentioned below.

## Graph structure-based Search Engine
Here, we create a graph structure that represents a hyperlink structure of given collection of "web pages" and for each page (node in your graph) calculate Weighted PageRank and other graph properties.

### Calculate Weighted PageRanks
In the file ```pagerank.c```, we read data from a given collection of pages in the file ```collection.txt``` and builds a graph structure using Adjacency Matrix or List Representation. Using the algorithm described below, we calculate Weighted PageRank for every URL in the file ```collection.txt```. In this file, URLs are separated by one or more spaces or/and new line character. Add suffix ```.txt``` to a URL to obtain file name of the corresponding "web page". For example, file url24.txt contains the required information for url24.
```
// Example file collection.txt

url25   url31 url2
   url102   url78
url32  url98 url33
```

Here is the simplified version of the Weighted PageRank Algorithm we will implement:
```
**PageRankW(d, diffPR, maxIterations)**
    Read "web pages" from the collection in file "collection.txt"
    and build a graph structure using Adjacency List or Matrix Representation
    
    N = number of urls in the collection For each url pi in the collection
    
    For each url p_i in the collection
          PR(p_i;0) = 1/N
    End For
    
    iteration = 0;
    diff = diffPR;   // to enter the following loop
    
    While (iteration < maxIteration AND diff >= diffPR)
          For each url p_i in the collection
                PR(p_i;t+1) = (1-d)/N + d * sum(p_j ∈ M(p_i), PR(p_j;t) * WIn_(p_j,p_i) * WOut(p_j,p_i))
          End For
          diff = sum(i=1..N, Abs(PR(p_i;t+1) - PR(p_i;t)))
          iteration++
     End While
```

```
Where:
 - M(p_i_ is a set containing nodes (urls) with outgoing links to p_i (ignore self-loops and parallel edges).
 - WIn_(p_j,p_i) and WOut(p_j,p_i) are defined above (see "Weighted PageRank").
 - t and (t+1) orrespond to values of "iteration".

Note,
 - For calculating WOut(p_j,p_i), if a node k has zero out degree (zero outlink), O_k should be 0.5 (and not 0). THis will avoid the issues related to division by 0.
```

```pagerank.c``` takes three arguments (```d``` - damping factor, ```diffPR``` - difference in PageRank sum, ```maxIterations``` - maximum iterations) and using the algorithm described in this section, calculates the Weighted PageRank for every URL.

For example,
```
% ./pagerank 0.85  0.00001  1000
```

This program outputs a list of URLs in descending order of Weighted PageRank values (use format string "%.7f") to a file named ```pagerankList.txt```. The list should also include degrees (number of out going links) for each url, along with its Weighted PageRank value. The values in the list should be comma separated. For example, ```pagerankList.txt``` may contain the following:
```
url31, 3, 0.2623546
url21, 1, 0.1843112
url34, 6, 0.1576851
url22, 4, 0.1520093
url32, 6, 0.0925755
url23, 4, 0.0776758
url11, 3, 0.0733884
```

## Search Engine
Using data available in ```invertedIndex.txt``` and ```pagerankList.txt```, our program will derive result from them.

```invertedIndex.txt``` contains one line per word, words are alphabetically ordered, using ascending order. Each list of URLs (for a single word) are alphabetically ordered, using ascending order.

We will read the file ```invertedIndex.txt``` line by line, assuming a max. line length of 1,000 chars, and will then tokenise words.

We will assume that there will be no duplicates for search terms, so "mars mars" is not possible.
```
// Example file invertedIndex.txt

design  url2 url25 url31
mars  url101 url25 url31
vegetation  url31 url61
```

In ```searchPagerank.c```, we will write a simple search engine that given search terms (words) as command-line arguments, finds pages with one or more search terms and outputs (to stdout) top 30 pages in descending order of number of search terms found and then within each group, descending order of Weighted PageRank. If number of matches are less than 30, we output all of them.

Example:
```
% ./searchPagerank  mars  design
url31
url25
url2
url101
```

## Hybrid/Meta Search Engine using Rank Aggregation
Here, we combine search results (ranks) from multiple sources using the "Scaled Footrule Rank Aggregation" method, described below.

Let ```T1``` and ```T2``` be search results (ranks) obtained using two different criteria. Note that we could use any suitable criteria, including manually generated rank lists.

A weighted bipartite graph for scaled footrule optimization ```(C,P,W)``` is defined as,
* ```C``` = set of nodes to be ranked (say a union of ```T1``` and ```T2```)
* ```P``` = set of positions available (say ```{1, 2, 3, 4, 5}```)
* ```W(c,p)``` is the scaled-footrule distance (from ```T1``` and ```T2```) of a ranking that places element ```'c'``` at position ```'p'```, given by ```W(c,p) = sum(i=1..k, |ø_i(c)/|ø_i|-p/n|```, where:
 * ```n``` is the cardinality (size) of ```C```,
 * ```|T1|``` is the cardinality (size) of ```T1```,
 * ```|T2|``` is the cardinality (size) of ```T2```,
 * ```T1(x3)``` is the position of ```x3``` in ```T1```,
 * ```k``` is number of rank lists.

The final ranking is derived by finding possible values of position ```'P'``` such that the scaled-footrule distance is minimum. There are many different ways to assign possible values for ```'P'```. In the above example ```P = [1, 3, 2, 5, 4]```. Some other possible values are, ```P = [1, 2, 4, 3, 5], P = [5, 2, 1, 4, 3], P = [1, 2, 3, 4, 5], etc```. For ```n = 5```, possible alternatives are ```5!``` For ```n = 10```, possible alternatives would be ```10!``` that is ```3,628,800``` alternatives. A very simple and obviously inefficient approach could use brute-force search and generate all possible alternatives, calculate scaled-footrule distance for each alternative, and find the alternative with minimum scaled-footrule distance.

Write a program ```scaledFootrule.c``` that aggregates ranks from files given as commandline arguments, and output aggregated rank list with minimum scaled footrule distance.
```
// Example, file rankA.txt

url1
url3
url5
url4
url2
```

```
// Example, file rankD.txt

url3
url2
url1
url4
```

The following command will read ranks from files "rankA.txt" and "rankD.txt" and outputs minimum scaled footrule distance (using format %.6f) on the first line, followed by the corresponding aggregated rank list.
```
% ./scaledFootrule   rankA.txt  rankD.txt
```

For the above example, there are two possible answers, with minimum distance of ```1.400000```.

Two possible values of ```P``` with minimum distance are:
```
C = [url1, url2, url3, url4, url5]
P = [1, 4, 2, 5, 3] and
P = [1, 5, 2, 4, 3]
```

By the way, we need to select any one of the possible values of ```P``` that has minium distance, so there could be multiple possible answers. Note that we need to output only one such list.

One possible answer for the above example, for ```P = [1, 4, 2, 5, 3]```:
```
1.400000
url1
url3
url5
url2
url4
```

Another possible answer for the above example, ```P = [1, 5, 2, 4, 3]```:
```
1.400000
url1
url3
url5
url4
url2
```

This program also handles multiple rank files, for example:
```
% ./scaledFootrule   rankA.txt  rankD.txt  newSearchRank.txt  myRank.txt
```
