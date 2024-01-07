#include "../Includes/preprocessor.h"
#include "../Includes/nodes.h"
#include "../Includes/doublelist.h"
#include "../Includes/stackList.h"
#include "../Includes/BSTcomp.h"
#include "../Includes/treeIt.h"

void* nextTreeItComp(treeIt* it){
		BSTNode* node=popDLStack(it->stack);
		void* result=node->mem;
		BSTNode*curr=node;
		if(curr){
			if(curr->right){
			pushDLStack(it->stack,curr->right);
			curr=curr->right;
			while(curr->left){
				
				pushDLStack(it->stack,curr->left);
				curr=curr->left;
			}
			
		
		}
		free(node);
		}
	
        return result;

}
treeIt* initTreeItComp(BSTreeComp* tree){
	
	treeIt* result= malloc(sizeof(treeIt));
	result->tree= tree;
	result->stack=NULL;
	rewindTreeItComp(result);
        return result;


}
int hasNextTreeItComp(treeIt*it){


        return !isEmptyDLStack(it->stack);

}
void rewindTreeItComp(treeIt*it){
	if(it->stack){
	destroyDLStack(it->stack);
	}
	it->stack= initDLStack(sizeof(BSTNode));
	printf("%p %p %p\n",it, it->tree, it->tree->root);
	BSTNode* node=it->tree->root;
	pushDLStack(it->stack,it->tree->root);
	while(node->left){
	
		pushDLStack(it->stack,node->left);
		node=node->left;
		
	}
}

void destroyTreeIt(treeIt* it){

	destroyDLStack(it->stack);
	it->stack=NULL;
	free(it);

}
