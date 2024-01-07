#ifndef DATABASE_H
#define DATABASE_H
typedef struct carddatabase{

char* filepath;
u_int64_t numOfCards;
int fd;
BSTreeComp* storage;
}carddatabase;

carddatabase* initDataBase(char* filepath);

void addCardToDataBase(carddatabase* db,card* collectible);


void remCardFromDataBase(carddatabase* db,char name[CARDSMALLFIELDSIZE]);


void printDataBase(carddatabase* db);


void printDataBaseCard(carddatabase* db,char name[CARDSMALLFIELDSIZE]);

u_int64_t getDataBaseSize(carddatabase* db);

void saveDataBase(carddatabase* db);

void destroyDataBase(carddatabase* db);

#endif
