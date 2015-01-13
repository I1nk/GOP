#include "gop.h"

/**
 * Generate the location randomly for each node based on the global
 * values from X_MAX and Y_MAX.
 *
 */
void generateNodes( void )
{

   //vars
   unsigned int index;
   double random_num;
   Node *list_node = list_node_g;
   const double RANDOM_NUMBER_MAX_D = (double) RAND_MAX;
   
   //start the random number with seed based on the time
   srand(time(NULL));

   //Find a random number
   random_num = rand();

   //scale the random number to 0-1
   random_num /= RANDOM_NUMBER_MAX_D;
   
   for (index = 0; index < SIZE_OF_NODES; index++, list_node++)
   {
   
      //Find a random number
      random_num = rand();
  
      //scale the random number to 0-1
      random_num /= RANDOM_NUMBER_MAX_D;

      //set the x location of the node
      list_node->x = X_MAX * random_num;
 
      //Find a random number
      random_num = rand();
  
      //scale the random number to 0-1
      random_num /= RANDOM_NUMBER_MAX_D;

      //set the x location of the node
      list_node->y = Y_MAX * random_num;
 
   }
   
}

/**
* Allocate memory in the heap for the hist array which is a 2d array
* @return double** to the array of unsigned ints
*/
Node **make2dNeighborList( void )
{
   //varaibles
   unsigned long i;
   Node **inrange;
   Node **p2;

   inrange = (Node**) malloc(SIZE_OF_NODES * sizeof(Node*));
   p2 = inrange;

   for(i = 0; i < SIZE_OF_NODES; i++,p2++)
   {
      *p2 = (Node*) calloc(SIZE_OF_NODES, sizeof(Node));
   }

   p2 = NULL;
   return inrange;

}



int main ( void )
{
   
   //vars
   Node *list_node = (Node*) calloc(SIZE_OF_NODES, sizeof(Node));
   Node **list_neighbor = make2dNeighborList();

   //set the globals up
   list_node_g = list_node;
   list_neighbor_g = list_neighbor;

   //Make the node list
   generateNodes();
   


   list_node_g = NULL;
   list_neighbor_g = NULL;

   free(list_node);
   free(list_neighbor);

   return 0;
}
