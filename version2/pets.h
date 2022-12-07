#ifndef PETS_H
#define PETS_H

#include "person.h"
#include "utils.h"

struct person;
enum bool;

enum petTypes {
    Cachorro, Gato, Cobra, Passarinho
};

struct pet {
    uint64_t code;
    uint64_t personCode;
    enum petTypes type;
    char name[stringMax];
    char birth[birthMax];
    struct pet *next;
};

void insertPet();
void addPetToList(struct pet *pt);

void updatePet();

void deletePet();
void deletePetsByPerson(struct person *p);
void deletePetInfo(struct pet *pt);
void removePetFromList(struct pet *pt);

void showPetByCode();
void showPetByPersonCode();
void showAllPets();
void showPet(struct pet *pt, int num);

enum petTypes getPetType(enum bool isUpdate);
char *typeToString(enum petTypes type);
enum bool personHasPetType(uint64_t personCode, enum petTypes type);

enum bool verifyPetName(char *name, uint64_t personCode, enum bool isUpdate);

struct pet *searchPetByCode(uint64_t code);

void addPetFromFile(struct pet *pt, struct pet **last);
void savePet();
void loadPet();
#endif //PETS_H
