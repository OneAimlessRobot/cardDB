#ifndef TREEIT_H
#define TREEIT_H

typedef struct treeIt{

stackList* stack;
BSTreeComp* tree;


}treeIt;

void* nextTreeItComp(treeIt* it);

treeIt* initTreeItComp(BSTreeComp* tree);

int hasNextTreeItComp(treeIt*it);

void rewindTreeItComp(treeIt*it);


void destroyTreeIt(treeIt* it);

#endif
