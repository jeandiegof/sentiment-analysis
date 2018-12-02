#include "tree.h"
#ifdef AVL_TREE
// C
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Local
#include "avl-tree.h"

#define AVL_VERBOSE(f_, ...)  //printf(f_, ##__VA_ARGS__)

extern int comp;

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

static int get_height(Node* node) {
    if (node != NULL) {
        return node->height;
    }
    return 0;
}

static int get_balance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

static Node* right_rotate(Node *node) {
    AVL_VERBOSE("avl-tree:right_rotate\n");

    Node *new_node = node->left;
    Node *tmp = new_node->right;

    new_node->right = node;
    node->left = tmp;

    node->height = 1 + maximum(get_height(node->left), get_height(node->right));
    new_node->height = 1 + maximum(get_height(new_node->left), get_height(new_node->right));

    return new_node;
}

static Node* left_rotate(Node *node) {
    AVL_VERBOSE("avl-tree:right_rotate\n");

    Node *new_node = node->right;
    Node *tmp = new_node->left;

    new_node->left = node;
    node->right = tmp;

    node->height = 1 + maximum(get_height(node->left), \
                               get_height(node->right));

    new_node->height = 1 + maximum(get_height(new_node->left), \
                                   get_height(new_node->right));

    return new_node;
}

static Node* double_right_rotate(Node *node) {
    AVL_VERBOSE("avl-tree:double_right_rotate\n");
    node->left =  left_rotate(node->left);
    return right_rotate(node);
}

static Node* double_left_rotate(Node *node) {
    AVL_VERBOSE("avl-tree:double_left_rotate\n");
    node->right = right_rotate(node->right);
    return left_rotate(node);
}

Node* new_tree() {
    return NULL;
}

Node* new_node(Data data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "%s:%d: could not create binary tree\n", __func__, __LINE__);
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

Node* insert(Node *tree, Data data) {
    AVL_VERBOSE("Inserting node!\n");
    if (tree == NULL) {
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
    } else {
        return tree;
    }

    const int left_height = get_height(tree->left);
    const int right_height = get_height(tree->right);
    const int max = (left_height > right_height) ? left_height : right_height;
    tree->height = 1 + max;

    const int balance = get_balance(tree);
    AVL_VERBOSE("Max: %d Height: %d | Balance: %d\n", max, tree->height, balance);
    if (balance == 0) {
        return tree;
    }
    // the balance is positive and the balance of the left subtree is also positive:
    //  right rotation
    if (balance > 1 && get_balance(tree->left) > 0) {
        return right_rotate(tree);
    }
    // the balance is negative and the balance of the right subtree is also negative:
    // left rotation
    if (balance < -1 && get_balance(tree->right) < 0) {
        return left_rotate(tree);
    }
    // the balance is positive and the balance of the left subtree is negative:
    // double right rotation
    if (balance > 1 && get_balance(tree->left) < 0) {
        return double_right_rotate(tree);
    }
    // the balance is negative and the balance of the right subtree is positive:
    // double left rotation
    if (balance < -1 && get_balance(tree->right) > 0) {
        return double_left_rotate(tree);
    }
    return tree;
}

Node* search(Node* tree, char* str) {
    if (tree == NULL) {
        AVL_VERBOSE("%s:%d: not found\n", __func__, __LINE__);
        return NULL;
    }

    const int position = strcmp(str, tree->data.word);
    if (position == 0) {
        AVL_VERBOSE("\033[33m found! \033[0m");
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
#endif