#include "arguments.h"

uint8_t is_argc_valid(int argc) {
    return (uint8_t) (argc == 4);
}

char* get_filename(Files file, char** argv) {
    return argv[file];
}

Status handle_files(FILE** lexicon, FILE** sentences, char** argv) {
    *lexicon = fopen(get_filename(LEXICON, argv), "r");
    *sentences = fopen(get_filename(SENTENCES, argv), "r");

    if (*lexicon == NULL) {
        fprintf(stderr, "Error opening file %s", get_filename(LEXICON, argv));
        return ERROR_OPENING_LEXICON;
    } else if (*sentences == NULL) {
        fprintf(stderr, "Error opening file %s", get_filename(SENTENCES, argv));
        return ERROR_OPENING_SENTENCES;
    }
    return OK;
}

