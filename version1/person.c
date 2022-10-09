#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "person.h"
#include "pets.h"
#include "utils.h"

void insertPerson()
{
    int index = searchEmptyPerson();
    if(index == -1) {
        printf("Nao ha espaços para inserir uma pessoa!\n");
        return;
    }

    char *name = (char *) malloc(nameMax * sizeof(char));
    printf("Insira o seu nome: ");
    readString(name, nameMax);
    name[strlen(name)-1] = '\0';

    char *cpf = (char *) malloc(cpfMax * sizeof(char));
    do {
        printf("Insira o seu cpf <000.000.000-00>: ");
        readString(cpf, cpfMax);
    } while(verifyCPF(cpf));

    char *birth = (char *) malloc(birthMax * sizeof(char));
    do {
        printf("Insira a sua data de nascimento <dd/mm/aaaa>: ");
        readString(birth, birthMax);
    } while(verifyBirth(birth));

    insertPersonInfos(index, name, cpf, birth);

    free(name);
    free(cpf);
    free(birth);

    printf("Pessoa inserida com sucesso!\n");
}

void updatePerson()
{
    int index = searchPersonByCode();
    if(index == -1) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    char *name = (char *) malloc(nameMax * sizeof(char));
    printf("Insira o novo nome: ");
    readString(name, nameMax);
    name[strlen(name)-1] = '\0';

    char *cpf = (char *) malloc(cpfMax * sizeof(char));
    do {
        printf("Insira o novo cpf <000.000.000-00>: ");
        readString(cpf, cpfMax);
    } while(verifyCPF(cpf));

    char *birth = (char *) malloc(birthMax * sizeof(char));
    do {
        printf("Insira a nova data de nascimento <dd/mm/aaaa>: ");
        readString(birth, birthMax);
    } while(verifyBirth(birth));

    insertPersonInfos(index, name, cpf, birth);

    free(name);
    free(cpf);
    free(birth);

    printf("Pessoa atualizada com sucesso!\n");
}

void deletePerson()
{
    int index = searchPersonByCode();

    if(index == -1) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    deletePersonInfos(index);
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
    while(1) {
        showPetTypeMenu();
        fflush(stdin);
        char c = (char) getc(stdin);

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
        if(personNames[i])
            showPerson(i);
    }
}

void showAllPersonsInOrder()
{
    printf("\nListar Todas as Pessoas em Ordem Alfabetica\n");

    // copy every name to another array
    int currentIndex = 0;
    int indexes[size];
    char *names[size];
    for(int i = 0; i < size; ++i) {
        if(personNames[i]) {
            names[currentIndex] = allocateString(personNames[i]);
            strcpy(names[currentIndex], personNames[i]);
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
        showPerson(indexes[smallerIndex]);
    }

    for(int i = 0; i < max; ++i)
        free(names[i]);
}

int searchEmptyPerson()
{
    for(int i = 0; i < size; ++i) {
        if(!personNames[i])
            return i;
    }

    return -1;
}

int searchPersonByCode()
{
    char code[4];
    do {
        printf("\nInsira o codigo da pessoa <000>: ");
        scanf("%s", code);
    } while(strlen(code) != 3);

    long index = strtol(code, NULL, 10) - 1;

    if(personNames[index])
        return index;
    return -1;
}

void insertPersonInfos(int index, char *name, char *cpf, char *birth)
{
    personCodes[index] = index + 1;

    personNames[index] = allocateString(name);
    strcpy(personNames[index], name);

    personCPFs[index] = allocateString(cpf);
    strcpy(personCPFs[index], cpf);

    personBirths[index] = allocateString(birth);
    strcpy(personBirths[index], birth);
}

void deletePersonInfos(int index)
{
    personCodes[index] = -1;
    personNames[index] = NULL;
    personCPFs[index] = NULL;
    personBirths[index] = NULL;
}

int verifyCPF(char *cpf)
{
    if(strlen(cpf) != 14) {
        printf("Tamanho de CPF invalido, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(size_t i = 0; i < strlen(cpf); ++i) {
        if(i == 3 || i == 7 || i == 11)
            continue;
        if(!isdigit(cpf[i])) {
            printf("Padrao de CPF invalido, verifique o exemplo entre \"<>\".\n");
            return 1;
        }
    }

    if(cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') {
        printf("Padrao de CPF invalido, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(int i = 0; i < size; ++i) {
        if(personCPFs[i] && strcmp(personCPFs[i], cpf) == 0) {
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

void showPersonPetType(char *type)
{
    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != -1 && strcmp(petTypes[i], type) == 0)
            showPerson(petPersonCodes[i] - 1);
    }
}
