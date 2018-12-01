cmake_minimum_required(VERSION 3.12)
project(sentiment_analysis C)

set(CMAKE_C_STANDARD 11)

add_executable(sentiment_analysis main.c arguments.h arguments.c parser.h parser.c binary-tree.c binary-tree.c.h)