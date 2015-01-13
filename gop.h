#ifndef _GOP_H_
#define _GOP_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//structs

typedef struct NODE
{
   double x;
   double y;
   double percentage;
   unsigned long rx;
   unsigned long tx;
   double range;
   struct NODE *neighbor_list;

}Node;


//functions
void generateNodes( void );

Node **make2dNeighborList(void);


//defines
#define SIZE_OF_NODES 10000000


//globals
Node *list_node_g;
Node **list_neighbor_g;
const double TX_PROBAILITY_PERCENTAGE = 0.7;
const double X_MAX = 25;
const double Y_MAX = 25;

#endif
