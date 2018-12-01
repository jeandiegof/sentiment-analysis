// C
#include <stdio.h>
// Local
#include "arguments.h"
#include "parser.h"
#include "binary-tree.h"

int main(int argc, char** argv) {
    if (!is_argc_valid(argc)) {
        fprintf(stderr, "Invalid usage!\n");
        fprintf(stderr, " Usage: %s lexical.txt sentences.txt output.txt", argv[0]);
    }

    FILE *lexicon = NULL;
    FILE *sentences = NULL;

    Status status = handle_files(&lexicon, &sentences, argv);
    if (status != OK) {
        return status;
    }

    handle_words(&sentences);

    Data data;
    strcpy(data.word, "teste");
    data.value = -1;
    Node* tree = new_tree();
    tree = insert(tree, data);

    Data data2 = {"abacate", 0};
    Data data3 = {"white", 0};


    tree = insert(tree, data3);
    tree = insert(tree, data2);
    //printf("On the left: %s\n", tree->left->data.word);
    //printf("On the right: %s\n", tree->right->data.word);

    handle_lexicon(&lexicon, &tree);
    return 0;
}