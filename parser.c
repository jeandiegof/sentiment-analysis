// C
#include <stdio.h>
#include <ctype.h>  // provides tolower signature
#include <stdlib.h>
// Local
#include "parser.h"
#include "binary-tree.h"

static void str_to_lower(char* str) {
    while(*str != '\0') {
        *str = (char) tolower(*str);
        str++;
    }
}

static int is_line_valid(char* str, size_t size) {
    // to be valid, the line must have at least \t and \n
    return size > 2;
}

static Data tokenize_line (char* line) {
    char *this_word = NULL;
    char word_separators[] = {"\t\n"};

    uint8_t flag = 0;
    Data data = {0};

    this_word = strtok(line, word_separators);
    while (this_word != NULL) {
        if(flag == 0) {
            printf(" %s |", this_word);
            strcpy(data.word, this_word);
            flag = 1;
        } else {
            // atoi doesn't throw any error if the conversion fails. That's a bottle neck
            const int value = atoi(this_word);
            printf(" %d\n", value);
            data.value = value;
            flag = 0;
        }
        this_word = strtok(NULL, word_separators);
    }
    return data;
}

Status handle_words(FILE** file) {
    if (*file == NULL) {
        fprintf(stderr, "%s %s:%d: file stream is invalid\n", __FILE__, __func__, __LINE__);
        return ERROR_STREAM_INVALID;
    }

    char line[MAXIMUM_LINE_SIZE];
    char word_separators[] = {" `,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    char* this_word;

    while (fgets(line, MAXIMUM_LINE_SIZE, *file)) {
        this_word = strtok(line, word_separators);
        while (this_word != NULL) {
            str_to_lower(this_word);
            //printf("%s\n", this_word);
            this_word = strtok(NULL, word_separators);
        }
    }
}

Status handle_lexicon(FILE** file, Node **tree) {
    if (*file == NULL) {
        fprintf(stderr, "%s %s:%d: file stream is invalid\n", __FILE__, __func__, __LINE__);
        return ERROR_STREAM_INVALID;
    }

    char line[MAXIMUM_LINE_SIZE] = {0};
    Data data;

    while (fgets(line, MAXIMUM_LINE_SIZE, *file)) {
        if(!is_line_valid(line, strlen(line))) {
            continue;
        }
        // gets the word and its value from the line
        data = tokenize_line(line);
        *tree = insert(*tree, data);
    }
}