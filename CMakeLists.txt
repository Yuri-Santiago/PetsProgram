cmake_minimum_required(VERSION 3.23)
project(PetsProgram C)

set(CMAKE_C_STANDARD 11)

add_executable(PetsProgram
        version1/main.c
        version1/person.h version1/person.c
        version1/pets.h version1/pets.c
        version1/utils.h version1/utils.c)
