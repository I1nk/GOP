#ifndef _GOP_H_
#define _GOP_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h> //for sleep
//structs

struct N_List
{
   unsigned long index;
   double distance;
};

typedef struct NODE
{
   double x;
   double y;
   char rx;
   char tx;
}Node;

//functions
void generateNodes( void );
void makeNeighborList(void);
void Make2dInRangeFree(struct N_List**);

struct N_List **make2dNeighborList(void);
int compareFunction(const void*, const void*);
double findDistance(Node*, Node*);

//defines
#define _TX_PROBAILITY_PERCENTAGE_ 0.7
#define _NO_TX_PROBAILITY_PERCENTAGE_ 1.0 - _TX_PROBAILITY_PERCENTAGE_
#define _STACK_CONSTANT_ 5
#define _NUMBER_OF_NODES_ 1000
#define _STACK_SIZE_ _NUMBER_OF_NODES_ * _STACK_CONSTANT_

//globals
const unsigned long NUMBER_OF_NODES = _NUMBER_OF_NODES_;
const unsigned long STACK_SIZE = _STACK_SIZE_;
Node *list_node_g;
struct N_List **list_neighbor_g;
const double TX_PROBAILITY_PERCENTAGE = _TX_PROBAILITY_PERCENTAGE_;
const double NO_TX_PROBAILITY_PERCENTAGE = _NO_TX_PROBAILITY_PERCENTAGE_;
const double X_MAX = 25;
const double Y_MAX = 25;
const double MAX_RANGE = 5;
unsigned int k_hops = 4;
unsigned long stack_index = 0;

#endif
