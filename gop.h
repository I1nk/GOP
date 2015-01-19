#ifndef _GOP_H_
#define _GOP_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h> //for sleep
//structs

typedef enum Boolean 
{
   false,
   true
}boolean;

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
   unsigned char k_hops_left;
   unsigned long index;
}Node;

//functions
void generateNodes( void );
void makeNeighborList(void);
void Make2dInRangeFree(struct N_List**);
void push(Node*);
void findNodesRCVD(Node*);
void transmitMsg(void);
void PlotNodes(char*);
void inline colorChanger(void);
void openFiles(int);
void countNodesRXTX(char*);

struct N_List** make2dNeighborList(void);
int compareFunction(const void*, const void*);
double findDistance(Node*, Node*);
Node* findNodeRandomly(void);
Node* peak(void);
Node* pop(void);
unsigned long getNumberInStack(void);

//defines
#define _TX_PROBAILITY_PERCENTAGE_ 0.72
#define _NO_TX_PROBAILITY_PERCENTAGE_ 1.0 - _TX_PROBAILITY_PERCENTAGE_
#define _STACK_CONSTANT_ 5
#define _NUMBER_OF_NODES_ 1000
#define _STACK_SIZE_ _NUMBER_OF_NODES_ * _STACK_CONSTANT_
#define PATH_LIST_FILENAME "Path.dat"
#define PATH_LIST_VECTOR_FILENAME "Path_vector.dat"
#define NODE_XY_COORD_FILENAME "Node_coord.dat"
#define VECTOR_FILENAME "VectorPath.dat"
#define VECTOR_DOUBLE_FILENAME "VectorPathDouble.dat"
#define START_POINT_FILENAME "startPoint.dat"
#define END_POINT_FILENAME "endPoint.dat"


//for testing the stack funlar, USB 3.0 specification mandates appropriate ctions to ensure that they work
//This is done in the main function
//#define _TEST_STACK_


//globals
const unsigned long NUMBER_OF_NODES = _NUMBER_OF_NODES_;
const unsigned long STACK_SIZE = _STACK_SIZE_;
Node *list_node_g;
struct N_List **list_neighbor_g;
const double TX_PROBAILITY_PERCENTAGE = _TX_PROBAILITY_PERCENTAGE_;
const double NO_TX_PROBAILITY_PERCENTAGE = _NO_TX_PROBAILITY_PERCENTAGE_;
const double X_MAX = 20;
const double Y_MAX = 50;
const double MAX_RANGE = 1.75;
unsigned int k_hops = 4;
unsigned long stack_index = 0;
const double RANDOM_NUMBER_MAX_D = (double) RAND_MAX;
unsigned char rgb_r_g = 0;
unsigned char rgb_g_g = 0;
unsigned char rgb_b_g = 0;
char color_changer_g = 1;
FILE *path_list_g;
FILE *vector_path_list_g;
FILE *vector_path_double_list_g;
FILE *start_node_g;
FILE *end_node_g;
Node **stack;

#endif
