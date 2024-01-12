#include "../../Includes/preprocessor.h"
#include "../../Includes/hasher.h"
#include "../../Includes/comparator.h"
#include "../../Includes/nodes.h"
#include "../../Includes/doublelistcomp.h"
#include "../../Includes/doublelist.h"
#include "../../Includes/stackList.h"
#include "../../Includes/BSTcomp.h"
#include "../../Includes/hashtablecomp.h"
#include "../../Includes/dliterator.h"
#include "../../Includes/treeIt.h"
#include "../../Includes/dliterator.h"
#include "../../Includes/htiterator.h"
#include "../../Includes/hashtablecmd.h"
#include "../../Includes/cmdstruct.h"
#include "../../Includes/artifact.h"
#include "../../Includes/card.h"
#include "../../Includes/database.h"
#include "../Includes/maincmds.h"

carddatabase* cards=NULL;
BSTreeComp* testarttree=NULL;
int loaded=0;
int artloaded=0;
cmdstruct maincmds[] = {
			{"load",load,"carrega cartas"},
                        {"loadart",loadart,"(TEST) carrega arte"},
                        {"addcard",addcard,"Adicionar carta"},
                        {"addrand",addrand,"Adicionar carta com dados lixo"},
                        {"addrandcards",addrands,"Adicionar cartas com dados lixo"},
                        {"remcard",remcard,"Remover carta"},
                        {"printcards",printcards,"Mostra cartas"},
                        {"printart",printart,"(TEST) Mostra arte"},
                        {"printcard",printcard,"Mostra 1 carta"},
                        {"printcardart",printcardart,"Mostra arte de 1 carta"},
                        {"printsize",printsize,"Mostra numero de cartas carregadas"},
                        {"sair",sair,"sair"},
                        {"showallcmds",showallcmds,"mostrar comandos disponiveis"},
                        {"save",save,"escrever no disco"},
                        {"",0,""}
                };


void sair(int64_t argc,int* toExit, void** argv){
        *toExit=1;
	if(loaded){
	destroyDataBase(cards);
	fprintf(stdout,"Cartas destruidas!!!!\n");
	}
	if(artloaded){
	destroyArtifactTree(testarttree);
	fprintf(stdout,"Arte destruida!!!!\n");
	}
}

void loadart(int64_t argc,int* toExit, void** argv){
	char path[ARTMIDFIELDSIZE+1]={0};
	fprintf(stdout,"\ninsere aqui a path para a arte:\n");
	fscanf(stdin,"%[^;];",path);
	FILE* stream= fopen(path,"r");
	testarttree= genArtifactTreeFromStream(stream);
	artloaded=1;
	fclose(stream);
	fprintf(stdout,"Carregaste %lu artes!!!\n",testarttree->currSize);
	
}

void load(int64_t argc,int* toExit, void** argv){

	cards= initDataBase(CARDS_PATH);
	if(!cards){
		fprintf(stderr,"Erro a carregar cartas!!!\n");
		return;
	}
	printf("Cartas carregadas!!!!\n");
	loaded=1;
}

void save(int64_t argc,int* toExit, void** argv){
	if(loaded){

		saveDataBase(cards);
	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}

void printart(int64_t argc,int* toExit, void** argv){
       	
		if(!artloaded){
		fprintf(stderr,"Arte nao inicializada!!!!\n");
		}
		else if(!testarttree->currSize){

		fprintf(stderr,"Não existe arte!!!!\n");
		
		}
		else{

		printArtifactTree(stdout,testarttree);
	
		}
}
void printcard(int64_t argc,int* toExit, void** argv){
       	
	if(loaded&&cards->storage->currSize){
		fflush(stdin);
		char name[CARDSMALLFIELDSIZE]={0};
		fscanf(stdin,"%[^;];",name);
		printf("Inseriste %s\n",name);
		printDataBaseCard(cards,name);
	}
	else{
		
		if(!loaded){
		fprintf(stderr,"Cartas nao carregadas!!!!\n");
		}
		else if(!cards->storage->currSize){

		fprintf(stderr,"Não existem cartas!!!!\n");
		
		}
	}
}

void addcard(int64_t argc,int* toExit, void** argv){
        if(loaded){
		card* addedcard=malloc(sizeof(card));
		memset(addedcard->name,0,CARDSMALLFIELDSIZE+1);
		memset(addedcard->type,0,CARDSMALLFIELDSIZE+1);
		memset(addedcard->build,0,CARDLARGEFIELDSIZE+1);
		memset(addedcard->desc,0,CARDLARGEFIELDSIZE+1);
		memset(addedcard->artfilepath,0,CARDMIDFIELDSIZE+1);
		fprintf(stdout,"(Para os primeiros 4 campos, tudo e lido ate se encontrar um ';')\n");

		fprintf(stdout,"insere aqui o nome (termina em ';') (max 127):\n");
		fscanf(stdin,"%[^;];",addedcard->name);

		fprintf(stdout,"insere aqui o tipo (termina em ';') (max 127):\n");
		fscanf(stdin,"%[^;];",addedcard->type);

		fprintf(stdout,"insere aqui a build (termina em ';') (max 10000):\n");
		fscanf(stdin,"%[^;];",addedcard->build);

		fprintf(stdout,"insere aqui a descricao (termina em ';') (max 10000):\n");
		fscanf(stdin,"%[^;];",addedcard->desc);

		fprintf(stdout,"insere aqui a idade (anos):");
		fscanf(stdin,"%lu",&addedcard->age);

		fprintf(stdout,"insere aqui a altura (cm):");
		fscanf(stdin,"%lu",&addedcard->height);

		fprintf(stdout,"insere aqui a massa (kg):");
		fscanf(stdin,"%lu",&addedcard->weight);

		fprintf(stdout,"insere aqui a path para a arte:");
		fscanf(stdin,"%[^;];",addedcard->artfilepath);

		addCardToDataBase(cards,addedcard);
		free(addedcard);
	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}
void addrand(int64_t argc,int* toExit, void** argv){
        if(loaded){
		card* addedcard= initRandCard();
		addCardToDataBase(cards,addedcard);
		free(addedcard);
	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}
void addrands(int64_t argc,int* toExit, void** argv){
        if(loaded){
		u_int64_t ammount=0;
		fscanf(stdin,"%lu",&ammount);
		for(;ammount;ammount--){
		card* addedcard= initRandCard();
		addCardToDataBase(cards,addedcard);
		free(addedcard);
		}
	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}

void printcardart(int64_t argc,int* toExit, void** argv){


}
void remcard(int64_t argc,int* toExit, void** argv){
        if(loaded&&cards->storage->currSize){
		
		fflush(stdin);
		char name[CARDSMALLFIELDSIZE]={0};
		fscanf(stdin,"%[^;];",name);
		printf("Inseriste %s\n",name);
		remCardFromDataBase(cards,name);
	}
	else{
		
		if(!loaded){
		fprintf(stderr,"Cartas nao carregadas!!!!\n");
		}
		else if(!cards->storage->currSize){

		fprintf(stderr,"Não existem cartas!!!!\n");
		
		}
	}

}

void printcards(int64_t argc,int* toExit, void** argv){
       	if(loaded&&cards->storage->currSize){

		printDataBase(cards);
	}
	else{
		if(!loaded){
		fprintf(stderr,"Cartas nao carregadas!!!!\n");
		}
		else if(!cards->storage->currSize){

		fprintf(stderr,"Não existem cartas!!!!\n");
		
		}
	}

}


void printsize(int64_t argc,int* toExit, void** argv){
	if(loaded){

		printf("O tamanho da base de dados é: %lu\n",getDataBaseSize(cards));
	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}


}

void showallcmds(int64_t argc,int* toExit, void** argv){


                        int j=0;
                        while(maincmds[j].cmdname[0]){
                        printf("%s- %s\n",(char*)maincmds[j].cmdname,(char*)maincmds[j].helpdesc);
                        j++;

                        }
                        printf("\n");
}

