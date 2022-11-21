#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "person.h"
#include "pets.h"

void init()
{
    for(int i = 0; i < size; ++i)
        personNames[i] = NULL;

    for(int i = 0; i < petSize; ++i)
        petPersonCodes[i] = -1;
}

void finish()
{
    for(int i = 0; i < size; ++i) {
        if(personNames[i]) {
            free(personNames[i]);
            free(personCPFs[i]);
            free(personBirths[i]);
            free(personRGs[i]);
            free(personAdresses[i]);
        }
    }

    for(int i = 0; i < petSize; ++i) {
        if(petPersonCodes[i] != -1) {
            free(petTypes[i]);
            free(petNames[i]);
            free(petBirths[i]);
        }
    }
}

void showMenu()
{
    printf("\nMenu de Funcionalidades");
    printf("\nDigite 1 para ir para o Menu de Pessoas.");
    printf("\nDigite 2 para ir para o Menu de Pets.");
    printf("\nDigite 0 para sair.");
    printf("\nDigite a opcao desejada: ");
}

void showPersonMenu()
{
    printf("\nMenu de Pessoas");
    printf("\nDigite 1 para inserir uma nova Pessoa.");
    printf("\nDigite 2 para atualizar uma Pessoa.");
    printf("\nDigite 3 para deletar uma Pessoa.");
    printf("\nDigite 4 para mostrar uma Pessoa pelo codigo.");
    printf("\nDigite 5 para mostrar uma Pessoa pelo Tipo de Pet.");
    printf("\nDigite 6 para mostrar todas as Pessoas.");
    printf("\nDigite 7 para mostrar todas as Pessoas em ordem alfabetica.");
    printf("\nDigite 0 voltar.");
    printf("\nDigite a opcao desejada: ");

    fflush(stdin);
    char c = (char) getc(stdin);

    switch (c) {
        case '1':
            insertPerson();
            break;
        case '2':
            updatePerson();
            break;
        case '3':
            deletePerson();
            break;
        case '4':
            showPersonByCode();
            break;
        case '5':
            showPersonsByPetType();
            break;
        case '6':
            showAllPersons();
            break;
        case '7':
            showAllPersonsInOrder();
            break;
        case '0':
            break;
        default:
            printf("\nOpcao invalida...");
    }
}

void showPetsMenu()
{
    printf("\nMenu de Pets");
    printf("\nDigite 1 para inserir um novo Pet.");
    printf("\nDigite 2 para atualizar um Pet.");
    printf("\nDigite 3 para deletar um Pet.");
    printf("\nDigite 4 para mostrar um Pet pelo codigo.");
    printf("\nDigite 5 para mostrar um Pet pelo codigo do seu Dono.");
    printf("\nDigite 6 para mostrar todos os Pets em ordem alfabetica.");
    printf("\nDigite 0 voltar.");
    printf("\nDigite a opcao desejada: ");

    fflush(stdin);
    char c = (char) getc(stdin);

    switch (c) {
        case '1':
            insertPet();
            break;
        case '2':
            updatePet();
            break;
        case '3':
            deletePet();
            break;
        case '4':
            showPetByCode();
            break;
        case '5':
            showPetByPersonCode();
            break;
        case '6':
            showAllPetsInOrder();
            break;
        case '0':
            break;
        default:
            printf("\nOpcao invalida...");
    }
}
void showPetTypeMenu()
{
    printf("\nInforme o Tipo do Pet");
    printf("\nDigite 1 para selecionar um Cachorro.");
    printf("\nDigite 2 para selecionar um Gato.");
    printf("\nDigite 3 para selecionar uma Cobra.");
    printf("\nDigite 4 para selecionar uma Passarinho.");
    printf("\nDigite a opcao desejada: ");
}

int verifyBirth(char *birth)
{
    if(strlen(birth) != 10) {
        printf("\nTamanho de Data de Nascimento invalida, verifique o exemplo entre \"<>\".");
        return 1;
    }

    for(size_t i = 0; i < strlen(birth); ++i) {
        if(i == 2 || i == 5)
            continue;
        if(!isdigit(birth[i])) {
            printf("\nPadrão de Data de Nascimento invalida, verifique o exemplo entre \"<>\".");
            return 1;
        }
    }

    if(birth[2] == '/' && birth[5] == '/')
        return 0;

    printf("\nPadrão de Data de Nascimento invalida, verifique o exemplo entre \"<>\".");
    return 1;
}

void strToUpper(char *str)
{
    for(size_t i = 0; i < strlen(str); ++i)
        str[i] = (char) toupper((int) str[i]);
}

void readString(char *str, int count)
{
    fflush(stdin);
    fgets(str, count, stdin);
}

char *allocateString(char *str)
{
    return (char *) malloc((strlen(str) + 1) * sizeof(char));
}
