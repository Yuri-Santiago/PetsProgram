#ifndef PETSPROGRAM_PETS_H
#define PETSPROGRAM_PETS_H

#define petSize 150

// Pets Data
extern int petCodes[petSize];
extern int petPersonCodes[petSize];
extern char petTypes[petSize][20];
extern char petNames[petSize][255];
extern char petBirths[petSize][11];

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
void insertPetInfos(int index, int personCode, char type[], char name[], char birth[]);
void updatePetInfos(int index, int petCode, int personCode, char type[], char name[], char birth[]);
int getPetCode(int personCode);
void choosePetType(char type[]);
int verifyPetName(char name[], int personCode);
void showPet(int index);

#endif //PETSPROGRAM_PETS_H
