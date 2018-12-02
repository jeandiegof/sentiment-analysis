cmake_minimum_required(VERSION 3.12)
project(sentiment_analysis C)

set(CMAKE_C_STANDARD 11)

subdirs(src)
add_executable(sentiment_analysis main.c files.h files.c parser.h parser.c binary-tree.c binary-tree.h avl-tree.c avl-tree.h tree.h)