#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pets.h"
#include "person.h"
#include "utils.h"

void insertPet()
{
    char type[20], name[255], birth[11];
    int personIndex;
    int index = searchEmptyPet();

    if(index == -1) {
        printf("\nNao ha espaços para inserir uma novo pet!\n");
        return;
    }

    personIndex = searchPersonByCode();
    if(personIndex == -1) {
        printf("\nPessoa nao encontrada!\n");
        return;
    }

    do {
        printf("Insira o nome do pet: ");
        scanf("%s", name);
    } while(verifyPetName(name, personIndex + 1));

    choosePetType(type);

    do {
        printf("\nInsira a data de nascimento do pet<dd/mm/aaaa>: ");
        scanf("%s", birth);
    } while(verifyBirth(birth));

    insertPetInfos(index, personIndex + 1, type, name, birth);
    printf("\nPet inserido com sucesso!\n");
}

void updatePet()
{
    char type[20], name[255], birth[11];
    int index, petCode, personCode;

    if(!searchPetByCode(&index, &petCode, &personCode)) {
        printf("Pet nao encontrado!");
        return;
    }

    do {
        printf("Insira o nome do pet: ");
        scanf("%s", name);
    } while(verifyPetName(name, personCode));

    choosePetType(type);

    do {
        printf("\nInsira a nova data de nascimento do pet<dd/mm/aaaa>: ");
        scanf("%s", birth);
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

    updatePetInfos(index, -1, -1, "", "", "");
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

    const char maxString[2] = "z";
    char smaller[255], names[petSize][255];
    int currentIndex = 0, indexes[petSize];
    int max, smallerIndex;

    printf("\nListar Todos os Pets em Ordem Alfabetica\n");

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != -1) {
            strcpy(names[currentIndex], petNames[i]);
            indexes[currentIndex] = i;
            currentIndex++;
        }
    }

    max = currentIndex;
    for(int i = 0; i < max; ++i) {
        strToUpper(names[i]);
    }

    while(currentIndex--) {
        strcpy(smaller, maxString);
        smallerIndex = 0;

        for(int i = 0; i < max; ++i) {
            if(strcmp(names[i], smaller) < 0) {
                strcpy(smaller, names[i]);
                smallerIndex = i;
            }
        }

        strcpy(names[smallerIndex], maxString);
        showPet(indexes[smallerIndex]);
    }
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
    char code[7], person[4], pet[4];
    long petNumber, personNumber;

    do {
        printf("\nInsira o codigo do pet <000000>: ");
        scanf("%s", code);
    } while(strlen(code) != 6);

    for(int i = 0; i < 3; i++)
        person[i] = code[i];
    person[3] = '\0';
    strcpy(pet, &code[3]);

    petNumber = strtol(pet, NULL, 10);
    personNumber = strtol(person, NULL, 10);

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

void insertPetInfos(int index, int personCode, char type[], char name[], char birth[])
{
    petCodes[index] = getPetCode(personCode);
    petPersonCodes[index] = personCode;
    strcpy(petTypes[index], type);
    strcpy(petNames[index], name);
    strcpy(petBirths[index], birth);
}

void updatePetInfos(int index, int petCode, int personCode, char type[], char name[], char birth[])
{
    petCodes[index] = petCode;
    petPersonCodes[index] = personCode;
    strcpy(petTypes[index], type);
    strcpy(petNames[index], name);
    strcpy(petBirths[index], birth);
}

int getPetCode(int personCode)
{
    int code = 0;

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] == -1)
            continue;

        if(petPersonCodes[i] == personCode && petCodes[i] > code)
            code = petCodes[i];
    }

    return code + 1;
}

void choosePetType(char type[])
{
    char c;
    while(1) {
        showPetTypeMenu();
        c = (char) getc(stdin);

        switch(c) {
            case '1':
                strcpy(type, "Cachorro");
                return;
            case '2':
                strcpy(type, "Gato");
                return;
            case '3':
                strcpy(type, "Cobra");
                return;
            case '4':
                strcpy(type, "Passarinho");
                return;
            default:
                printf("Opcao invalida...\n");
        }
    }
}

int verifyPetName(char name[], int personCode)
{
    char tempPetName[255];
    char tempName[255];

    strcpy(tempName, name);
    strToUpper(tempName);

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != personCode)
            continue;

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
