#include "tree.h"
#ifdef BINARY_TREE
// C
#include <stdlib.h>
#include <stdio.h>
// Local
#include "binary-tree.h"

extern int comp;

Node* new_tree() {
    return NULL;
}

Node* new_node(Data data) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "%s %s:%d: could not create binary tree\n", __FILE__, __func__, __LINE__);
        return NULL;
    }
    // if there is enough memory available
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    //printf("%s %s:%d: node created successfully\n", __FILE__, __func__, __LINE__);
    return node;
}

Node* insert(Node *tree, Data data) {
    if (tree == NULL) {
        //printf("%s %s:%d: insert on empty tree\n", __FILE__, __func__, __LINE__);
        //printf("%s %s:%d: creating new tree to keep going\n", __FILE__, __func__, __LINE__);
        return new_node(data);
    }

    const int position = strcmp(data.word, tree->data.word);
    // negative: data.word is lexicographically smaller than tree->data.word
    // zero: the strings are equal
    // positive: data.word is lexicographically bigger than tree->data.word
    if (position < 0) {
        tree->left = insert(tree->left, data);
    } else if (position > 0) {
        tree->right = insert(tree->right, data);
    }
    return tree;
}

Node* search(Node* tree, char* str) {
    if (tree == NULL) {
        //printf("%s:%d: not found\n", __func__, __LINE__);
        return NULL;
    }

    const int position = strcmp(str, tree->data.word);
    if (position == 0) {
        //printf("\033[33m found! \033[0m");
        comp++;
        return tree;
    } else if (position < 0) {
        comp++;
        return search(tree->left, str);
    } else {
        comp++;
        return search(tree->right, str);
    }
}

#endif // binary_tree