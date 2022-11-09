cmake_minimum_required(VERSION 3.23)
project(PetsProgram C)

set(CMAKE_C_STANDARD 17)

add_executable(PetsProgramV1
        version1/main.c
        version1/person.h version1/person.c
        version1/pets.h version1/pets.c
        version1/utils.h version1/utils.c)

add_executable(PetsProgramV2
        version2/main.c
        version2/person.h version2/person.c
        version2/pets.h version2/pets.c
        version2/utils.h version2/utils.c)
