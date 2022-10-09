#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("Insira o nome do pet: ");
        readString(name, nameMax);
        name[strlen(name)-1] = '\0';
    } while(verifyPetName(name, personIndex + 1));

    char *type = choosePetType();

    char *birth = (char *) malloc(birthMax * sizeof(char));
    do {
        printf("\nInsira a data de nascimento do pet<dd/mm/aaaa>: ");
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

    char *name = (char *) malloc(nameMax * sizeof(char));
    do {
        printf("Insira o nome do pet: "); // TODO: mesmo nome de pet na hora de atualizar não atualiza...
        readString(name, nameMax);
        name[strlen(name)-1] = '\0';
    } while(verifyPetName(name, personCode));

    char *type = choosePetType();

    char *birth = (char *) malloc(birthMax * sizeof(char));
    do {
        printf("\nInsira a nova data de nascimento do pet<dd/mm/aaaa>: ");
        readString(birth, birthMax);
    } while(verifyBirth(birth));

    updatePetInfos(index, petCode, personCode, type, name, birth);
    printf("\nPet inserido com sucesso!\n");
}

void deletePet()
{
    int index, petCode, personCode;
    if(!searchPetByCode(&index, &petCode, &personCode)) {
        printf("Pet nao encontrado!");
        return;
    }

    deletePetInfos(index);
    printf("Pessoa deletada com sucesso!\n");
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
    char code[7];
    do {
        printf("\nInsira o codigo do pet <000000>: ");
        scanf("%s", code);
    } while(strlen(code) != 6);

    char person[4];
    for(int i = 0; i < 3; i++)
        person[i] = code[i];
    person[3] = '\0';

    char pet[4];
    strcpy(pet, &code[3]);

    long petNumber = strtol(pet, NULL, 10);
    long personNumber = strtol(person, NULL, 10);

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] == personNumber && petCodes[i] == petNumber) {
            *index = i;
            *personCode = personNumber;
            *petCode = petNumber;
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
    petTypes[index] = NULL;
    petNames[index] = NULL;
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
    while(1) {
        showPetTypeMenu();
        fflush(stdin);
        char c = (char) getc(stdin);

        char *type = (char *) malloc(petTypeMax * sizeof(char));
        switch(c) {
            case '1':
                strcpy(type, "Cachorro");
                return type;
            case '2':
                strcpy(type, "Gato");
                return type;
            case '3':
                strcpy(type, "Cobra");
                return type;
            case '4':
                strcpy(type, "Passarinho");
                return type;
            default:
                printf("Opcao invalida...\n");
        }
    }
}

int verifyPetName(char *name, int personCode)
{
    char tempName[255];
    strcpy(tempName, name);
    strToUpper(tempName);

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != personCode)
            continue;

        char tempPetName[255];
        strcpy(tempPetName, petNames[i]);
        strToUpper(tempPetName);

        if(strcmp(tempPetName, tempName) == 0) {
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
