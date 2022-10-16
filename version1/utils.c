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
    printf("\nMenu de Funcionalidades\n");
    printf("Digite 1 para ir para o Menu de Pessoas.\n");
    printf("Digite 2 para ir para o Menu de Pets.\n");
    printf("Digite 0 para sair.\n");
    printf("Digite a opcao desejada: ");
}

void showPersonMenu()
{
    printf("\nMenu de Pessoas\n");
    printf("Digite 1 para inserir uma nova Pessoa.\n");
    printf("Digite 2 para atualizar uma Pessoa.\n");
    printf("Digite 3 para deletar uma Pessoa.\n");
    printf("Digite 4 para mostrar uma Pessoa pelo codigo.\n");
    printf("Digite 5 para mostrar uma Pessoa pelo Tipo de Pet.\n");
    printf("Digite 6 para mostrar todas as Pessoas.\n");
    printf("Digite 7 para mostrar todas as Pessoas em ordem alfabetica.\n");
    printf("Digite 0 voltar.\n");
    printf("Digite a opcao desejada: ");

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
            printf("Opcao invalida...\n");
    }
}

void showPetsMenu()
{
    printf("\nMenu de Pets\n");
    printf("Digite 1 para inserir um novo Pet.\n");
    printf("Digite 2 para atualizar um Pet.\n");
    printf("Digite 3 para deletar um Pet.\n");
    printf("Digite 4 para mostrar um Pet pelo codigo.\n");
    printf("Digite 5 para mostrar um Pet pelo codigo do seu Dono.\n");
    printf("Digite 6 para mostrar todos os Pets em ordem alfabetica.\n");
    printf("Digite 0 voltar.\n");
    printf("Digite a opcao desejada: ");

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
            printf("Opcao invalida...\n");
    }
}
void showPetTypeMenu()
{
    printf("\nInforme o Tipo do Pet\n");
    printf("Digite 1 para selecionar um Cachorro.\n");
    printf("Digite 2 para selecionar um Gato.\n");
    printf("Digite 3 para selecionar uma Cobra.\n");
    printf("Digite 4 para selecionar uma Passarinho.\n");
    printf("Digite a opcao desejada: ");
}

int verifyBirth(char *birth)
{
    if(strlen(birth) != 10) {
        printf("Tamanho de Data de Nascimento invalida, verifique o exemplo entre \"<>\".\n");
        return 1;
    }

    for(size_t i = 0; i < strlen(birth); ++i) {
        if(i == 2 || i == 5)
            continue;
        if(!isdigit(birth[i])) {
            printf("Padrão de Data de Nascimento invalida, verifique o exemplo entre \"<>\".\n");
            return 1;
        }
    }

    if(birth[2] == '/' && birth[5] == '/')
        return 0;

    printf("Padrão de Data de Nascimento invalida, verifique o exemplo entre \"<>\".\n");
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
