#include "person.h"

struct person *start;

void insertPerson()
{
    struct person *p = (struct person*) malloc(sizeof(struct person));
    if(!p) {
        printf("\nSem memoria!");
        return;
    }

    inputString("\nInsira o seu nome <vazio para cancelar>: ", p->name, stringMax, &notVerify, false);
    if(strlen(p->name) == 1) {
        free(p);
        return;
    }
    formatName(p->name);

    inputString("\nInsira o seu cpf <000.000.000-00>: ", p->cpf, cpfMax, &verifyCPF, false);
    inputString("\nInsira a sua data de nascimento <dd/mm/aaaa>: ", p->birth, birthMax, &verifyBirth, false);
    inputString("\nInsira o seu RG: <0000000000-0>: ", p->rg, rgMax, &verifyRG, false);
    inputString("\nInsira o seu Endereco: ", p->address, stringMax, &verifyIsEmpty, false);
    trimStr(p->address);

    char incomeChar[stringMax];
    inputString("\nInsira o seu Rendimento: ", incomeChar, stringMax, &verifyIncome, false);
    p->income = strtoull(incomeChar, NULL, 0);
    p->code = getPersonCode();

    addPersonToList(p);
    printf("\nPessoa inserida com sucesso!\n");

    setUnsavedData();
}

void addPersonToList(struct person *p)
{
    if(!start) { // Primeiro elemento da lista
        p->next = NULL;
        start = p;
        return;
    }

    struct person *old = NULL;
    struct person *t = start;
    while(t) {
        if(strcmp(t->name, p->name) < 0) {
            old = t;
            t = t->next;
        } else {
            if(old) { // Insere no meio da lista
                old->next = p;
                p->next = t;
                return;
            }

            p->next = t; // Novo primerio elemento da lista
            start = p;
            return;
        }
    }

    old->next = p; // Insere no final da lista
    p->next = NULL;
}

void updatePerson()
{
    uint64_t code = inputCode("Insira o codigo da Pessoa <000>: ");
    struct person *p = searchPersonByCode(code);
    if(!p) {
        printf("\nPessoa nao encontrada!");
        return;
    }

    printf("\nAo atualizar, inserir vazio significa manter o valor existente.");

    char oldName[stringMax];
    strcpy(oldName, p->name);
    inputString("\nInsira o novo nome: ", p->name, stringMax, &notVerify, true);
    formatName(p->name);

    inputString("\nInsira o novo cpf <000.000.000-00>: ", p->cpf, cpfMax, &verifyCPF, true);
    inputString("\nInsira a sua data de nascimento <dd/mm/aaaa>: ", p->birth, birthMax, &verifyBirth, true);
    inputString("\nInsira o seu RG: <0000000000-0>: ", p->rg, rgMax, &verifyRG, true);
    inputString("\nInsira o seu Endereco: ", p->address, stringMax, &verifyIsEmpty, true);
    trimStr(p->address);

    char incomeChar[stringMax];
    inputString("\nInsira o seu Rendimento: ", incomeChar, stringMax, &verifyIncome, true);
    if(strlen(incomeChar) != 0)
        p->income = strtoull(incomeChar, NULL, 0);

    if(strcmp(oldName, p->name) != 0) {
        removePersonFromList(p);
        addPersonToList(p);
    }
    printf("\nPessoa atualizada com sucesso!");

    setUnsavedData();
}

void deletePerson()
{
    uint64_t code = inputCode("Insira o codigo da Pessoa <000>: ");
    struct person *p = searchPersonByCode(code);
    if(!p) {
        printf("\nPessoa nao encontrada!");
        return;
    }

    removePersonFromList(p);
    deletePetsByPerson(p);

    free(p);
    printf("\nPessoa deletada com sucesso!");

    setUnsavedData();
}

void removePersonFromList(struct person *p)
{
    if(p->code == start->code) { // Remove o primeiro elemento da lista
        if(p->next)
            start = p->next;
        else // Era o único elemento da lista
            start = NULL;
        return;
    }

    struct person *old = start;
    struct person *t = start->next;
    while(t) {
        if(p->code == t->code) {
            if(t->next)// Remove o elemento do meio da lista
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

void showPersonByCode()
{
    uint64_t code = inputCode("Insira o codigo da Pessoa <000>: ");
    struct person *p = searchPersonByCode(code);
    if(!p) {
        printf("\nPessoa nao encontrada!");
        return;
    }

    showPerson(p, 0);
}

void showPersonsByPetType()
{
    showPetTypeMenu();
    fflush(stdin);
    enum petTypes type = getc(stdin) - '1';

    if(type < 0 || type > 3) {
        printf("\nOpcao invalida...");
        return;
    }

    printf("\nPessoas com o tipo de pet escolhido:\n");

    struct person *p = start;
    int i = 0;
    while(p) {
        if(personHasPetType(p->code, type))
            showPerson(p, ++i);
        p = p->next;
    }
}

void showAllPersons()
{
    printf("\nListar Todas as Pessoas\n");

    struct person *p = start;
    int i = 0;
    while(p) {
        showPerson(p, ++i);
        p = p->next;
    }
}

void showPerson(struct person *p, int num)
{
    if(num)
        printf("\n\nPessoa Numero %d:", num);
    else
        printf("\n");

    printf("\nCodigo: %03llu", p->code);
    printf("\nNome: %s", p->name);
    printf("\nCPF: %s", p->cpf);
    printf("\nData de Nascimento: %s", p->birth);
    printf("\nRG: %s", p->rg);
    printf("\nEndereco: %s", p->address);
    printf("\nRendimento: %llu R$", p->income);
}

struct person *searchPersonByCode(uint64_t code)
{
    struct person *p = start;
    while(p) {
        if(p->code == code)
            return p;
        p = p->next;
    }
    return NULL;
}

void addPersonFromFile(struct person *p, struct person **last)
{
    if(!(*last)) // Primeiro elemento da lista
        start = p;
    else // Elementos logo apos o primeiro
        (*last)->next = p;

    p->next = NULL;
}

void savePerson()
{
    FILE *file = fopen("person.bin", "wb");
    if(!file) {
        printf("\nHouve um erro ao salvar os dados!");
        exit(2);
    }

    printf("\nSalvando os dados das Pessoas.");
    struct person *p = start;
    while(p) {
        fwrite(p, sizeof(struct person), 1, file);
        p = p->next;
    }

    printf("\nDados Salvos.\n");
    fclose(file);
}

void loadPerson()
{
    FILE *file = fopen("person.bin", "rb");
    if(!file) {
        printf("\nHouve um erro ao carregar os dados!");
        exit(2);
    }

    // Libera a memoria alocada
    struct person *p = start;
    while(start) {
        start = start->next;
        free(p);
        p = start;
    }

    printf("\nCarregando os dados das Pessoas.");
    struct person *last = NULL;
    while(!feof(file)) {
        p = (struct person*) malloc(sizeof(struct person));
        if(!p) {
            printf("\nSem memoria!");
            return;
        }

        if(1 != fread(p, sizeof(struct person), 1, file))
            break;
        addPersonFromFile(p, &last);
        last = p;
    }

    printf("\nDados Carregados.\n");
    fclose(file);
}
