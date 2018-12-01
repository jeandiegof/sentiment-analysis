// C
#include <stdio.h>
// Local
#include "arguments.h"
#include "parser.h"

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


    return 0;
}