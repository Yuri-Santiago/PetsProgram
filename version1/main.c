#include <stdio.h>

#include "person.h"
#include "pets.h"
#include "utils.h"

// Person Data
int personCodes[size];
char personNames[size][255];
char personCPFs[size][15];
char personBirths[size][11];

// Pets Data
int petCodes[petSize];
int petPersonCodes[petSize];
char petTypes[petSize][20];
char petNames[petSize][255];
char petBirths[petSize][11];

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
            c = (char) getc(stdin);
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

// TODO: update pets with same number
