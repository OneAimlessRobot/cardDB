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


	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}

void printcard(int64_t argc,int* toExit, void** argv){
	if(loaded){


	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}

void addcard(int64_t argc,int* toExit, void** argv){
        if(loaded){


	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}
}

void remcard(int64_t argc,int* toExit, void** argv){
        if(loaded){


	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
	}

}

void printcards(int64_t argc,int* toExit, void** argv){
       	if(loaded){

		printDataBase(cards);
	}
	else{

		fprintf(stderr,"Cartas nao carregadas!!!!\n");
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

