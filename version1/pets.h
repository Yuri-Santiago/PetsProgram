#ifndef PETS_H
#define PETS_H

#define petSize 150
#define petTypeMax 20

// Pets Data
extern int petCodes[petSize];
extern int petPersonCodes[petSize];
extern char *petTypes[petSize];
extern char *petNames[petSize];
extern char *petBirths[petSize];

// Pet CRUD
void insertPet();
void updatePet();
void deletePet();
void showPetByCode();
void showPetByPersonCode();
void showAllPetsInOrder();

// Pet utils
int searchEmptyPet();
int searchPetByCode(int *index, int *petCode, int *personCode);
void insertPetInfos(int index, int personCode, char *type, char *name, char *birth);
void updatePetInfos(int index, int petCode, int personCode, char *type, char *name, char *birth);
void deletePetInfos(int index);
int getPetCode(int personCode);
char *choosePetType();
int verifyPetName(char *name, int personCode);
void showPet(int index);

#endif //PETS_H
