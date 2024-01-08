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
#include "../../Includes/card.h"
#include "../../Includes/database.h"
#include "../Includes/maincmds.h"

carddatabase* cards=NULL;
int loaded=0;
cmdstruct maincmds[] = {
			{"load",load,"carrega cartas"},
                        {"addcard",addcard,"Adicionar carta"},
                        {"addrand",addrand,"Adicionar carta com dados lixo"},
                        {"addrandcards",addrands,"Adicionar cartas com dados lixo"},
                        {"remcard",remcard,"Remover carta"},
                        {"printcards",printcards,"Mostra cartas"},
                        {"printcard",printcard,"Mostra 1 carta"},
                        {"printsize",printsize,"Mostra numero de cartas carregadas"},
                        {"sair",sair,"sair"},
                        {"showallcmds",showallcmds,"mostrar comandos disponiveis"},
                        {"save",save,"escrever no disco"},
                        {"",0,""}
                };


void sair(int64_t argc,int* toExit, void** argv){
        *toExit=1;
	destroyDataBase(cards);
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

