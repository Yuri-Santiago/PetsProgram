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
int searchPetByCode(int *, int *, int *);
void insertPetInfos(int, int, char *, char *, char *);
void updatePetInfos(int, int, int, char *, char *, char *);
void deletePetInfos(int);
int getPetCode(int);
char *choosePetType();
int verifyPetName(char *, int);
void showPet(int);

#endif //PETS_H
