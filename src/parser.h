#ifndef SENTIMENT_ANALYSIS_PARSER_H
#define SENTIMENT_ANALYSIS_PARSER_H

// Local
#include "files.h"
#include "tree.h"

#define MAXIMUM_LINE_SIZE   1000

Status handle_sentences(FILE **file, FILE **output, Node **tree);
Status handle_lexicon(FILE **file, Node **tree);

#endif //SENTIMENT_ANALYSIS_PARSER_H
