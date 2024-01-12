#include "../Includes/preprocessor.h"
#include "../Includes/auxFuncs.h"
#include "../Includes/comparator.h"
#include "../Includes/card.h"
/*typedef struct card{

char name[CARDSMALLFIELDSIZE+1],type[CARDSMALLFIELDSIZE+1],build[CARDLARGEFIELDSIZE+1],desc[CARDLARGEFIELDSIZE+1];
u_int64_t age,weight,height;

}card;
*/

int compareCards(void* arg1,void* arg2){
	card* card1= (card*) arg1;
	card* card2= (card*) arg2;
	
	return memcmp(card1->name,card2->name,CARDSMALLFIELDSIZE);


}

comparator cardCmp={compareCards};

card* initCard(char name[CARDSMALLFIELDSIZE],char type[CARDSMALLFIELDSIZE], char build[CARDLARGEFIELDSIZE], char desc[CARDLARGEFIELDSIZE],u_int64_t age, u_int64_t weight, u_int64_t height){

	card* result= malloc(sizeof(card));
	memset(result->name,0,CARDSMALLFIELDSIZE+1);
	memcpy(result->name,name,CARDSMALLFIELDSIZE);
	memset(result->type,0,CARDSMALLFIELDSIZE+1);
	memcpy(result->type,type,CARDSMALLFIELDSIZE);
	memset(result->build,0,CARDLARGEFIELDSIZE+1);
	memcpy(result->build,build,CARDLARGEFIELDSIZE);
	memset(result->desc,0,CARDLARGEFIELDSIZE+1);
	memcpy(result->desc,desc,CARDLARGEFIELDSIZE);
	result->age=age;
	result->weight=weight;
	result->height=height;
	return result;


}
card* initRandCard(void){

	card* result= malloc(sizeof(card));
	char* randName= randStr(CARDSMALLFIELDSIZE);
	memcpy(result->name,randName,CARDSMALLFIELDSIZE);
	free(randName);
	char* randType= randStr(CARDSMALLFIELDSIZE);
	memcpy(result->type,randType,CARDSMALLFIELDSIZE);
	free(randType);
	char* randBuild= randStr(CARDLARGEFIELDSIZE);
	memcpy(result->build,randBuild,CARDLARGEFIELDSIZE);
	free(randBuild);
	char* randDesc= randStr(CARDLARGEFIELDSIZE);
	memcpy(result->desc,randDesc,CARDLARGEFIELDSIZE);
	free(randDesc);
	result->age=genRandInt(0,10000);
	result->weight=genRandInt(0,10000);
	result->height=genRandInt(0,10000);
	return result;


}

static card* initEmptyCard(void){
	card* result= malloc(sizeof(card));
	memset(result->name,0,CARDSMALLFIELDSIZE+1);
	memset(result->type,0,CARDSMALLFIELDSIZE+1);
	memset(result->build,0,CARDLARGEFIELDSIZE+1);
	memset(result->desc,0,CARDLARGEFIELDSIZE+1);
	memset(result->artfilepath,0,CARDMIDFIELDSIZE+1);
	return result;


}



char* printPrettyCard(card* collectible){

	u_int64_t cardStrSize=(CARDSMALLFIELDSIZE+2+100)*2+(CARDLARGEFIELDSIZE+2+100)*2+(100+100+10+1)*3;
	char* result= malloc(cardStrSize);
	char* ptr= result;
	memset(result,0,cardStrSize);
	ptr+=snprintf(ptr,(CARDSMALLFIELDSIZE+2+100)*2,"Name: %s\nType: %s\n",collectible->name,collectible->type);
	ptr+=snprintf(ptr,(100+100+1+10)*3,"Age: %lu years\nHeight: %lucm\nWeight: %lukg\n",collectible->age,collectible->height,collectible->weight);
	ptr+=snprintf(ptr,(CARDLARGEFIELDSIZE+2+100)*2,"Build: %s\nDesc: %s\n",collectible->build,collectible->desc);
	return result;

}


card* fscanCard(FILE* fstream){

	card* result= initEmptyCard();
	/*fscanf(fstream,"%lu%lu%lu%s%s%s%s",&result->age,&result->weight,&result->height,result->name,result->type,result->build,result->desc);
	removeUnderscoreChars(result->name,CARDSMALLFIELDSIZE);
	removeUnderscoreChars(result->type,CARDSMALLFIELDSIZE);
	removeUnderscoreChars(result->build,CARDLARGEFIELDSIZE);
	removeUnderscoreChars(result->desc,CARDLARGEFIELDSIZE);
	*/
	fscanf(fstream,"%lu%lu%lu%lu\n%[^;];\n%[^;];\n%[^;];\n%[^;];\n%[^;];\n",&result->numOfArts,&result->age,&result->weight,&result->height,result->name,result->type,result->build,result->desc,result->artfilepath);
	FILE* tstream= fopen(result->artfilepath,"r");
	result->actualArts=genArtifactTreeFromStream(tstream);
	fclose(tstream);
	return result;
	



}

void fprintCard(card* collectible,FILE* fstream){
	/*
	removeSpaceChars(collectible->name,CARDSMALLFIELDSIZE);
	removeSpaceChars(collectible->type,CARDSMALLFIELDSIZE);
	removeSpaceChars(collectible->build,CARDLARGEFIELDSIZE);
	removeSpaceChars(collectible->desc,CARDLARGEFIELDSIZE);
	fprintf(fstream,"%lu\n%lu\n%lu\n%s\n%s\n%s\n%s\n",collectible->age,collectible->weight,collectible->height,collectible->name,collectible->type,collectible->build,collectible->desc);
	*/
	fprintf(fstream,"%lu\n%lu\n%lu\n%lu\n%s;\n%s;\n%s;\n%s;\n%s;\n",collectible->numOfArts,collectible->age,collectible->weight,collectible->height,collectible->name,collectible->type,collectible->build,collectible->desc,collectible->artfilepath);
	
}
void destroyCard(card** collectible){

	free(*collectible);
	*collectible=NULL;

}

