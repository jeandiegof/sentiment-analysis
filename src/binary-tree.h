#ifndef SENTIMENT_ANALYSIS_BINARY_TREE_H
#define SENTIMENT_ANALYSIS_BINARY_TREE_H

// Local
#include "files.h"  // provides an struct for error naming

#define MAXIMUM_WORD_SIZE   100

typedef struct {
    char word[MAXIMUM_WORD_SIZE];
    int value;
} Data;

typedef struct Node {
    Data data;
    struct Node *left;
    struct Node *right;
} Node;

Node* new_node(Data data);
Node* new_tree();
Node* insert(Node *tree, Data data);
Node* search(Node* tree, char* str);

#endif //SENTIMENT_ANALYSIS_BINARY_TREE_H
