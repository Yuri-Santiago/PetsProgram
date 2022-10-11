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

    char *rg = (char *) malloc(rgMax * sizeof(char));
    do {
        printf("Insira o seu RG: <0000000000-0>: ");
        readString(rg, rgMax);
    } while(verifyRG(rg));

    char *address = (char *) malloc(nameMax * sizeof(char));
    printf("Insira o seu Endereco: ");
    readString(address, nameMax);
    address[strlen(address)-1] = '\0';

    unsigned long income;
    printf("Insira o seu Rendimento: ");
    scanf("%lu", &income);

    insertPersonInfos(index, name, cpf, birth, rg, address, income);

    free(name);
    free(cpf);
    free(birth);
    free(rg);
    free(address);

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

    char *rg = (char *) malloc(rgMax * sizeof(char));
    do {
        printf("Insira o novo RG: <0000000000-0>: ");
        readString(rg, rgMax);
    } while(verifyRG(rg));

    char *address = (char *) malloc(nameMax * sizeof(char));
    printf("Insira o novo Endereco: ");
    readString(address, nameMax);
    address[strlen(address)-1] = '\0';

    unsigned long income;
    printf("Insira o novo Rendimento: ");
    scanf("%lu", &income);

    insertPersonInfos(index, name, cpf, birth, rg, address, income);

    free(name);
    free(cpf);
    free(birth);
    free(rg);
    free(address);

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
        char c = (char) getc(stdin);
        getchar();

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
    char *code;
    do {
        printf("\nInsira o codigo da pessoa <000>: ");
        fgets(code, 4, stdin);
    } while(!isdigit(code[0]) || !isdigit(code[1]) || !isdigit(code[2]));

    getchar();

    long index = strtol(code, NULL, 10) - 1;

    if(index >= size)
        return -1;

    if(personNames[index])
        return (int) index;
    return -1;
}

void insertPersonInfos(int index, char *name, char *cpf, char *birth, char *rg, char *address, unsigned long income)
{
    personCodes[index] = index + 1;

    personNames[index] = allocateString(name);
    strcpy(personNames[index], name);

    personCPFs[index] = allocateString(cpf);
    strcpy(personCPFs[index], cpf);

    personBirths[index] = allocateString(birth);
    strcpy(personBirths[index], birth);

    personRGs[index] = allocateString(rg);
    strcpy(personRGs[index], rg);

    personAdresses[index] = allocateString(address);
    strcpy(personAdresses[index], address);

    personIncomes[index] = income;
}

void deletePersonInfos(int index)
{
    personCodes[index] = -1;
    personNames[index] = NULL;
    personCPFs[index] = NULL;
    personBirths[index] = NULL;
    personRGs[index] = NULL;
    personAdresses[index] = NULL;
    personIncomes[index] = 0;
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

int verifyRG(char *rg)
{
    if(strlen(rg) != 12) {
        printf("Tamanho de RG invalido, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(size_t i = 0; i < strlen(rg); ++i) {
        if(i == 10)
            continue;
        if(!isdigit(rg[i])) {
            printf("Padrao de RG invalido, verifique o exemplo entre \"<>\".\n");
            return 1;
        }
    }

    if(rg[10] != '-') {
        printf("Padrao de RG invalido, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(int i = 0; i < size; ++i) {
        if(personRGs[i] && strcmp(personRGs[i], rg) == 0) {
            printf("RG ja existente no banco de dados!\n");
            return 1;
        }
    }

    return 0;
}

void showPerson(int index)
{
    printf("\nPessoa %d:\n", index+1);
    printf("Codigo: %03d\nNome: %s\nCPF: %s\nData de Nascimento: %s\n"
           "RG: %s\nEndereço: %s\nRendimento: %lu R$\n",
           personCodes[index], personNames[index], personCPFs[index], personBirths[index],
           personRGs[index], personAdresses[index], personIncomes[index]);
}

void showPersonPetType(char *type)
{
    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != -1 && strcmp(petTypes[i], type) == 0)
            showPerson(petPersonCodes[i] - 1);
    }
}
