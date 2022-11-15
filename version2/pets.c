#include "pets.h"

void insertPet()
{
    struct pet *pt = (struct pet*) malloc(sizeof(struct pet));
    if(!pt) {
        printf("\nSem memoria!\n");
        return;
    }

    uint64_t code = inputCode("Insira o codigo da Pessoa <000>: ");
    struct person *p = searchPersonByCode(code);
    if(!p) {
        printf("\nPessoa nao encontrada!");
        return;
    }

    pt->type = getPetType(false);

    do {
        inputString("\nInsira nome do Pet <vazio para cancelar>: ", pt->name, stringMax, &notVerify, false);
        if(strlen(pt->name) == 1) {
            free(pt);
            return;
        }
    } while(verifyPetName(pt->name, p->code, false));

    inputString("\nInsira a data de nascimento do Pet <dd/mm/aaaa>: ", pt->birth, birthMax, &verifyBirth, false);
    pt->code = getPetCode();
    pt->personCode = p->code;

    addPetToList(pt);
    printf("\nPet inserido com sucesso!");
}

void addPetToList(struct pet *pt)
{
    if(!petStart) { // Primeiro elemento da lista
        pt->next = NULL;
        petStart = pt;
        return;
    }

    struct pet *old = NULL;
    struct pet *t = petStart;
    while(t) {
        if(strcmp(t->name, pt->name) < 0) {
            old = t;
            t = t->next;
        } else {
            if(old) { // Insere no meio da lista
                old->next = pt;
                pt->next = t;
                return;
            }

            pt->next = t; // Novo primerio elemento da lista
            petStart = pt;
            return;
        }
    }

    old->next = pt; // Insere no final da lista
    pt->next = NULL;
}

void updatePet()
{
    uint64_t code = inputCode("Insira o codigo do Pet <000>: ");
    struct pet *pt = searchPetByCode(code);
    if(!pt) {
        printf("\nPet nao encontrado!");
        return;
    }

    printf("\nAo atualizar, inserir vazio significa manter o valor existente.");

    enum petTypes type = getPetType(true);
    if(type != -1)
        pt->type = type;

    char newName[stringMax];
    do {
        strcpy(newName, "");
        inputString("\nInsira o novo nome do Pet: ", newName, stringMax, &notVerify, true);
        if(strlen(newName) == 0) {
            strcpy(newName, pt->name);
            break;
        }

        formatName(newName);
        if(strcmp(newName, pt->name) == 0)
            break;
    } while(verifyPetName(newName, pt->personCode, true));

    inputString("\nInsira a nova data de nascimento do Pet <dd/mm/aaaa>: ", pt->birth, birthMax, &verifyBirth, true);

    if(strcmp(newName, pt->name) != 0) {
        strcpy(pt->name, newName);
        removePetFromList(pt);
        addPetToList(pt);
    }
    printf("\nPet atualizado com sucesso!");
}

void deletePet()
{
    uint64_t code = inputCode("Insira o codigo do Pet <000>: ");
    struct pet *pt = searchPetByCode(code);
    if(!pt) {
        printf("\nPet nao encontrado!");
        return;
    }
    deletePetInfo(pt);
}

void deletePetsByPerson(struct person *p)
{
    printf("\nDeletar Pets de %s:", p->name);

    struct pet *pt = petStart;
    while(pt) {
        if(pt->personCode == p->code)
            deletePetInfo(pt);
        pt = pt->next;
    }
}

void deletePetInfo(struct pet *pt)
{
    removePetFromList(pt);
    free(pt);
    printf("\nPet deletado com sucesso!");
}

void removePetFromList(struct pet *pt)
{
    if(pt->code == petStart->code) { // Remove o primeiro elemento da lista
        if(pt->next)
            petStart = pt->next;
        else // Era o único elemento da lista
            petStart = NULL;
        return;
    }

    struct pet *old = petStart;
    struct pet *t = petStart->next;
    while(t) {
        if(pt->code == t->code) {
            if(t->next) // Remove o elemento do meio da lista
                old->next = t->next;
            else // Remove o ultimo da lista
                old->next = NULL;
            return;
        } else {
            old = t;
            t = t->next;
        }
    }
}

void showPetByCode()
{
    uint64_t code = inputCode("Insira o codigo do Pet <000>: ");
    struct pet *pt = searchPetByCode(code);
    if(!pt) {
        printf("\nPet nao encontrado!");
        return;
    }

    showPet(pt, 0);
}

void showPetByPersonCode()
{
    uint64_t code = inputCode("Insira o codigo da Pessoa <000>: ");
    struct person *p = searchPersonByCode(code);
    if(!p) {
        printf("\nPessoa nao encontrada!");
        return;
    }

    printf("\nListar Todos os Pets de %s", p->name);

    int i = 0;
    struct pet *pt = petStart;
    while(pt) {
        if(pt->personCode == p->code)
            showPet(pt, ++i);
        pt = pt->next;
    }
}

void showAllPets()
{
    printf("\nListar Todos os Pets em Ordem Alfabetica");

    struct pet *pt = petStart;
    while(pt) {
        showPet(pt, 0);
        pt = pt->next;
    }
}

void showPet(struct pet *pt, int num)
{
    if(num)
        printf("\n\nPet Numero %d:", num);
    else
        printf("\n\nCodigo do Dono: %03llu", pt->personCode);

    printf("\nCodigo: %03llu", pt->code);
    printf("\nTipo: %s", typeToString(pt->type));
    printf("\nNome: %s", pt->name);
    printf("\nData de Nascimento: %s", pt->birth);
}

enum petTypes getPetType(enum bool isUpdate)
{
    enum petTypes type;
    do {
        showPetTypeMenu();
        fflush(stdin);
        type = getc(stdin) - '1';

        if(isUpdate && type == -39)
            return -1;
    } while(type < 0 || type > 3);

    return type;
}

char *typeToString(enum petTypes type)
{
    switch(type) {
        case Cachorro:
            return "Cachorro";
        case Gato:
            return "Gato";        
        case Cobra:
            return "Cobra";
        case Passarinho:
            return "Passarinho";
        default:
            return "Tipo Invalido";
    }
}

enum bool personHasPetType(uint64_t personCode, enum petTypes type)
{
    struct pet *pt = petStart;
    while(pt) {
        if(pt->type == type && pt->personCode == personCode)
            return true;
        pt = pt->next;
    }

    return false;
}

enum bool verifyPetName(char *name, uint64_t personCode, enum bool isUpdate)
{
    if(!isUpdate)
        formatName(name);

    struct pet *pt = petStart;
    while(pt) {
        if(strcmp(pt->name, name) == 0 && pt->personCode == personCode) {
            printf("\nNome de pet repetido! Insira um outro nome.");
            return true;
        }
        pt = pt->next;
    }

    return false;
}

struct pet *searchPetByCode(uint64_t code)
{
    struct pet *pt = petStart;
    while(pt) {
        if(code == pt->code)
            return pt;
        pt = pt->next;
    }
    return NULL;
}

void addPetFromFile(struct pet *pt, struct pet **last)
{
    if(!(*last)) { // Primeiro elemento da lista
        pt->next = NULL;
        petStart = pt;
    } else { // Elementos logo apos o primeiro
        (*last)->next = pt;
        pt->next = NULL;
    }
}

void savePet()
{
    FILE *file = fopen("pet.bin", "wb");
    if(!file) {
        printf("\nHouve um erro ao salvar os dados!");
        exit(2);
    }

    printf("\nSalvando os dados dos Pets.");
    struct pet *pt = petStart;
    while(pt) {
        fwrite(pt, sizeof(struct pet), 1, file);
        pt = pt->next;
    }

    printf("\nDados Salvos.\n");
    fclose(file);
}

void loadPet()
{
    FILE *file = fopen("pet.bin", "rb");
    if(!file) {
        printf("\nHouve um erro ao carregar os dados!");
        exit(2);
    }

    // Libera a memoria alocada
    struct pet *pt = petStart;
    while(petStart) {
        petStart = petStart->next;
        free(pt);
        pt = petStart;
    }

    printf("\nCarregando os dados dos Pets.");
    struct pet *last = NULL;
    while(!feof(file)) {
        pt = (struct pet*) malloc(sizeof(struct pet));
        if(!pt) {
            printf("\nSem memoria!");
            return;
        }

        if(1 != fread(pt, sizeof(struct pet), 1, file))
            break;
        addPetFromFile(pt, &last);
        last = pt;
    }

    printf("\nDados Carregados.\n");
    fclose(file);
}
