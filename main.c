// C
#include <stdio.h>
// Local
#include "arguments.h"
#include "parser.h"
#include "binary-tree.h"
#include "avl-tree.h"

int comp = 0;

int main(int argc, char** argv) {
    if (!is_argc_valid(argc)) {
        fprintf(stderr, "Invalid usage!\n");
        fprintf(stderr, " Usage: %s lexical.txt sentences.txt output.txt", argv[0]);
    }

    FILE *lexicon = NULL;
    FILE *sentences = NULL;
    FILE *output = NULL;

    Status status = handle_files(&lexicon, &sentences, &output, argv);
    if (status != OK) {
        return status;
    }

    Node *tree2 = new_tree();
    // full fill the tree
    handle_lexicon(&lexicon, &tree2);

    printf("FINDME %s | ", tree2->data.word);

    // search for the words in the tree
    handle_sentences(&sentences, &output, &tree2);
    // prints the number of compares
    printf("%d", comp);
    return 0;
}