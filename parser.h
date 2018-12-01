#ifndef SENTIMENT_ANALYSIS_PARSER_H
#define SENTIMENT_ANALYSIS_PARSER_H

// Local
#include "arguments.h"
#include "binary-tree.h"

#define MAXIMUM_LINE_SIZE   1000

Status handle_words(FILE **file);
Status handle_lexicon(FILE **file, Node **tree);

#endif //SENTIMENT_ANALYSIS_PARSER_H
