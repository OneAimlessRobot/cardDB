#ifndef CARD_H
#define CARD_H
#define CARDSMALLFIELDSIZE 128
#define CARDLARGEFIELDSIZE 4096
typedef struct card{

char name[CARDSMALLFIELDSIZE+1],type[CARDSMALLFIELDSIZE+1],build[CARDLARGEFIELDSIZE+1],desc[CARDLARGEFIELDSIZE+1];
u_int64_t age,weight,height;

}card;

card* initCard(char name[CARDSMALLFIELDSIZE],char type[CARDSMALLFIELDSIZE], char build[CARDLARGEFIELDSIZE], char desc[CARDLARGEFIELDSIZE],u_int64_t age, u_int64_t weight, u_int64_t height);
char* printPrettyCard(card* collectible);
card* destroyCard(card** collectible);
card* fscanCard(FILE* fstream);
card* fprintCard(card* collectible,FILE* fstream);

#endif
