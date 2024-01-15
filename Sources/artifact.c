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
static image parseImage(FILE* stream){


		image newImage;
		memset(&newImage,0,sizeof(image));
		char* title,*imageType,*desc;
		memset(title=newImage.title,0,ARTMIDFIELDSIZE+1);
		memset(imageType=newImage.imageType,0,ARTMIDFIELDSIZE+1);
		memset(desc=newImage.desc,0,ARTLARGEFIELDSIZE+1);
		fscanf(stream,"%[^;];%[^;];%[^;];",title,imageType,desc);
		return newImage;

}
static imagealbum parseImageAlbum(FILE* stream){

	imagealbum result;
	memset(&result,0,sizeof(imagealbum));
	u_int64_t numOfArtifacts=0;
	result.imgList=initDListComp(sizeof(artifact),&artCompare);
	fscanf(stream, "%lu",&numOfArtifacts);
	memset(result.title,0,ARTMIDFIELDSIZE+1);
	fscanf(stream, "%[^;];",result.title);
	result.numOfImages=numOfArtifacts;
	for(;numOfArtifacts;numOfArtifacts--){
		image newImage=parseImage(stream);
		addElemToListComp2(result.imgList,(void*)&newImage);
		
	}
	return result;


}
static skit parseSkit(FILE* stream){

		skit newSkit;
		memset(&newSkit,0,sizeof(skit));
		memset(newSkit.title,0,ARTMIDFIELDSIZE+1);
		memset(newSkit.desc,0,ARTLARGEFIELDSIZE+1);
		fscanf(stream,"%[^;];%[^;];",newSkit.title,newSkit.desc);
		return newSkit;

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


static void printImage(FILE* stream,image*img){

	fprintf(stream,"%s\n;%s;\n%s;\n",img->title,img->imageType,img->desc);


}

static void printImageAlbum(FILE* stream,imagealbum* imgalbum){


	fprintf(stream, "%lu\n",imgalbum->imgList->currSize);
	fprintf(stream, "%s;\n",imgalbum->title);
	dliteratorcomp* it= initItComp(imgalbum->imgList);
	while(hasNextItComp(it)){
		image* img=nextItComp(it);
		printImage(stream,img);
		

	}
	free(it);

}



static void printSkit(FILE* stream,skit* sk){



		fprintf(stream,"%s;\n%s;\n",sk->title,sk->desc);
		


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
		case IMAGEALBUM:
		printImageAlbum(stream,&artobj->contents.photoalbum);
		break;
		case IMAGE:
		printImage(stream,&artobj->contents.photo);
		break;
		case SKIT:
		printSkit(stream,&artobj->contents.scene);
		break;
		default:
		break;


	}


}

static void printArtifact(FILE* stream,artifact* obj){
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
static void printTrackPretty(FILE* stream,musictrack* track){

		fprintf(stream,"Track:\n Title:  %s\nGenre: %s\nDesc: %s\n",track->title,track->genre,track->desc);
		
}
static void printAlbumPretty(FILE* stream,musicalbum* album){

	fprintf(stream, "Album:\nTitle: %s\n\n",album->title);
	fprintf(stream, "Number of tracks: %lu\n",album->trackList->currSize);
	dliteratorcomp* it= initItComp(album->trackList);
	while(hasNextItComp(it)){
		musictrack* track=nextItComp(it);
		printTrackPretty(stream,track);
		

	}
	free(it);
}
static void printTextPretty(FILE* stream,text* comp){

		fprintf(stream,"Text:\nTitle: %s\nDesc: %s\n",comp->title,comp->desc);
		
}
static void printJournalPretty(FILE* stream,journal* diary){

	fprintf(stream, "Journal:\nIntro: %s\n\n",diary->intro);
	fprintf(stream, "Number of texts: %lu\n",diary->textList->currSize);
	dliteratorcomp* it= initItComp(diary->textList);
	while(hasNextItComp(it)){
		text* txt=nextItComp(it);
		printTextPretty(stream,txt);
		

	}
	free(it);

}
static void printPhrasePretty(FILE* stream,phrase* phr){

		fprintf(stream,"%s\n",phr->desc);
		
}


static void printImagePretty(FILE* stream,image*img){

	fprintf(stream,"Image: \nTitle: %s\nImage type: %s\nDesc: %s\n",img->title,img->imageType,img->desc);


}

static void printImageAlbumPretty(FILE* stream,imagealbum* imgalbum){


	fprintf(stream, "Image album:\nNum of images: %lu\n",imgalbum->imgList->currSize);
	fprintf(stream, "Title: %s\n",imgalbum->title);
	dliteratorcomp* it= initItComp(imgalbum->imgList);
	while(hasNextItComp(it)){
		image* img=nextItComp(it);
		printTrack(stream,img);
		

	}
	free(it);

}



static void printSkitPretty(FILE* stream,skit* sk){



		fprintf(stream,"Skit:\nTitle: %s\nDesc: %s\n",sk->title,sk->desc);
		


}

static void printArtpiecePretty(FILE* stream,artpiece* artobj){
	
	switch(artobj->type){
		
		case PHRASE:
		printPhrasePretty(stream,&artobj->contents.quote);
		break;
		case TEXT:
		printTextPretty(stream,&artobj->contents.composition);
		break;
		case MUSICTRACK:
		printTrackPretty(stream,&artobj->contents.track);
		break;
		case MUSICALBUM:
		printAlbumPretty(stream,&artobj->contents.album);
		break;
		case IMAGEALBUM:
		printImageAlbumPretty(stream,&artobj->contents.photoalbum);
		break;
		case IMAGE:
		printImagePretty(stream,&artobj->contents.photo);
		break;
		case SKIT:
		printSkitPretty(stream,&artobj->contents.scene);
		break;
		default:
		break;


	}


}
static void printArtifactPretty(FILE* stream,artifact* obj){
	switch(obj->type){
		
		case JOURNAL:
		fprintf(stream,"Type: Journal\n");
		printJournalPretty(stream,&obj->object.diary);
		break;
		case ARTPIECE:
		fprintf(stream,"Type: Piece of Art\n");
		printArtpiecePretty(stream,&obj->object.artobject);
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
		case IMAGE:
		artobj.contents.photo=parseImage(stream);
		break;
		case IMAGEALBUM:
		artobj.contents.photoalbum=parseImageAlbum(stream);
		break;
		case SKIT:
		artobj.contents.scene=parseSkit(stream);
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
	if(tree){
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
}


void printArtifactTreePretty(FILE*stream,BSTreeComp* tree){
	fprintf(stream,"Printing artifacts of card:\n\n");
	treeIt* it= initTreeItComp(tree);
	while(hasNextTreeItComp(it)){
		
		artifact* nextElem= (artifact*)nextTreeItComp(it);
		printArtifactPretty(stream,nextElem);
	}
	destroyTreeIt(it);
}
