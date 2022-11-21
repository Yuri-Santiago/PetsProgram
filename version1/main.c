#include <stdio.h>

#include "person.h"
#include "pets.h"
#include "utils.h"

// Person Data
int personCodes[size];
char *personNames[size];
char *personCPFs[size];
char *personBirths[size];
char *personRGs[size];
char *personAdresses[size];
unsigned long personIncomes[size];

// Pets Data
int petCodes[petSize];
int petPersonCodes[petSize];
char *petTypes[petSize];
char *petNames[petSize];
char *petBirths[petSize];

int main() {
    init();

    insertPersonInfos(0, "Yuri", "111.111.111-11", "27/12/2002", "1234567891-0", "Rua 3", 1650);
    insertPersonInfos(1, "Alex", "222.222.222-22", "01/09/2022", "1098765432-1", "Rua 4", 2500);
    insertPetInfos(0, 1, "Gato", "Nina", "25/10/2021");
    insertPetInfos(1, 1, "Cachorro", "Tusk", "20/11/2017");
    insertPetInfos(2, 1, "Passarinho", "Blue", "12/04/2022");
    insertPetInfos(3, 1, "Gato", "Pequeno", "15/03/2020");

    while(1) {
        showMenu();
        fflush(stdin);
        char c = (char) getc(stdin);

        switch(c) {
            case '1':
                showPersonMenu();
                break;
            case '2':
                showPetsMenu();
                break;
            case '0':
                finish();
                return 0;
            default:
                printf("\nOpcao invalida...");
        }
    }
}
