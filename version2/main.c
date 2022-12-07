#include "person.h"
#include "pets.h"
#include "utils.h"

enum options {
    FinishProgram, PersonMenu, PetsMenu, SaveData, LoadData
};

void insertPersonInfos(uint64_t code, char *name, char *cpf, char *birth, char *rg, char *address, uint64_t income)
{
    struct person *p = (struct person*) malloc(sizeof(struct person));
    p->code = code;
    strcpy(p->name, name);
    strcpy(p->cpf, cpf);
    strcpy(p->birth, birth);
    strcpy(p->rg, rg);
    strcpy(p->address, address);
    p->income = income;
    addPersonToList(p);
}

void insertPetInfos(uint64_t code, uint64_t personCode, enum petTypes type, char *name, char *birth)
{
    struct pet *pt = (struct pet*) malloc(sizeof(struct pet));
    pt->code = code;
    pt->personCode = personCode;
    pt->type = type;
    strcpy(pt->name, name);
    strcpy(pt->birth, birth);
    addPetToList(pt);
}

int main() {
    init();

    insertPersonInfos(1, "Yuri", "111.111.111-11", "27/12/2002", "1234567891-0", "Rua 3", 1650);
    insertPersonInfos(2, "Alex", "222.222.222-22", "01/09/2022", "1098765432-1", "Rua 4", 2500);
    insertPetInfos(1, 1, Gato, "Nina", "25/10/2021");
    insertPetInfos(2, 1, Cachorro, "Tusk", "20/11/2017");
    insertPetInfos(3, 2, Gato, "Pequeno", "15/03/2020");

    while(1) {
        showMenu();
        fflush(stdin);
        enum options opt = getc(stdin) - '0';

        switch(opt) {
            case PersonMenu:
                if(checkUnloaded())
                    break;
                showPersonMenu();
                break;
            case PetsMenu:
                if(checkUnloaded())
                    break;
                showPetsMenu();
                break;
            case SaveData:
                saveData();
                break;
            case LoadData:
                loadData();
                break;
            case FinishProgram:
                finish();
                break; //return 0;
            default:
                printf("\nOpcao invalida...");
        }
    }
}
