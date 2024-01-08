#ifndef CARD_H
#define CARD_H
#define CARDSMALLFIELDSIZE 128
#define CARDLARGEFIELDSIZE 5000
typedef struct card{

char name[CARDSMALLFIELDSIZE+1],type[CARDSMALLFIELDSIZE+1],build[CARDLARGEFIELDSIZE+1],desc[CARDLARGEFIELDSIZE+1];
u_int64_t age,weight,height;

}card;

int compareCards(void* arg1,void* arg2);
card* initCard(char name[CARDSMALLFIELDSIZE],char type[CARDSMALLFIELDSIZE], char build[CARDLARGEFIELDSIZE], char desc[CARDLARGEFIELDSIZE],u_int64_t age, u_int64_t weight, u_int64_t height);
card* initRandCard(void);
char* printPrettyCard(card* collectible);
card* fscanCard(FILE*fstream);
void fprintCard(card* collectible,FILE* fstream);

void destroyCard(card** collectible);

extern comparator cardCmp;

#endif
