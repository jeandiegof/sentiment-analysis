cmake_minimum_required(VERSION 3.12)
project(sentiment_analysis C)

set(CMAKE_C_STANDARD 11)

add_executable(sentiment_analysis src/main.c src/files.h src/files.c src/parser.h src/parser.c src/binary-tree.c src/binary-tree.h src/avl-tree.c src/avl-tree.h src/tree.h)