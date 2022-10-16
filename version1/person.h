#ifndef PERSON_H
#define PERSON_H

#define size 30
#define nameMax 255
#define cpfMax 15
#define birthMax 11
#define rgMax 13

// Person Data
extern int personCodes[size];
extern char *personNames[size];
extern char *personCPFs[size];
extern char *personBirths[size];
extern char *personRGs[size];
extern char *personAdresses[size];
extern unsigned long personIncomes[size];

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
void insertPersonInfos(int index, char *name, char *cpf, char *birth, char *rg, char *address, unsigned long income);
void deletePersonInfos(int index);
int verifyCPF(char *cpf);
int verifyRG(char *rg);
void showPerson(int index);
void showPersonPetType(char *type);
int isIntInList(int i, const int list[]);

#endif //PERSON_H
