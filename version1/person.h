#ifndef PETSPROGRAM_PERSON_H
#define PETSPROGRAM_PERSON_H

#define size 30
#define nameMax 255
#define cpfMax 15
#define birthMax 11

// Person Data
extern int personCodes[size];
extern char *personNames[size];
extern char *personCPFs[size];
extern char *personBirths[size];

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
void insertPersonInfos(int, char *, char *, char *);
void deletePersonInfos(int);
int verifyCPF(char *);
void showPerson(int);
void showPersonPetType(char *);

#endif //PETSPROGRAM_PERSON_H
