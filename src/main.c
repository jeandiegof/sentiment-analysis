// C
#include <stdio.h>
#include <time.h>
// Local
#include "files.h"
#include "parser.h"
#include "tree.h"

int comp = 0;

int main(int argc, char** argv) {
    if (!is_argc_valid(argc)) {
        fprintf(stderr, "Invalid usage!\n");
        fprintf(stderr, " Usage: %s lexical.txt sentences.txt output.txt", argv[0]);
        return -1;
    }

    FILE *lexicon = NULL;
    FILE *sentences = NULL;
    FILE *output = NULL;

    Status status = handle_files(&lexicon, &sentences, &output, argv);
    if (status != OK) {
        return status;
    }
#ifdef AVL_TREE
    printf("Running with AVL tree\n");
#else
    printf("Running with Binary Tree\n");
#endif

    Node *tree2 = new_tree();

    // full fill the tree and calculate the time taken
    clock_t start = clock();
    handle_lexicon(&lexicon, &tree2);
    const double insert_time = (double) (clock() - start) / CLOCKS_PER_SEC;

    // search for the words in the tree
    handle_sentences(&sentences, &output, &tree2);

    // prints the number of compares
    printf("Ok! Output file %s generated successfully.", get_filename(OUTPUT, argv));
    printf("\nComparisons: %d", comp);
    printf("\nInsertion time: %f", insert_time);
    printf("\n");
    return 0;
}