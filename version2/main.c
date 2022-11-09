#include "person.h"
#include "pets.h"
#include "utils.h"

enum options {
    FinishProgram, PersonMenu, PetsMenu
};

struct person *start;
struct pet *petStart;

int main() {
    init();

    struct person *p = (struct person*) malloc(sizeof(struct person));
    p->code = 1;
    strcpy(p->name, "Yuri");
    strcpy(p->cpf, "111.111.111-11");
    strcpy(p->birth, "27/12/2002");
    strcpy(p->rg, "1234567891-0");
    strcpy(p->address, "Rua 3");
    p->income = 1200;

    struct person *p2 = (struct person*) malloc(sizeof(struct person));
    p2->code = 2;
    strcpy(p2->name, "Alex");
    strcpy(p2->cpf, "222.222.222-22");
    strcpy(p2->birth, "01/09/2022");
    strcpy(p2->rg, "1098765432-1");
    strcpy(p2->address, "Rua 4");
    p2->income = 3450;

    struct person *p3 = (struct person*) malloc(sizeof(struct person));
    p3->code = 3;
    strcpy(p3->name, "Raquel");
    strcpy(p3->cpf, "333.333.333-33");
    strcpy(p3->birth, "15/12/2002");
    strcpy(p3->rg, "9999999999-9");
    strcpy(p3->address, "Rua 5");
    p3->income = 1599;

    addPersonToList(p);
    addPersonToList(p2);
    addPersonToList(p3);

    struct pet *pt = (struct pet*) malloc(sizeof(struct pet));
    pt->code = 1;
    pt->personCode = 1;
    pt->type = Gato;
    strcpy(pt->name, "Nina");
    strcpy(pt->birth, "11/12/2020");
    addPetToList(pt);

    while(1) {
        showMenu();
        fflush(stdin);
        enum options opt = getc(stdin) - '0';

        switch(opt) {
            case PersonMenu:
                showPersonMenu();
                break;
            case PetsMenu:
                showPetsMenu();
                break;
            case FinishProgram:
                finish();
                return 0;
            default:
                printf("\nOpcao invalida...");
        }
    }
}
