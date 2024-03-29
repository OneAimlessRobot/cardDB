#include "../Includes/preprocessor.h"
#include "../Includes/nodes.h"
#include "../Includes/comparator.h"
#include "../Includes/doublelist.h"
#include "../Includes/doublelistcomp.h"
#include "../Includes/dliterator.h"



void* nextIt(dliterator* it){


	void* result=it->nextNode->mem;
	it->nextNode=it->nextNode->next;
	return result;

}
dliterator* initIt(DListW* list){
	
	dliterator* result= malloc(sizeof(dliterator));
	result->list= list;
	result->nextNode=list->head;

	return result;


}
u_int64_t hasNextIt(dliterator*it){

	//printf("No: %p\n",it->nextNode);
	return(u_int64_t)it->nextNode;

}
void rewindIt(dliterator*it){


	 it->nextNode=it->list->head;

}

void* nextItComp(dliteratorcomp* it){


	void* result=it->nextNode->mem;
	it->nextNode=it->nextNode->next;
	return result;

}
dliteratorcomp* initItComp(DListWComp* list){
	
	dliteratorcomp* result= malloc(sizeof(dliteratorcomp));
	result->list= list;
	result->nextNode=list->head;

	return result;


}
u_int64_t hasNextItComp(dliteratorcomp*it){


	return (u_int64_t)it->nextNode;

}
void rewindItComp(dliteratorcomp*it){


	 it->nextNode=it->list->head;

}
