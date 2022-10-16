#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pets.h"
#include "person.h"
#include "utils.h"

void insertPet()
{
    int index = searchEmptyPet();
    if(index == -1) {
        printf("\nNao ha espaços para inserir uma novo pet!\n");
        return;
    }

    int personIndex = searchPersonByCode();
    if(personIndex == -1) {
        printf("\nPessoa nao encontrada!\n");
        return;
    }

    char *name = (char *) malloc(nameMax * sizeof(char));
    do {
        printf("Insira o nome do pet<vazio para cancelar>: ");
        readString(name, nameMax);

        if(strlen(name) == 1)
            return;

        name[strlen(name)-1] = '\0';
    } while(verifyPetName(name, personIndex + 1));

    char *type;
    do {
        type = choosePetType();
    } while(strcmp(type, "") == 0);

    char *birth = (char *) malloc(birthMax * sizeof(char));
    do {
        printf("\nInsira a data de nascimento do pet <dd/mm/aaaa>: ");
        readString(birth, birthMax);
    } while(verifyBirth(birth));

    insertPetInfos(index, personIndex + 1, type, name, birth);

    free(name);
    free(type);
    free(birth);

    printf("\nPet inserido com sucesso!\n");
}

void updatePet()
{
    int index, petCode, personCode;
    if(!searchPetByCode(&index, &petCode, &personCode)) {
        printf("Pet nao encontrado!");
        return;
    }

    printf("Ao atualizar, inserir vazio significa manter o valor existente.\n");

    char *name = (char *) malloc(nameMax * sizeof(char));
    do {
        printf("Insira o nome do pet: ");
        readString(name, nameMax);

        if(strlen(name) == 1) {
            strcpy(name, petNames[index]);
            break;
        }

        name[strlen(name)-1] = '\0';
    } while(verifyPetName(name, personCode));

    char *type = choosePetType();
    if(strcmp(type, "") == 0) {
        free(type);
        type = allocateString(petTypes[index]);
        strcpy(type, petTypes[index]);
    }

    char *birth = (char *) malloc(birthMax * sizeof(char));
    do {
        printf("\nInsira a nova data de nascimento do pet <dd/mm/aaaa>: ");
        readString(birth, birthMax);

        if(strlen(birth) == 1) {
            strcpy(birth, petBirths[index]);
            break;
        }
    } while(verifyBirth(birth));

    updatePetInfos(index, petCode, personCode, type, name, birth);

    free(name);
    free(type);
    free(birth);

    printf("\nPet atualizado com sucesso!\n");
}

void deletePet()
{
    int index, petCode, personCode;
    if(!searchPetByCode(&index, &petCode, &personCode)) {
        printf("Pet nao encontrado!");
        return;
    }

    deletePetInfos(index);
    printf("Pet deletado com sucesso!\n");
}

void showPetByCode()
{
    int index, petCode, personCode;
    if(!searchPetByCode(&index, &petCode, &personCode)) {
        printf("Pet nao encontrado!");
        return;
    }

    showPet(index);
}

void showPetByPersonCode()
{
    int index = searchPersonByCode();
    if(index == -1) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    printf("\nListar Todos os Pets de %s\n", personNames[index]);
    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != -1 && petPersonCodes[i] == index+1)
            showPet(i);
    }
}

void showAllPetsInOrder()
{
    printf("\nListar Todos os Pets em Ordem Alfabetica\n");

    // copy every name to another array
    int currentIndex = 0;
    int indexes[petSize];
    char *names[petSize];
    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != -1) {
            names[currentIndex] = allocateString(petNames[i]);
            strcpy(names[currentIndex], petNames[i]);
            indexes[currentIndex] = i;
            currentIndex++;
        }
    }

    // transform every name to upper
    int max = currentIndex;
    for(int i = 0; i < max; ++i)
        strToUpper(names[i]);

    char smaller[nameMax];
    while(currentIndex--) {
        strcpy(smaller, "z");
        int smallerIndex = 0;

        for(int i = 0; i < max; ++i) {
            if(strcmp(names[i], smaller) < 0) {
                strcpy(smaller, names[i]);
                smallerIndex = i;
            }
        }

        strcpy(names[smallerIndex], "z");
        showPet(indexes[smallerIndex]);
    }

    for(int i = 0; i < max; ++i)
        free(names[i]);
}

int searchEmptyPet()
{
    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] == -1)
            return i;
    }

    return -1;
}

int searchPetByCode(int *index, int *petCode, int *personCode)
{
    char *code = (char *) malloc(nameMax * sizeof(char));
    do {
        printf("\nInsira o codigo do pet <000000>: ");
        fflush(stdin);
        fgets(code, nameMax, stdin);
    } while(strlen(code) != 7 || !isdigit(code[0]) || !isdigit(code[1]) || !isdigit(code[2])
            || !isdigit(code[3]) || !isdigit(code[4]) || !isdigit(code[5]) || code[6] != '\n');

    char pet[4];
    strcpy(pet, &code[3]);

    char person[4];
    memset(person, '\0', sizeof(person));
    strncpy(person, code, 3);

    free(code);

    long petNumber = strtol(pet, NULL, 10);
    long personNumber = strtol(person, NULL, 10);

    if(petNumber >= petSize || personNumber >= size)
        return 0;

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] == personNumber && petCodes[i] == petNumber) {
            *index = i;
            *personCode = (int) personNumber;
            *petCode = (int) petNumber;
            return 1;
        }
    }

    return 0;
}

void insertPetInfos(int index, int personCode, char *type, char *name, char *birth)
{
    petCodes[index] = getPetCode(personCode);
    petPersonCodes[index] = personCode;

    petTypes[index] = allocateString(type);
    strcpy(petTypes[index], type);

    petNames[index] = allocateString(name);
    strcpy(petNames[index], name);

    petBirths[index] = allocateString(birth);
    strcpy(petBirths[index], birth);
}

void updatePetInfos(int index, int petCode, int personCode, char *type, char *name, char *birth)
{
    petCodes[index] = petCode;
    petPersonCodes[index] = personCode;

    petTypes[index] = allocateString(type);
    strcpy(petTypes[index], type);

    petNames[index] = allocateString(name);
    strcpy(petNames[index], name);

    petBirths[index] = allocateString(birth);
    strcpy(petBirths[index], birth);
}

void deletePetInfos(int index)
{
    petCodes[index] = -1;
    petPersonCodes[index] = -1;
    free(petTypes[index]);
    petTypes[index] = NULL;
    free(petNames[index]);
    petNames[index] = NULL;
    free(petBirths[index]);
    petBirths[index] = NULL;
}

int getPetCode(int personCode)
{
    int code = 0;

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] == -1)
            continue;

        // get the max current petCode
        if(petPersonCodes[i] == personCode && petCodes[i] > code)
            code = petCodes[i];
    }

    return code + 1;
}

char *choosePetType()
{
    showPetTypeMenu();
    fflush(stdin);
    char c = (char) getc(stdin);

    char *type = (char *) malloc(petTypeMax * sizeof(char));
    switch(c) {
        case '1':
            strcpy(type, "Cachorro");
            break;
        case '2':
            strcpy(type, "Gato");
            break;
        case '3':
            strcpy(type, "Cobra");
            break;
        case '4':
            strcpy(type, "Passarinho");
            break;
        default:
            strcpy(type, "");
    }

    return type;
}

int verifyPetName(char *name, int personCode)
{
    char insertedName[nameMax];
    strcpy(insertedName, name);
    strToUpper(insertedName);

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != personCode)
            continue;

        char petName[nameMax];
        strcpy(petName, petNames[i]);
        strToUpper(petName);

        if(strcmp(petName, insertedName) == 0) {
            printf("Nome de pet repetido! Insira um outro nome.\n");
            return 1;
        }
    }

    return 0;
}

void showPet(int index)
{
    printf("\nPet %d de %s:\n", petCodes[index], personNames[petPersonCodes[index]-1]);
    printf("Codigo: %03d%03d\nTipo: %s\nNome: %s\nData de Nascimento: %s\n",
            petPersonCodes[index], petCodes[index], petTypes[index], petNames[index], petBirths[index]);
}
