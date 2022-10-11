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
char *petTypes[petSize]; // 20
char *petNames[petSize]; // 255
char *petBirths[petSize]; // 11

int main() {
    init();

    insertPersonInfos(0, "Yuri", "077.183.053-09", "27/12/2002", "123456789", "Rua 3", 1650);
    insertPersonInfos(1, "Raquel", "000.000.000-00", "15/09/2022", "123456789", "Rua 3", 2500);
    insertPetInfos(0, 1, "Gato", "Nina", "25/10/2021");
    insertPetInfos(1, 1, "Cachorro", "Tusk", "20/11/2017");
    insertPetInfos(2, 1, "Passarinho", "Bot", "25/10/2021");

    while(1) {
        showMenu();
        char c = (char) getc(stdin);
        getchar();

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
                printf("Opcao invalida...\n");
        }
    }
}
