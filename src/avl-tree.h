#ifndef SENTIMENT_ANALYSIS_AVL_TREE_H
#define SENTIMENT_ANALYSIS_AVL_TREE_H

#define MAXIMUM_WORD_SIZE   100

typedef struct {
    char word[MAXIMUM_WORD_SIZE];
    int value;
} Data;

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int height;
    Data data;
} Node;

Node* new_node(Data data);
Node* new_tree();
Node* insert(Node *tree, Data data);
Node* search(Node* tree, char* str);

#endif //SENTIMENT_ANALYSIS_AVL_TREE_H
