#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "person.h"
#include "pets.h"

extern struct person *start;
extern struct pet *petStart;

extern enum bool unsavedData;
extern enum bool unloadedData;

enum bool {
    false, true
};

enum codeIndex {
    Person, Pet
};

enum info {
    InfoCPF, InfoRG
};

enum optionsPerson {
    FinishPerson, InsertPerson, UpdatePerson, DeletePerson, ShowPersonCode, ShowPersonType, ShowAllPersons
};

enum optionsPets {
    FinishPets, InsertPet, UpdatePets, DeletePet, ShowPetCode, ShowPetPersonCode, ShowAllPets
};

enum bool checkUnloaded();
void setUnsavedData();

void init();
void finish();

void showMenu();
void showPersonMenu();
void showPetsMenu();
void showPetTypeMenu();

void trimStr(char *str);
void formatName(char *name);

enum bool searchDuplicate(enum info i, const char *info);

void inputString(char* message, char* str, int count, enum bool(*verify)(const char*), enum bool isUpdate);
enum bool verifyCPF(const char *cpf);
enum bool verifyBirth(const char *birth);
enum bool verifyRG(const char *rg);
enum bool verifyIncome(const char *income);
enum bool verifyIsEmpty(const char *str);
enum bool notVerify(const char *str);

void saveData();
void loadData();

void createPersonFile();
void createPetFile();
void createKeysFile();
void readKeys(uint64_t *keys);
void updateKeys(uint64_t *keys);

uint64_t inputCode(char *str);
uint64_t getPersonCode();
uint64_t getPetCode();
uint64_t getCode(enum codeIndex c);
#endif //UTILS_H
