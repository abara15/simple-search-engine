#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "List.h"
#include "searchPagerank.h"

int main(int argc, char *argv[]) {

    // Make sure the correct number of arguments are given.
    if (argc == 1) {
        fprintf(stderr, "Error: More arguments are required\n");
        exit(1);
    }

    char *searchWords[1000];
    List UrlList = newList();

    // Get the search words input into the command line and put them in an array.
    int counter = 0;
    for (int i = 0; i < argc - 1; i++) {
        searchWords[i] = malloc(strlen(argv[i + 1]) + 1);
        strcpy(searchWords[i], argv[i + 1]);
        counter++;
    }

    // Go through invertedIndex.txt, and add all the files any of the search terms appear in into UrlList.
    frequency(searchWords, UrlList, counter);

    // Go through pageRankList.txt, extract the PageRanks, and add it to its node in UrlList.
    getPR(UrlList);

    // Sort UrlList in descending order number of matches per page, and in descending order of PageRank.
    sortList(UrlList);

    // Print the list to stdout.
    ListPrint(stdout, UrlList);

    // Terminate program.
    return 0;
}



// Add any of the files which any of the search terms appear in into the linked list.
void frequency (char **words, List l, int size) {
    char index[100];
    char line[1000];

    // Open invertedIndex.txt
    for (int i = 0; words[i] != NULL; i++) {
        FILE *indexFile = fopen("invertedIndex.txt", "r");
        // Read through each word in invertedIndex.txt.
        while (fscanf(indexFile, "%s", index) != EOF) {
            // Checks if the word corresponds with a search word.
            if (strcmp(words[i], index) == 0) {
                // It does, so we get the whole line and use strtok to extract each URL.
                fgets(line, 1000, indexFile);
                char *token = strtok(line, " ");
                for (int j = i; token != NULL; j++) {
                    if (strcmp(token, "\n") == 0) { break ;}
                    // Checks if URL is already in list.
                    if (inList(l, token) == 1) {
                        // If not already in the list, insert the URL.
                        ListInsert(l, i, token);
                    }
                    token = strtok(NULL, " ");
                }                
            }
        }
        fclose(indexFile);
    }
}

// Add the PageRanks for each URL into the linked list.
void getPR (List l) {
    char fileName[1000];
    char line[1000];
    Node curr = l->first;

    // Loop through each node in the Linked List.
    for (; curr != NULL; curr = curr->next) {
        FILE *read = fopen("pagerankList.txt", "r");
        // Read every word in pagerankList.txt.
        while (fscanf(read, "%s", fileName) != EOF) {
            // Remove ',' from word and check if it compares to the word in the current node.
            if (strcmp(normaliseWord(fileName), curr->word) == 0) {
                // Read in the rest of the line.
                fgets(line, 1000, read);
                // Tokenise it twice to get the PageRank value.
                char *token = strtok(line, " ");
                token = strtok(NULL, " ");
                // Set the rank of the node to our token, in double form.
                curr->rank = atof(normaliseWord(token));              
            }
        }
        fclose(read);
    }
}

// Remove any commas of new line characters from string - adapted from AssignmentOne.
char *normaliseWord(char *string) {
    for (int current = 0; string[current] != '\0'; current++) {
        // Check if char is ',' or '\n'.
        if (string[current] == ',' || string[current] == '\n') {
            string[current] = '\0';
        }
    }
    // Return modified string.
    return string;
}

// Bubble sort into descending order of count, and within that, descending order of rank.
void sortList(List l) {
    Node i, j;
    // Loop through list and compare i to i->next.
    for (i = l->first; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // If i has a lower frequency than its next element, swap them (so it's descending).
            if (i->count < j->count) {
                swap(i, j);
            }
        }
    }

    // Loop through list and compare i to i->next.
    for (i = l->first; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // Make sure the words are not the same.
            if (strcmp(i->word, j->word) != 0) {
                // If i and j have the same frequency, but i has a lower PR than j, swap them (so it's descending).
                if (i->count == j->count && i->rank < j->rank) {
                    swap(i, j);
                }
            }
        }
    }
}

// Swap nodes of linked list.
void swap(Node x, Node y) {
    // Store each of the elements in our node into temp variables, and perform swap.
    char *tempWord = malloc(strlen(x->word) + 1);
    strcpy(tempWord, x->word);
    int tempData = x->data;
    int tempCount = x->count;
    double tempRank = x->rank;

    strcpy(x->word, y->word);
    x->data = y->data;
    x->count = y->count;
    x->rank = y->rank;

    strcpy(y->word, tempWord);
    y->data = tempData;
    y->count = tempCount;
    y->rank = tempRank;
}