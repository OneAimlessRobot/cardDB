#include "../Includes/preprocessor.h"
#include "../Includes/nodes.h"
#include "../Includes/comparator.h"
#include "../Includes/hasher.h"
#include "../Includes/doublelist.h"
#include "../Includes/doublelistcomp.h"
#include "../Includes/dliterator.h"
#include "../Includes/hashtablecomp.h"
#include "../Includes/htiterator.h"



void* nextItHT(htiterator* it){
void* result=NULL;


	result=nextItComp(it->currIt);

	if(!hasNextItComp(it->currIt)){
	free(it->currIt);
	it->currIt=NULL;
	it->currpos++;
	if(it->currpos==it->table->currSpineSize){
	return result;
	}
	it->currIt=initItComp(it->table->spine[it->currpos]);
	while(!hasNextItComp(it->currIt)&&it->currpos<it->lastpos){
			
	free(it->currIt);
	it->currIt=NULL;
	it->currpos++;
	it->currIt=initItComp(it->table->spine[it->currpos]);
			
	}
	
	}
	
	return result;

}

htiterator* initItHT(hashtablecomp* table){
	htiterator* result= malloc(sizeof(htiterator));
	result->table= table;
	if(rewindItHT(result)){
		free(result);
		return NULL;
	}
	result->currIt=initItComp(table->spine[result->currpos]);

	return result;


}
u_int64_t hasNextItHT(htiterator*it){

	return(u_int64_t)( it->currpos<=it->lastpos &&(u_int64_t) hasNextItComp(it->currIt));

}
int rewindItHT(htiterator*it){

	int firstpos=0;
	while(!it->table->spine[firstpos]->currSize){
		
		firstpos++;

	}
	if(firstpos >= it->table->currSpineSize){

		return 1;
	}

	it->firstpos=firstpos;
	int lastpos=it->table->currSpineSize-1;
	while(!it->table->spine[lastpos]->currSize&&lastpos<it->firstpos){
		
		lastpos--;

	}
	it->lastpos=lastpos;
	it->currpos=firstpos;
	return 0;
}
