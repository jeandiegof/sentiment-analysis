// C
#include <stdio.h>
#include <ctype.h>  // provides tolower signature
#include <stdlib.h>
// Local
#include "parser.h"

#define PARSER_VERBOSE(f_, ...)     //printf(f_, ##__VA_ARGS__)

static void str_to_lower(char* str) {
    while(*str != '\0') {
        *str = (char) tolower(*str);
        str++;
    }
}

static int is_line_valid(char* str, size_t size) {
    // to be valid, the line must have at least \t and \n + data
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
            PARSER_VERBOSE(" %s |", this_word);
            str_to_lower(this_word);
            strcpy(data.word, this_word);
            flag = 1;
        } else {
            // atoi doesn't throw any error if the conversion fails. That's a bottle neck
            const int value = atoi(this_word);
            PARSER_VERBOSE(" %d\n", value);
            data.value = value;
            flag = 0;
        }
        this_word = strtok(NULL, word_separators);
    }
    return data;
}

static int get_line_polarity(char *line, Node **tree) {
    // The given test files seems to ignore the '-' sometimes, but not every time.
    // I'll be ignoring them.
    const char word_separators[] = {" `,.&*%\?!;/'@\"$#=><()][}{:\n\t"};

    Node *node;
    int polarity = 0;

    char* this_word;
    this_word = strtok(line, word_separators);
    while (this_word != NULL) {
        str_to_lower(this_word);
        node = search(*tree, this_word);
        if (node != NULL) {
            PARSER_VERBOSE("\n\tSearch %s", this_word);
            PARSER_VERBOSE("\n\tFound %s | Value: %d\n", node->data.word, node->data.value);
            polarity += node->data.value;
        }
        this_word = strtok(NULL, word_separators);
    }
    return polarity;
}

Status handle_sentences(FILE** file, FILE** output, Node **tree) {
    if (*file == NULL) {
        fprintf(stderr, "%s %s:%d: file stream is invalid\n", __FILE__, __func__, __LINE__);
        return ERROR_STREAM_INVALID;
    }

    char line[MAXIMUM_LINE_SIZE];
    char cp_line[MAXIMUM_LINE_SIZE];
    char output_line[MAXIMUM_LINE_SIZE+5];

    while (fgets(line, MAXIMUM_LINE_SIZE, *file)) {
        if (!is_line_valid(line, strlen(line))) {
            continue;
        }
        // makes a copy of line
        strcpy(cp_line, line);
        const int polarity = get_line_polarity(line, tree);
        sprintf(output_line, "%d %s", polarity, cp_line);
        append_in_output(*output, output_line);
        PARSER_VERBOSE("%d %s", polarity, cp_line);
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