#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

enum bool unloadedData;
enum bool unsavedData;

enum bool checkUnloaded()
{
    if(!unloadedData)
        return false;

    char c;
    do {
        printf("\nOs dados nao foram carregados para o programa, deseja continuar sem carregar?\n<S ou N>: ");
        fflush(stdin);
        c = toupper(getc(stdin));
    } while(c != 'S' && c != 'N');

    if(c == 'S') {
        unloadedData = false;
        return false;
    } else {
        return true;
    }
}

void setUnsavedData()
{
    unsavedData = true;
}

void init()
{
    start = NULL;
    petStart = NULL;
    unloadedData = true;
    unsavedData = false;

    createPersonFile();
    createPetFile();
    createKeysFile();
}

void finish()
{
    if(!unsavedData)
        exit(0);

    char c;
    do {
        printf("\nExistem dados nao salvos no programa, deseja sair sem salvar?\n<S ou N>: ");
        fflush(stdin);
        c = toupper(getc(stdin));
    } while(c != 'S' && c != 'N');

    if(c == 'S')
        exit(0);
}

void showMenu()
{
    printf("\n\nMenu de Funcionalidades");
    printf("\nDigite 1 para ir para o Menu de Pessoas.");
    printf("\nDigite 2 para ir para o Menu de Pets.");
    printf("\nDigite 3 para Salvar os Dados");
    printf("\nDigite 4 para Carregar os Dados");
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
    printf("\nDigite 0 voltar.");
    printf("\nDigite a opcao desejada: ");

    fflush(stdin);
    enum optionsPerson opt = getc(stdin) - '0';

    switch(opt) {
        case InsertPerson:
            insertPerson();
            break;
        case UpdatePerson:
            updatePerson();
            break;
        case DeletePerson:
            deletePerson();
            break;
        case ShowPersonCode:
            showPersonByCode();
            break;
        case ShowPersonType:
            showPersonsByPetType();
            break;
        case ShowAllPersons:
            showAllPersons();
            break;
        case FinishPerson:
            break;
        default:
            printf("\nOpcao invalida...");
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
    printf("Digite 6 para mostrar todos os Pets.\n");
    printf("Digite 0 voltar.\n");
    printf("Digite a opcao desejada: ");

    fflush(stdin);
    enum optionsPets opt = getc(stdin) - '0';

    switch(opt) {
        case InsertPet:
            insertPet();
            break;
        case UpdatePets:
            updatePet();
            break;
        case DeletePet:
            deletePet();
            break;
        case ShowPetCode:
            showPetByCode();
            break;
        case ShowPetPersonCode:
            showPetByPersonCode();
            break;
        case ShowAllPets:
            showAllPets();
            break;
        case FinishPets:
            break;
        default:
            printf("\nOpcao invalida...");
    }
}
void showPetTypeMenu()
{
    printf("\nInforme o Tipo do Pet");
    printf("\nDigite 1 para escolher Cachorro.");
    printf("\nDigite 2 para escolher Gato.");
    printf("\nDigite 3 para escolher Cobra.");
    printf("\nDigite 4 para escolher Passarinho.");
    printf("\nDigite a opcao desejada: ");
}

void trimStr(char *str)
{
    int trimBegin = 0;
    for(int i = 0; isspace(str[i]); i++)
        trimBegin++;
    strcpy(str, &str[trimBegin]);

    int trimEnd = 0;
    for(int i = (int) strlen(str) - 1; isspace(str[i]); i--)
        trimEnd++;
    str[strlen(str) - trimEnd] = '\0';
}

void formatName(char *name)
{
    trimStr(name);

    enum bool isInitial = true;
    while(*name) {
        if(isspace(*name)) {
            isInitial = true;
            name++;
            continue;
        }

        if(isInitial && isalpha(*name)) {
            *name = (char) toupper(*name);
            isInitial = false;
        } else if(isalpha(*name)) {
            *name = (char) tolower(*name);
        }

        name++;
    }
}

enum bool searchDuplicate(enum info i, const char *info)
{
    struct person *p = start;
    switch(i) {
        case InfoCPF:
            while(p) {
                if(strcmp(p->cpf, info) == 0)
                    return true;
                p = p->next;
            }
            return false;
        case InfoRG:
            while(p) {
                if(strcmp(p->rg, info) == 0)
                    return true;
                p = p->next;
            }
            return false;
        default:
            printf("\nInfo invalida!");
            return true;
    }
}

void inputString(char* message, char* str, int count, enum bool(*verify)(const char*), enum bool isUpdate)
{
    char s[255];
    do {
        printf("%s", message);
        fflush(stdin);
        fgets(s, count, stdin);

        if(isUpdate && strlen(s) == 1)
            return;
    } while(verify(s));

    strcpy(str, s);
}

enum bool verifyCPF(const char *cpf)
{
    if(strlen(cpf) != 14) {
        printf("\nTamanho de CPF invalido, verifique o exemplo entre \"<>\".");
        return true;
    }

    for(size_t i = 0; i < strlen(cpf); ++i) {
        if(i == 3 || i == 7 || i == 11)
            continue;
        if(!isdigit(cpf[i])) {
            printf("\nPadrao de CPF invalido, verifique o exemplo entre \"<>\".");
            return true;
        }
    }

    if(cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') {
        printf("\nPadrao de CPF invalido, verifique o exemplo entre \"<>\".");
        return true;
    }

    if(searchDuplicate(InfoCPF, cpf)) {
        printf("\nCPF ja existente no banco de dados!");
        return true;
    }

    return false;
}

enum bool verifyBirth(const char *birth)
{
    if(strlen(birth) != 10) {
        printf("\nTamanho de Data de Nascimento invalida, verifique o exemplo entre \"<>\".");
        return true;
    }

    for(size_t i = 0; i < strlen(birth); ++i) {
        if(i == 2 || i == 5)
            continue;
        if(!isdigit(birth[i])) {
            printf("\nPadrão de Data de Nascimento invalida, verifique o exemplo entre \"<>\".");
            return true;
        }
    }

    if(birth[2] == '/' && birth[5] == '/')
        return false;

    printf("\nPadrão de Data de Nascimento invalida, verifique o exemplo entre \"<>\".");
    return true;
}

enum bool verifyRG(const char *rg)
{
    if(strlen(rg) != 12) {
        printf("\nTamanho de RG invalido, verifique o exemplo entre \"<>\".");
        return true;
    }

    for(size_t i = 0; i < strlen(rg); ++i) {
        if(i == 10)
            continue;
        if(!isdigit(rg[i])) {
            printf("\nPadrao de RG invalido, verifique o exemplo entre \"<>\".");
            return true;
        }
    }

    if(rg[10] != '-') {
        printf("\nPadrao de RG invalido, verifique o exemplo entre \"<>\".");
        return true;
    }

    if(searchDuplicate(InfoRG, rg)) {
        printf("\nRG ja existente no banco de dados!");
        return true;
    }

    return false;
}

enum bool verifyIncome(const char *income)
{
    uint64_t incomeInt = strtoull(income, NULL, 10);
    if(!incomeInt) {
        printf("\nDigite um valor valido para o Rendimento!");
        return true;
    }
    return false;
}

enum bool verifyIsEmpty(const char *str)
{
    if(strlen(str) == 1) {
        printf("\nO campo esta vazio!");
        return true;
    }
    return false;
}

enum bool notVerify(const char *str)
{
    (void) str;
    return false;
}

void saveData()
{
    savePerson();
    savePet();

    unsavedData = false;
}

void loadData()
{
    loadPerson();
    loadPet();

    unloadedData = false;
}

void createPersonFile()
{
    FILE *file = fopen("person.bin", "rb");
    if(file != NULL) {
        fclose(file);
        return;
    }

    file = fopen("person.bin", "wb");
    if(file == NULL) {
        printf("\nHouve um erro ao criar o arquivo!");
        exit(2);
    }
    fclose(file);
}

void createPetFile()
{
    FILE *file = fopen("pet.bin", "rb");
    if(file != NULL) {
        fclose(file);
        return;
    }

    file = fopen("pet.bin", "wb");
    if(file == NULL) {
        printf("\nHouve um erro ao criar o arquivo!");
        exit(2);
    }
    fclose(file);
}

void createKeysFile()
{
    FILE *file = fopen("keys.bin", "rb");
    if(file != NULL) {
        fclose(file);
        return;
    }

    file = fopen("keys.bin", "wb");
    if(file == NULL) {
        printf("\nHouve um erro ao criar o arquivo!");
        exit(2);
    }

    uint64_t keys[2] = {3, 4};
    fwrite(keys, sizeof(uint64_t), 2, file);
    fclose(file);
}

void readKeys(uint64_t *keys)
{
    FILE *file = fopen("keys.bin", "rb");
    if(file == NULL) {
        printf("\nHouve um erro ao ler o arquivo!");
        exit(2);
    }

    fread(keys, sizeof(uint64_t), 2, file);
    fclose(file);
}

void updateKeys(uint64_t *keys)
{
    FILE *file = fopen("keys.bin", "wb");
    if(file == NULL) {
        printf("\nHouve um erro ao atualizar o arquivo!");
        exit(2);
    }

    fwrite(keys, sizeof(uint64_t), 2, file);
    fclose(file);
}

uint64_t inputCode(char *str)
{
    char codeInput[stringMax];
    do {
        printf("\n%s", str);
        fflush(stdin);
        fgets(codeInput, stringMax, stdin);
    } while(strlen(codeInput) != 4 || !isdigit(codeInput[0]) || !isdigit(codeInput[1])
            || !isdigit(codeInput[2]) || codeInput[3] != '\n');

    return strtoull(codeInput, NULL, 10);
}

uint64_t getPersonCode()
{
    return getCode(Person);
}

uint64_t getPetCode()
{
    return getCode(Pet);
}

uint64_t getCode(enum codeIndex c)
{
    uint64_t keys[2];
    readKeys(keys);
    uint64_t code = keys[c]++;
    updateKeys(keys);
    return code;
}
