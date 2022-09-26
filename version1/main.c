#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 30
#define petSize 150

// Infos of Person
int personCodes[size];
char personNames[size][255];
char personCPFs[size][15];
char personBirths[size][11];

// Infos of a Pet
int petCodes[petSize];
int petPersonCodes[petSize];
char petTypes[petSize][20];
char petNames[petSize][255];
char petBirths[petSize][11];

// Person CRUD
void insertPerson();
void updatePerson();
void deletePerson();
void showPersonByCode();
void showPersonsByPetType();
void showAllPersons();
void showAllPersonsInOrder();

// Person utils
int searchEmptyPerson();
int searchPersonByCode();
void insertPersonInfos(int index, char name[], char cpf[], char birth[]);
int verifyCPF(char cpf[]);
void showPerson(int index);
void showPersonPetType(char type[]);

// Pet CRUD
void insertPet();
void updatePet();
void deletePet();
void showPetByCode();
void showPetByPersonCode();
void showAllPetsInOrder();

// Pet utils
int searchEmptyPet();
int searchPetByCode(int *index, int *petCode, int *personCode);
void insertPetInfos(int index, int personCode, char type[], char name[], char birth[]);
void updatePetInfos(int index, int petCode, int personCode, char type[], char name[], char birth[]);
int getPetCode(int personCode);
void choosePetType(char type[]);
int verifyPetName(char name[], int personCode);
void showPet(int index);

// utils
void init();
void showMenu();
void showPetTypeMenu();
int verifyBirth(char birth[]);
void strToUpper(char str[]);

int main() {
    char c;
    init();

    insertPersonInfos(0, "Yuri", "077.183.053-09", "27/12/2002");
    insertPersonInfos(1, "Raquel", "000.000.000-00", "15/09/2022");
    insertPetInfos(0, 1, "Gato", "Nina", "25/10/2021");
    insertPetInfos(1, 1, "Cachorro", "Tusk", "20/11/2017");
    insertPetInfos(2, 1, "Passarinho", "Bot", "25/10/2021");

    while(1) {
        showMenu();
        printf("Digite a opcao desejada: ");

        do {
            c = getc(stdin);
        } while(c == '\n');

        switch(c) {
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
            case '8':
                insertPet();
                break;
            case '9':
                updatePet();
                break;
            case 'a':
                deletePet();
                break;
            case 'b':
                showPetByCode();
                break;
            case 'c':
                showPetByPersonCode();
                break;
            case 'd':
                showAllPetsInOrder();
                break;
            case '0':
                return 0;
            default:
                printf("Opcao invalida...\n");
        }
    }
}

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
        c = getc(stdin);

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
    int index;

    do {
        printf("\nInsira o codigo da pessoa <000>: ");
        scanf("%s", code);
    } while(strlen(code) != 3);

    index = atoi(code) - 1;

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
    int petNumber, personNumber;

    do {
        printf("\nInsira o codigo do pet <000000>: ");
        scanf("%s", code);
    } while(strlen(code) != 6);

    for(int i = 0; i < 3; i++)
        person[i] = code[i];
    person[4] = '\0';
    strcpy(pet, &code[3]);

    petNumber = atoi(pet);
    personNumber = atoi(person);

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
        c = getc(stdin);

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

void strToUpper(char str[])
{
    for(size_t i = 0; i < strlen(str); ++i)  {
        str[i] = (char) toupper((int) str[i]);
    }
}

// TODO: update pets with same number
