#include "../Includes/preprocessor.h"
#include "../Includes/nodes.h"
#include "../Includes/comparator.h"
#include "../Includes/doublelist.h"
#include "../Includes/doublelistcomp.h"
#include "../Includes/stackList.h"
#include "../Includes/queueList.h"
#include "../Includes/dliterator.h"
#include "../Includes/BSTcomp.h"
#include "../Includes/treeIt.h"
#include "../Includes/card.h"
#include "../Includes/artifact.h"
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

*/
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





















typedef struct DListWComp{

DList head,trail;
u_int64_t currSize,elemSize;
comparator*comp;
}DListWComp;


DListWComp* initDListComp(u_int64_t elemSize,comparator*comp);

void addElemToList2(DListWComp* list,void* data,u_int64_t index);

void addElemToListComp2(DListWComp* list,void* data);

void remElemFromListComp2(DListWComp* list,void* data);

void remElemFromList2(DListWComp* list,u_int64_t index);


void* findElemListCompComp(DListWComp* list,void* data);


void* getElemAtIndexComp(DListWComp*list,u_int64_t index);

DListWComp* makeIntListComp(int arr[],int size,comparator*comp);

void printIntListComp(DListWComp* list);

void printIntListBackComp(DListWComp* list);

void destroyDListComp(DListWComp* list);

*/
int compareArtifacts(void* arg1,void* arg2){
	artifact* art1=(artifact*)arg1;
	artifact* art2=(artifact*)arg2;
	return memcmp(art1,art2,sizeof(artifact));

}
comparator artCompare={compareArtifacts};

static phrase parsePhrase(FILE* stream){

		phrase newPhrase;
		memset(&newPhrase,0,sizeof(phrase));
		char *desc;
		memset(desc=newPhrase.desc,0,ARTMIDFIELDSIZE+1);
		fscanf(stream,"%[^;];",desc);
		return newPhrase;

}

static text parseText(FILE* stream){

		text newText;
		memset(&newText,0,sizeof(text));
		memset(newText.title,0,ARTMIDFIELDSIZE+1);
		memset(newText.desc,0,ARTLARGEFIELDSIZE+1);
		fscanf(stream,"%[^;];%[^;];",newText.title,newText.desc);
		return newText;

}

static journal parseJournal(FILE* stream){

	journal result;
	memset(&result,0,sizeof(journal));
	u_int64_t numOfTexts=0;
	result.textList=initDListComp(sizeof(artifact),&artCompare);
	fscanf(stream, "%lu",&numOfTexts);
	memset(result.intro,0,ARTLARGEFIELDSIZE+1);
	fscanf(stream, "%[^;];",result.intro);
	result.numOfTexts=numOfTexts;
	for(;numOfTexts;numOfTexts--){
		text newText=parseText(stream);
		addElemToListComp2(result.textList,(void*)&newText);
		

	}
	return result;

}
static musictrack parseTrack(FILE* stream){

		musictrack newTrack;
		memset(&newTrack,0,sizeof(musictrack));
		char* title,*genre,*desc;
		memset(title=newTrack.title,0,ARTMIDFIELDSIZE+1);
		memset(genre=newTrack.genre,0,ARTMIDFIELDSIZE+1);
		memset(desc=newTrack.desc,0,ARTLARGEFIELDSIZE+1);
		fscanf(stream,"%[^;];%[^;];%[^;];",title,genre,desc);
		return newTrack;

}
static musicalbum parseAlbum(FILE* stream){

	musicalbum result;
	memset(&result,0,sizeof(musicalbum));
	u_int64_t numOfArtifacts=0;
	result.trackList=initDListComp(sizeof(artifact),&artCompare);
	fscanf(stream, "%lu",&numOfArtifacts);
	memset(result.title,0,ARTMIDFIELDSIZE+1);
	fscanf(stream, "%[^;];",result.title);
	result.numOfTracks=numOfArtifacts;
	for(;numOfArtifacts;numOfArtifacts--){
		musictrack newTrack=parseTrack(stream);
		addElemToListComp2(result.trackList,(void*)&newTrack);
		
	}
	return result;

}

static void printTrack(FILE* stream,musictrack* track){

		fprintf(stream,"%s;\n%s;\n%s;\n",track->title,track->genre,track->desc);
		
}
static void printAlbum(FILE* stream,musicalbum* album){

	fprintf(stream, "%lu\n",album->trackList->currSize);
	fprintf(stream, "%s;\n",album->title);
	dliteratorcomp* it= initItComp(album->trackList);
	while(hasNextItComp(it)){
		musictrack* track=nextItComp(it);
		printTrack(stream,track);
		

	}
	free(it);
}
static void printText(FILE* stream,text* comp){

		fprintf(stream,"%s;\n%s;\n",comp->title,comp->desc);
		
}
static void printJournal(FILE* stream,journal* diary){

	fprintf(stream, "%lu\n",diary->textList->currSize);
	fprintf(stream, "%s;\n",diary->intro);
	dliteratorcomp* it= initItComp(diary->textList);
	while(hasNextItComp(it)){
		text* txt=nextItComp(it);
		printText(stream,txt);
		

	}
	free(it);

}
static void printPhrase(FILE* stream,phrase* phr){

		fprintf(stream,"%s;\n",phr->desc);
		
}

static void printArtpiece(FILE* stream,artpiece* artobj){
	
	fprintf(stream,"%d\n",artobj->type);
	switch(artobj->type){
		
		case PHRASE:
		printPhrase(stream,&artobj->contents.quote);
		break;
		case TEXT:
		printText(stream,&artobj->contents.composition);
		break;
		case MUSICTRACK:
		printTrack(stream,&artobj->contents.track);
		break;
		case MUSICALBUM:
		printAlbum(stream,&artobj->contents.album);
		break;
		default:
		break;


	}


}

void printArtifact(FILE* stream,artifact* obj){
	fprintf(stream,"%d\n",obj->type);
	switch(obj->type){
		
		case JOURNAL:
		printJournal(stream,&obj->object.diary);
		break;
		case ARTPIECE:
		printArtpiece(stream,&obj->object.artobject);
		break;
		default:
		break;
		


	}


}
/*Falta:
	(FAZER ISTO TUDO NO HEADER PRIMEIRO PARA SER MAIS FACIL. DEPOIS DEIXAR CABEÇALHOS PARA TRAS
	ASSIM COMO DECLARACOES. METER FUNCOES ESTATICAS NO FICHEIRO '.c'. Ai de mim daqui a uns
	tempos...)
	
	funcao para triar entre o tipo de artefacto (objeto artistico vs journal).
	vai ter um switch que vai receber o inteiro vindo deste funcao assim como a stream.
	la, se for journal, vai direto para a funcao parseJournal.
	Se for objeto artistico, vai para uma...

	funcao de parsing de objetos artisticos
	em que lhe e passado o tipo de objeto artistico com scanf na stream
	que tem um switch que seleciona o parsing efetuado com base no
	tipo de objeto artistico.

	Isso e enfiado num buffer criado com malloc, escrito na arvore
	depois siga proximo.


*/
static artpiece parseArtpiece(FILE* stream){
	/*
		
	
	PHRASE=1;
	TEXT=2;
	MUSICTRACK=3;
	MUSICALBUM=4;
	
	
	
	
	*/
	artpiece artobj;
	memset(&artobj,0,sizeof(artpiece));
	fscanf(stream,"%d",&artobj.type);
	switch(artobj.type){
		
		case PHRASE:
		artobj.contents.quote=parsePhrase(stream);
		break;
		case TEXT:
		artobj.contents.composition=parseText(stream);
		break;
		case MUSICTRACK:
		artobj.contents.track=parseTrack(stream);
		break;
		case MUSICALBUM:
		artobj.contents.album=parseAlbum(stream);
		break;
		default:
		break;


	}
	return artobj;


}

static artifact genArtifactFromStream(FILE* stream){
		
	artifact obj;
	memset(&obj,0,sizeof(artifact));
	fscanf(stream,"%d",&obj.type);
	int i=obj.type;
	switch(i){
		case JOURNAL:
		obj.object.diary=parseJournal(stream);
		break;
		case ARTPIECE:
		obj.object.artobject=parseArtpiece(stream);
		break;
		default:
		break;


	}
	return obj;

}
//void addToBSTreeComp(BSTreeComp* tree,void* elem);
BSTreeComp* genArtifactTreeFromStream(FILE* stream){

	BSTreeComp* tree= initBSTreeComp(sizeof(artifact),&artCompare);
	u_int64_t numOfArtifacts=0;
	fscanf(stream,"%lu",&numOfArtifacts);
	for(;numOfArtifacts;numOfArtifacts--){
		artifact obj=genArtifactFromStream(stream);
		addToBSTreeComp(tree,(void*)&obj);

	}

	return tree;
}
void printArtifactTree(FILE*stream,BSTreeComp* tree){

	fprintf(stream,"%lu\n",tree->currSize);
	treeIt* it= initTreeItComp(tree);
	while(hasNextTreeItComp(it)){
		
		artifact* nextElem= (artifact*)nextTreeItComp(it);
		printArtifact(stream,nextElem);
	}
	destroyTreeIt(it);
}

void destroyArtifactTree(BSTreeComp* tree){

	if(tree->currSize){
	treeIt* it= initTreeItComp(tree);
	
	while(hasNextTreeItComp(it)){
		
		artifact* nextElem= (artifact*)nextTreeItComp(it);
		switch(nextElem->type){
			case JOURNAL:
				destroyDListComp(nextElem->object.diary.textList);
			break;
			case ARTPIECE:
				switch(nextElem->object.artobject.type){
					case MUSICALBUM:
				destroyDListComp(nextElem->object.artobject.contents.album.trackList);
					break;
					default:
					break;
				}
			break;
			default:
			break;
		
		}
	}
	destroyTreeIt(it);
	}
	destroyBSTreeComp(tree);
}


