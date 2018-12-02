// Local
#include "arguments.h"

#define FILES_VERBOSE(f_, ...)     printf(f_, ##__VA_ARGS__)

uint8_t is_argc_valid(int argc) {
    return (uint8_t) (argc == 4);
}

char* get_filename(Files file, char** argv) {
    return argv[file];
}

Status handle_files(FILE** lexicon, FILE** sentences, FILE** output, char** argv) {
    *lexicon = fopen(get_filename(LEXICON, argv), "r");
    *sentences = fopen(get_filename(SENTENCES, argv), "r");

    if (*lexicon == NULL) {
        fprintf(stderr, "Error opening file %s", get_filename(LEXICON, argv));
        return ERROR_OPENING_LEXICON;
    } else if (*sentences == NULL) {
        fprintf(stderr, "Error opening file %s", get_filename(SENTENCES, argv));
        return ERROR_OPENING_SENTENCES;
    }

    *output = fopen(get_filename(OUTPUT, argv), "a");
    if (*output == NULL) {
        fprintf(stderr, "Error creating file %s", get_filename(OUTPUT, argv));
        return ERROR_CREATING_OUTPUT;
    }

    return OK;
}

Status append_in_output(FILE* output, char *line) {
    if (output == NULL) {
        fprintf(stderr, "Error handling output file.");
        return ERROR_STREAM_INVALID;
    }
    fwrite(line, 1, strlen(line), output);
}

Status close_files(FILE** lexicon, FILE** sentences, FILE** output) {
    fclose(*lexicon);
    fclose(*sentences);
    fclose(*output);
}
