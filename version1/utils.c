#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "person.h"
#include "pets.h"

void init()
{
    for(int i = 0; i < size; ++i)
        strcpy(personNames[i], "");

    for(int i = 0; i < petSize; ++i)
        petPersonCodes[i] = -1;
}

void showMenu()
{
    printf("\nMenu de Funcionalidades\n");
    printf("Digite 1 para inserir uma nova Pessoa.\n");
    printf("Digite 2 para atualizar uma Pessoa.\n");
    printf("Digite 3 para deletar uma Pessoa.\n");
    printf("Digite 4 para mostrar uma Pessoa pelo codigo.\n");
    printf("Digite 5 para mostrar uma Pessoa pelo Tipo de Pet.\n");
    printf("Digite 6 para mostrar todas as Pessoas.\n");
    printf("Digite 7 para mostrar todas as Pessoas em ordem alfabetica.\n");
    printf("Digite 8 para inserir um novo Pet.\n");
    printf("Digite 9 para atualizar um Pet.\n");
    printf("Digite a para deletar um Pet.\n");
    printf("Digite b para mostrar um Pet pelo codigo.\n");
    printf("Digite c para mostrar um Pet pelo codigo do seu Dono.\n");
    printf("Digite d para mostrar todos os Pets em ordem alfabetica.\n");
    printf("Digite 0 sair.\n");
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

int verifyBirth(char birth[])
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

void strToUpper(char str[])
{
    for(size_t i = 0; i < strlen(str); ++i)  {
        str[i] = (char) toupper((int) str[i]);
    }
}
