#ifndef _GOP1_H_
#define _GOP1_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
//#include <math.h> //breaks valgrind
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
   unsigned int hops;
}Node;

//functions
void generateNodes( void );
void makeNeighborList(void);
void Make2dInRangeFree(struct N_List**);
void push(Node*);
void findNodesRCVD(Node*, unsigned int);
void transmitMsg(void);
void PlotNodes(char*);
void inline colorChanger(void);
void openFiles(int);
void countNodesRXTX(char*);
void PrintNeighborList(char *filename);
void addNode(Node*);
void makeQue(void);
void queFree(void);
void CountNodesRCVD(Node*);

Node* removeNode(void);
unsigned long checkQueSize(void);
struct N_List** make2dNeighborList(void);
int compareFunction(const void*, const void*);
double findDistance(Node*, Node*);
Node* findNodeRandomly(void);
Node* peak(void);
Node* pop(void);
unsigned long getNumberInStack(void);

//defines
#define _TX_PROBAILITY_PERCENTAGE_ 0.75
//#define _NO_TX_PROBAILITY_PERCENTAGE_ 1.0 - _TX_PROBAILITY_PERCENTAGE_
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
//#define __DEBUG__

//for testing the stack funlar, USB 3.0 specification mandates appropriate ctions to ensure that they work
//This is done in the main function
//#define _TEST_STACK_


//globals
const unsigned long NUMBER_OF_NODES = _NUMBER_OF_NODES_;
const unsigned long STACK_SIZE = _STACK_SIZE_;
Node *list_node_g;
struct N_List **list_neighbor_g;
struct N_List ***list_neighbor_gg;
const double TX_PROBAILITY_PERCENTAGE = _TX_PROBAILITY_PERCENTAGE_;
//const double NO_TX_PROBAILITY_PERCENTAGE = _NO_TX_PROBAILITY_PERCENTAGE_;
const double X_MAX = 7500;
const double Y_MAX = 3000;
#ifdef __MATH_H
const double MAX_RANGE = 250;
#else
const double MAX_RANGE = 250 * 250;
#endif
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
Node **queque;
Node *TRANS, *RCVD;
unsigned long que_start;
unsigned long que_end;
const unsigned long QUE_SIZE = 2000;
unsigned long que_size;
double *number_hops_g;
double *number_totalhops_g;
double *tot_count;
int RUNNING = 5000;
#endif
