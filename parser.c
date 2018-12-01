// C
#include <stdio.h>
#include <ctype.h>  // provides tolower signature
// Local
#include "parser.h"

static void str_to_lower(char *str) {
    while(*str != '\0') {
        *str = tolower(*str);
        str++;
    }
}

Status handle_words(FILE **file) {
    if (*file == NULL) {
        fprintf(stderr, "%s %s:%d: file stream is invalid\n", __FILE__, __func__, __LINE__);
        return ERROR_STREAM_INVALID;
    }

    char line[MAXIMUM_LINE_SIZE];
    char word_separators[] = {" `,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    char *this_word;

    while (fgets(line, MAXIMUM_LINE_SIZE, *file)) {
        this_word = strtok(line, word_separators);
        while (this_word != NULL) {
            str_to_lower(this_word);
            printf("%s\n", this_word);
            this_word = strtok(NULL, word_separators);
        }
    }
}