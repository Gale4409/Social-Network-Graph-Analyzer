cmake_minimum_required(VERSION 3.31)
project(social_graph_analyzer C)

set(CMAKE_C_STANDARD 99)

add_executable(social_graph_analyzer main.c
        queue.c
        Graph.c)
