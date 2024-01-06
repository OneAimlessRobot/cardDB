#ifndef DATABASE_H
#define DATABASE_H
typedef struct carddatabase{

char* filepath;
u_int64_t numOfCards;
int fd;
BSTreeComp* storage;
}carddatabase;

carddatabase* initDataBase(char* filepath);
#endif
