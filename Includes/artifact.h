#ifndef ARTIFACT_H
#define ARTIFACT_H
#define ARTSMALLFIELDSIZE 128
#define ARTMIDFIELDSIZE  750
#define ARTLARGEFIELDSIZE 2000
typedef enum artifactindex {
	
	ARTPIECE=1;
	JOURNAL=2;


}artifactindex;

typedef enum artpieceindex {
	PHRASE=1;
	TEXT=2;
	MUSICTRACK=3;
	MUSICALBUM=4;
	

}artpieceindex;

typedef struct musictrack{

	char title[ARTSMALLFIELDSIZE+1],genre[ARTSMALLFIELDSIZE+1],desc[ARTLARGEFIELDSIZE+1];


}musictrack;
typedef struct text{

	
	char title[ARTSMALLFIELDSIZE+1],desc[ARTLARGEFIELDSIZE+1];


}text;
typedef struct phrase{

	
	char desc[ARTMIDFIELDSIZE+1];


}phrase;
typedef struct musicalbum{
	
	u_int64_t numOfTracks;
	DListWComp* trackList;

}musicalbum;

typedef struct journal{
	u_int64_t numOfTexts;
	DListWComp* textList;
	
}journal;










typedef union untypedartpiece{
	musictrack track;
	musicalbum album;
	text composition;
	phrase quote;
}untypedartpiece;

typedef union untypedartifact{

	artpiece artobject;
	journal diary;

}untypedartifact;














typedef struct artpiece{
	
	artpieceindex type;
	untypedartpiece contents;

}artpiece;

typedef struct artifact{
	artifactindex type;
	untypedartifact object;

}
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

extern comparator artCompare;

static journal* parseJournal(FILE* stream){

	journal* result=malloc(sizeof(artifact));
	memset(result,0,sizeof(artifact));
	int numOfTexts=0;
	result->textList=initDListComp(sizeof(artifact),&artCompare);
	fscanf(stream, "%lu",&numOfTexts);
	result.numOfTexts=numOfTexts;
	for(;numOfTexts;numOfTexts--){
		text* newText=parseText(stream);
		addElemToListComp2(result->textList,(void*)newText);
		free(newText);

	}
	return result;

}
static text* parseText(FILE* stream){

		text* newText= malloc(sizeof(artifact));
		memset(newText->title,0,ARTSMALLFIELDSIZE+1);
		memset(newText->desc,0,ARTLARGEFIELDSIZE+1);
		fscanf(stream,"%[^;];%[^;];",newText->title,newText->desc);
		return newText;

}

static phrase* parsePhrase(FILE* stream){

		text* newPhrase= malloc(sizeof(artifact));
		memset(newPhrase->desc,0,ARTMIDFIELDSIZE+1);
		fscanf(stream,"%[^;];",newPhrase->desc);
		return newPhrase;

}
static musicalbum* parseAlbum(FILE* stream){

	musicalbum* result=malloc(sizeof(artifact));
	memset(result,0,sizeof(artifact));
	int numOfArtifacts=0;
	result.trackList=initDListComp(sizeof(artifact),&artCompare);
	fscanf(stream, "%lu",&numOfArtifacts);
	result.numOfTexts=numOfArtifacts;
	for(;numOfArtifacts;numOfArtifacts--){
		musictrack* newTrack=parseTrack(stream);
		addElemToListComp2(result.trackList,(void*)newTrack);
		free(musictrack);

	}
	return result;

}
static musictrack* parseTrack(FILE* stream){

		musictrack* newTrack= malloc(sizeof(artifact));
		memset(newTrack->title,0,ARTSMALLFIELDSIZE+1);
		memset(newTrack->genre,0,ARTSMALLFIELDSIZE+1);
		memset(newTrack->desc,0,ARTLARGEFIELDSIZE+1);
		fscanf(stream,"%[^;];%[^;];%[^;];",newTrack->title,newTrack->genre,newTrack->desc);
		return newTrack;

}

/*Falta:
	(FAZER ISTO TUDO NO HEADER PRIMEIRO PARA SER MAIS FACIL. DEPOIS DEIXAR CABEÇALHOS PARA TRAS
	ASSIM COMO DECLARACOES. METER FUNCOES ESTATICAS NO FICHEIRO '.c'. Ai de mim daqui a uns
	tempos...)
	
	funcao para triar entre o tipo de artefacto (objeto artistico vs journal).
	vai ter um switch que vai receber o inteiro vindo deste funcao assim como a stream.
	la, se for journal, vai direto para a funcao parseJournal.
	Se for objeto artistico, vai para uma funcao de parsing de objetos artisticos
	em que lhe e passado o tipo de objeto artistico com scanf na stream
	que tem um switch que seleciona o parsing efetuado com base no 
	tipo de objeto artistico. Isso e enfiado num buffer criado com malloc, escrito na arvore
	depois siga proximo.


*/
BSTreeComp* genArtifactTreeFromStream(FILE* stream){

	BSTreeComp* tree= initBSTreeComp(sizeof(artifact),artCompare);
	u_int64_t numOfArtifacts=0;
	fscanf(stream,"%lu",&numOfArtifacts);
	for(;numOfArtifacts;numOfArtifacts--){
		artifact* obj= malloc(sizeof(artifact));
		scanf(stream,"%d",&obj->type);
		


	}


}

#endif
