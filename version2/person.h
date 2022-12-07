#ifndef PERSON_H
#define PERSON_H

#define stringMax 100
#define cpfMax 15
#define birthMax 11
#define rgMax 13

#include "pets.h"
#include "utils.h"

extern struct person *start;

struct person {
    uint64_t code;
    char name[stringMax];
    char cpf[cpfMax];
    char birth[birthMax];
    char rg[rgMax];
    char address[stringMax];
    uint64_t income;
    struct person *next;
};

void insertPerson();
void addPersonToList(struct person *p);

void updatePerson();

void deletePerson();
void removePersonFromList(struct person *p);

void showPersonByCode();
void showPersonsByPetType();
void showAllPersons();
void showPerson(struct person *p, int num);

struct person *searchPersonByCode(uint64_t code);

void addPersonFromFile(struct person *p, struct person **last);
void savePerson();
void loadPerson();
#endif //PERSON_H
