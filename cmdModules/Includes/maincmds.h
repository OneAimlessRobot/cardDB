#ifndef MAINCMDS_H
#define MAINCMDS_H
void sair(int64_t argc,int* toExit, void** argv);

void load(int64_t argc,int* toExit, void** argv);

void showallcmds(int64_t argc,int* toExit, void** argv);

void save(int64_t argc,int* toExit, void** argv);

void printcard(int64_t argc,int* toExit, void** argv);

void addcard(int64_t argc,int* toExit, void** argv);

void addrand(int64_t argc,int* toExit, void** argv);

void addrands(int64_t argc,int* toExit, void** argv);

void remcard(int64_t argc,int* toExit, void** argv);

void printcards(int64_t argc,int* toExit, void** argv);

void printsize(int64_t argc,int* toExit, void** argv);


extern cmdstruct maincmds[];

#endif
