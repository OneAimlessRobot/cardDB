#ifndef HTITERATOR_H
#define HTITERATOR_H

typedef struct htiterator{

dliteratorcomp* currIt;
u_int64_t firstpos,lastpos,currpos;
hashtablecomp* table;

}htiterator;


void* nextItHT(htiterator* it);
htiterator* initItHT(hashtablecomp* table);
u_int64_t hasNextItHT(htiterator*it);
int rewindItHT(htiterator*it);

#endif
