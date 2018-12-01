#ifndef SENTIMENT_ANALYSIS_ARGUMENTS_H
#define SENTIMENT_ANALYSIS_ARGUMENTS_H

// C
#include <stdint-gcc.h>
#include <string.h>
#include <stdio.h>

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
    ERROR_STREAM_INVALID,
    OK
} Status;

uint8_t is_argc_valid(int argc);
char* get_filename(Files file, char** argv);

Status handle_files(FILE** lexicon, FILE** sentences, char** argv);

#endif //SENTIMENT_ANALYSIS_ARGUMENTS_H
