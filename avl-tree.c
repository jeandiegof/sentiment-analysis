// C
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Local
#include "avl-tree.h"

extern int comp;

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
    Node* tmp = (Node*) malloc(sizeof(Node));

    tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->height = 1 + (get_height(node->left) > get_height(node->right)) ? \
                                    get_height(node->left) : get_height(node->right);

    tmp->height = 1 + (get_height(tmp->right) > node->height) ? \
                                    get_height(tmp->right) : node->height;

    return tmp;
}

static Node* left_rotate(Node *node) {
    Node *tmp = (Node*) malloc(sizeof(Node));

    tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->height = 1 + (get_height(node->left) > get_height(node->right)) ? \
                                    get_height(node->left) : get_height(node->right);

    tmp->height = 1 + (get_height(tmp->left) > node->height) ? \
                                    get_height(tmp->left) : node->height;

    return tmp;
}

static Node* double_right_rotate(Node *node) {
    node->right = left_rotate(node->right);
    return right_rotate(node);
}

static Node* double_left_rotate(Node *node) {
    node->left = right_rotate(node->left);
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
    printf("Inserting node!\n");
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
    }

    const int left_height = get_height(tree->left);
    const int right_height = get_height(tree->right);
    tree->height = 1 + (left_height > right_height) ? left_height : right_height;

    const int balance = get_balance(tree);

    if (balance == 0) {
        return tree;
    }

    // the balance is positive and the balance of the left subtree is also positive:
    //  right rotation
    if (balance > 0 && get_balance(tree->left) > 0) {
        tree->right = insert(tree->right, data);
        return right_rotate(tree);
    }
    // the balance is negative and the balance of the right subtree is also negative:
    // left rotation
    if (balance < 0 && get_balance(tree->right) < 0) {
        tree->left = insert(tree->left, data);
        return left_rotate(tree);
    }

    // the balance is positive and the balance of the left subtree is negative:
    // double right rotation
    if (balance > 0 && get_balance(tree->left) < 0) {
        tree->right = insert(tree->right, data);
        return double_right_rotate(tree);
    }

    // the balance is negative and the balance of the right subtree is positive:
    // double left rotation
    if (balance < 0 && get_balance(tree->right) > 0) {
        tree->left = insert(tree->left, data);
        return double_right_rotate(tree);
    }
}

Node* search(Node* tree, char* str) {
    if (tree == NULL) {
        printf("%s:%d: not found\n", __func__, __LINE__);
        return NULL;
    }

    const int position = strcmp(str, tree->data.word);
    if (position == 0) {
        printf("\033[33m found! \033[0m");
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
