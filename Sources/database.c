#include "../Includes/preprocessor.h"
#include "../Includes/comparator.h"
#include "../Includes/nodes.h"
#include "../Includes/doublelist.h"
#include "../Includes/stackList.h"
#include "../Includes/BSTcomp.h"
#include "../Includes/card.h"
#include "../Includes/database.h"

carddatabase* initDataBase(char* filepath){
	
	carddatabase* result= malloc(sizeof(carddatabase));
	result->storage= initBSTreeComp(sizeof(card),&cardCmp);
	FILE* stream= fopen(filepath,"r");
	int numOfCards=0;
	fscanf(stream,"%d",&numOfCards);
	result->numOfCards=numOfCards;
	for(;numOfCards;numOfCards--){
		card* readCard= fscanCard(stream);
		addToBSTreeComp(result,readCard);
		free(readCard);
	}
	fclose(stream);
	return result;


}
