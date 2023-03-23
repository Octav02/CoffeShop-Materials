cmake_minimum_required(VERSION 3.24)
project(CoffeeShop_Materials C)

set(CMAKE_C_STANDARD 17)

add_executable(CoffeeShop_Materials main.c material.c material.h list.c list.h service.c service.h ui.c ui.h sorting.c sorting.h)
