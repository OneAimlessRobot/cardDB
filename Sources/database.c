#include "../Includes/preprocessor.h"
#include "../Includes/comparator.h"
#include "../Includes/nodes.h"
#include "../Includes/doublelist.h"
#include "../Includes/stackList.h"
#include "../Includes/BSTcomp.h"
#include "../Includes/card.h"
#include "../Includes/treeIt.h"
#include "../Includes/database.h"
/*

BSTreeComp* initBSTreeComp(u_int64_t elemSize,comparator*comp);


void addToBSTreeComp(BSTreeComp* tree,void* elem);

void removeFromBSTreeComp(BSTreeComp* tree,void* elem);

void destroyBSTreeComp(BSTreeComp* tree);

void* findInBSTreeComp(BSTreeComp* tree, void* data);


void printIntBSTreeBreadthComp(BSTreeComp*tree);

void printIntBSTreeDepthComp(BSTreeComp*tree);

void printIntBSTreeInfixComp(BSTreeComp*tree);

void printBSTreePrettyComp(BSTreeComp*tree);

BSTreeComp* makeIntTreeComp(int arr[],int arrSize,comparator*comp);






typedef struct carddatabase{

char* filepath;
u_int64_t numOfCards;
int fd;
BSTreeComp* storage;
}carddatabase;




typedef struct treeIt{

stackList* stack;
BSTreeComp* tree;


}treeIt;

void* nextTreeItComp(treeIt* it);

treeIt* initTreeItComp(BSTreeComp* tree);

int hasNextTreeItComp(treeIt*it);

void rewindTreeItComp(treeIt*it);


void destroyTreeIt(treeIt* it);





*/
carddatabase* initDataBase(char* filepath){
	
	carddatabase* result= malloc(sizeof(carddatabase));
	memset(result,0,sizeof(carddatabase));
	result->storage= initBSTreeComp(sizeof(card),&cardCmp);
	FILE* stream= fopen(filepath,"r");
	if(!stream){
		destroyBSTreeComp(result->storage);
		result->storage=NULL;
		free(result);
		result=NULL;
		return result;
		
	}
	int numOfCards=0;
	fscanf(stream,"%d",&numOfCards);
	result->numOfCards=numOfCards;
	for(;numOfCards;numOfCards--){
		card* readCard= fscanCard(stream);
		addToBSTreeComp(result->storage,readCard);
		free(readCard);
	}
	fclose(stream);
	return result;


}
void addCardToDataBase(carddatabase* db,card* collectible){

	if(collectible){
	card* found=(card*)findInBSTreeComp(db->storage, collectible);
	if(!found){
	addToBSTreeComp(db->storage,(void*)collectible);
	db->numOfCards++;
	}
	else{
		fprintf(stdout,"Carta ja existe!!!!\n");
	}
	}


}

void remCardFromDataBase(carddatabase* db,char name[CARDSMALLFIELDSIZE]){
	
	card tmp= {{0},{0},{0},{0},0,0,0,{0},NULL};
	memcpy(tmp.name,name,CARDSMALLFIELDSIZE);
	u_int64_t size=db->storage->currSize;
	card* found=(card*)findInBSTreeComp(db->storage,&tmp);
	destroyArtifactTree(found->actualArts);
	removeFromBSTreeComp(db->storage,(void*)&tmp);
	if(db->storage->currSize!=size){
	db->numOfCards--;
	}

}


void printDataBase(carddatabase* db){


	treeIt* it= initTreeItComp(db->storage);
	while(hasNextTreeItComp(it)){
		
		void* nextElem= nextTreeItComp(it);
		char* strCard=printPrettyCard((card*)nextElem);
		printf("%s\n",strCard);
		free(strCard);
	}
	destroyTreeIt(it);
	

}
void printDataBaseLess(carddatabase* db){


	treeIt* it= initTreeItComp(db->storage);
	while(hasNextTreeItComp(it)){
		
		card* nextElem=(card*) nextTreeItComp(it);
		printf("%s\n",(card*)nextElem->name);
	}
	destroyTreeIt(it);
	

}


void printCardArt(carddatabase* db,char name[CARDSMALLFIELDSIZE]){

	card tmp= {{0},{0},{0},{0},0,0,0,{0},NULL};
	memcpy(tmp.name,name,CARDSMALLFIELDSIZE);
	card* found=(card*)findInBSTreeComp(db->storage, &tmp);
	if(!found){
		printf("No such card!!! %s N existe\n",tmp.name);
		return;
	}
	printArtifactTreePretty(stdout,found->actualArts);


}
void printDataBaseCard(carddatabase* db,char name[CARDSMALLFIELDSIZE]){

	card tmp= {{0},{0},{0},{0},0,0,0,{0},NULL};
	memcpy(tmp.name,name,CARDSMALLFIELDSIZE);
	card* found=(card*)findInBSTreeComp(db->storage, &tmp);
	if(!found){
		printf("No such card!!! %s N existe\n",tmp.name);
		return;
	}
	char* strCard=printPrettyCard(found);
	printf("%s\n",strCard);
	free(strCard);


}

u_int64_t getDataBaseSize(carddatabase* db){

	return db->numOfCards;

}

void saveDataBase(carddatabase* db){

	int fdsave= open(CARDS_PATH,O_RDWR | O_CREAT | O_TRUNC,0777);
	FILE* saveDb= fdopen(fdsave,"w+");
	if(!saveDb||fdsave==-1){
		close(fdsave);
		perror("Ficheiro nao aberto ao salvar base de dados!!!\n");
		exit(-1);
	}
	u_int64_t numOfCards= db->numOfCards;
	fprintf(saveDb,"%lu\n\n",numOfCards);
	if(db->storage->currSize){
	treeIt* it= initTreeItComp(db->storage);
	while(hasNextTreeItComp(it)){
		
		void* nextElem= nextTreeItComp(it);
		fprintCard((card*)nextElem,saveDb);
	}
	destroyTreeIt(it);
	}
	fclose(saveDb);
	

}

void destroyDataBase(carddatabase* db){

	if(db){
	if(db->storage->currSize){
	treeIt* it= initTreeItComp(db->storage);
	while(hasNextTreeItComp(it)){
		
		card* nextElem=(card*) nextTreeItComp(it);
		destroyArtifactTree(nextElem->actualArts);
		nextElem->actualArts=NULL;
	}
	destroyTreeIt(it);
	}
	destroyBSTreeComp(db->storage);
	free(db);
	}

}

void editCardArt(carddatabase* db,char name[CARDSMALLFIELDSIZE]){

	card tmp= {{0},{0},{0},{0},0,0,0,{0},NULL};
	memcpy(tmp.name,name,CARDSMALLFIELDSIZE);
	card* found=(card*)findInBSTreeComp(db->storage, &tmp);
	if(!found){
		printf("No such card!!! %s N existe\n",tmp.name);
		return;
	}
	char cmd[1024]={0};
	char* ptr= cmd;
	ptr+=snprintf(ptr,1024,"nano %s",found->artfilepath);
	fprintf(stdout,"Carrega enter para editares as artes. Lembra-te de respeitar o formato!!!\n");
	fscanf(stdout,"\n");
	system(cmd);
	destroyArtifactTree(found->actualArts);
	FILE* fstream= fopen(found->artfilepath,"r");
	found->actualArts=genArtifactTreeFromStream(fstream);
	fclose(fstream);



}
