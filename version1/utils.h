#ifndef UTILS_H
#define UTILS_H

void init();
void finish();
void showMenu();
void showPersonMenu();
void showPetsMenu();
void showPetTypeMenu();
int verifyBirth(char *birth);
void strToUpper(char *str);
void readString(char *str, int count);
char *allocateString(char *str);

#endif //UTILS_H
