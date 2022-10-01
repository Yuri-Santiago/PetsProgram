#ifndef PETSPROGRAM_PERSON_H
#define PETSPROGRAM_PERSON_H

#define size 30

// Person Data
extern int personCodes[size];
extern char personNames[size][255];
extern char personCPFs[size][15];
extern char personBirths[size][11];

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

#endif //PETSPROGRAM_PERSON_H
