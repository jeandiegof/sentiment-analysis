#ifndef SENTIMENT_ANALYSIS_ARGUMENTS_H
#define SENTIMENT_ANALYSIS_ARGUMENTS_H

#include <stdint-gcc.h>
#include <string.h>

#define MAXIMUM_PATH_SIZE   30

typedef enum {
    LEXICON = 1,
    SENTENCES = 2,
    OUTPUT = 3
} Files;

typedef enum {
    ERROR_OPENING_LEXICON,
    ERROR_OPENING_SENTENCES,
    ERROR_CREATING_OUTPUT,
    OK,
} Status;

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
}

#endif //SENTIMENT_ANALYSIS_ARGUMENTS_H
