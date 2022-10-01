#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "person.h"
#include "pets.h"
#include "utils.h"

void insertPerson()
{
    char name[255], cpf[15], birth[11];
    int index = searchEmptyPerson();

    if(index == -1) {
        printf("Nao ha espaços para inserir uma pessoa!\n");
        return;
    }

    printf("Insira o seu nome: ");
    scanf("%s", name);

    do {
        printf("Insira o seu cpf <000.000.000-00>: ");
        scanf("%s", cpf);
    } while(verifyCPF(cpf));

    do {
        printf("Insira a sua data de nascimento <dd/mm/aaaa>: ");
        scanf("%s", birth);
    } while(verifyBirth(birth));

    insertPersonInfos(index, name, cpf, birth);
    printf("Pessoa inserida com sucesso!\n");
}

void updatePerson()
{
    char name[255], cpf[15], birth[11];
    int index = searchPersonByCode();

    if(index == -1) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    printf("Insira o novo nome: ");
    scanf("%s", name);

    do {
        printf("Insira o novo cpf <000.000.000-00>: ");
        scanf("%s", cpf);
    } while(verifyCPF(cpf));

    do {
        printf("Insira a nova data de nascimento <dd/mm/aaaa>: ");
        scanf("%s", birth);
    } while(verifyBirth(birth));

    insertPersonInfos(index, name, cpf, birth);
    printf("Pessoa atualizada com sucesso!\n");
}

void deletePerson()
{
    int index = searchPersonByCode();

    if(index == -1) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    insertPersonInfos(index, "", "", "");
    printf("Pessoa deletada com sucesso!\n");
}

void showPersonByCode()
{
    int index = searchPersonByCode();

    if(index == -1) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    showPerson(index);
}

void showPersonsByPetType()
{
    char c;
    while(1) {
        showPetTypeMenu();
        c = (char) getc(stdin);

        switch(c) {
            case '1':
                showPersonPetType("Cachorro");
                return;
            case '2':
                showPersonPetType("Gato");
                return;
            case '3':
                showPersonPetType("Cobra");
                return;
            case '4':
                showPersonPetType("Passarinho");
                return;
            default:
                printf("Opcao invalida...\n");
        }
    }
}

void showAllPersons()
{
    printf("\nListar Todas as Pessoas\n");

    for(int i = 0; i < size; ++i) {
        if(strcmp(personNames[i], "") != 0)
            showPerson(i);
    }
}

void showAllPersonsInOrder()
{
    const char maxString[2] = "z";
    char smaller[255], names[size][255];
    int currentIndex = 0, indexes[size];
    int max, smallerIndex;

    printf("\nListar Todas as Pessoas em Ordem Alfabetica\n");

    for(int i = 0; i < size; ++i) {
        if(strcmp(personNames[i], "") != 0) {
            strcpy(names[currentIndex], personNames[i]);
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
        showPerson(indexes[smallerIndex]);
    }
}

int searchEmptyPerson()
{
    for(int i = 0; i < size; ++i) {
        if(strcmp(personNames[i], "") == 0)
            return i;
    }

    return -1;
}

int searchPersonByCode()
{
    char code[4];
    long index;

    do {
        printf("\nInsira o codigo da pessoa <000>: ");
        scanf("%s", code);
    } while(strlen(code) != 3);

    index = strtol(code, NULL, 10) - 1;

    if(strcmp(personNames[index], "") != 0)
        return index;
    return -1;
}

void insertPersonInfos(int index, char name[], char cpf[], char birth[])
{
    personCodes[index] = index + 1;
    strcpy(personNames[index], name);
    strcpy(personCPFs[index], cpf);
    strcpy(personBirths[index], birth);
}

int verifyCPF(char cpf[])
{
    if(strlen(cpf) != 14) {
        printf("Tamanho de CPF invalido, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(size_t i = 0; i < strlen(cpf); ++i) {
        if(i == 3 || i == 7 || i == 11)
            continue;
        if(!isdigit(cpf[i])) {
            printf("Padrão de CPF invalido, verifique o exemplo entre \"<>\".\n");
            return 1;
        }
    }

    if(cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') {
        printf("Padrão de CPF invalido, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(int i = 0; i < size; ++i) {
        if(strcmp(personCPFs[i], cpf) == 0) {
            printf("CPF ja existente no banco de dados!\n");
            return 1;
        }
    }

    return 0;
}

void showPerson(int index)
{
    printf("\nPessoa %d:\n", index+1);
    printf("Codigo: %03d\nNome: %s\nCPF: %s\nData de Nascimento: %s\n",
           personCodes[index], personNames[index], personCPFs[index], personBirths[index]);
}

void showPersonPetType(char type[])
{
    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] == -1)
            continue;
        if(strcmp(petTypes[i], type) == 0)
            showPerson(petPersonCodes[i] - 1);
    }
}
