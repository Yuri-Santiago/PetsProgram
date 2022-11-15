#include "person.h"
#include "pets.h"
#include "utils.h"

enum options {
    FinishProgram, PersonMenu, PetsMenu, SaveData, LoadData
};

struct person *start;
struct pet *petStart;

int main() {
    init();

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
            case SaveData:
                saveData();
                break;
            case LoadData:
                loadData();
                break;
            case FinishProgram:
                finish();
                return 0;
            default:
                printf("\nOpcao invalida...");
        }
    }
}
