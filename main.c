// C
#include <stdio.h>
// Local
#include "arguments.h"
#include "parser.h"
#include "tree.h"

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
    // search for the words in the tree
    handle_sentences(&sentences, &output, &tree2);
    // prints the number of compares
    printf("Ok! Output file %s generated successfully.", get_filename(OUTPUT, argv));
    printf("\nComparisons: %d", comp);
    printf("\n");
    return 0;
}