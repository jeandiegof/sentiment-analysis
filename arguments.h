#ifndef SENTIMENT_ANALYSIS_ARGUMENTS_H
#define SENTIMENT_ANALYSIS_ARGUMENTS_H

#include <stdint-gcc.h>

typedef enum {
    LEXICAL = 1,
    SENTENCES = 2,
    OUTPUT = 3
} Files;

uint8_t is_argc_valid(int argc) {
    return (uint8_t) (argc == 4);
}

char* get_filename(Files file, char** argv) {
    return argv[file];
}

#endif //SENTIMENT_ANALYSIS_ARGUMENTS_H
