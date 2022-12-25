cmake_minimum_required(VERSION 3.24)
project(mathematical_expression_parser C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mathematical_expression_parser
        args.c
        cleanup.c
        eval.h
        evaluate.c
        lexer.c
        main.c
        parse_float.c
        parser.c
        print.c
        print_tree.c
        tree_ops.c)
