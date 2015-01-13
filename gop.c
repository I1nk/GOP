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
   
   for (index = 0; index < NUMBER_OF_NODES; index++, list_node++)
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

int compareFunction(const void *v_node_1, const void *v_node_2)
{
   
   //vars
   struct N_List *node_1 = (struct N_List*) v_node_1;
   struct N_List *node_2 = (struct N_List*) v_node_2;

   if(node_1->distance < node_2->distance)
      return -1;
   else if (node_1->distance > node_2->distance)
      return 1;
   else
      return 0;
}


void makeNeighborList( void )
{

   //vars
   unsigned long index, index_inner, index_outer, position = 0;
   struct N_List *list_neighbor = *list_neighbor_g;
   struct N_List *start = list_neighbor;
   Node *node = list_node_g;
   Node *list_node;// = list_node_g;

   for (index_outer = 0; index_outer < NUMBER_OF_NODES-1; \
      index_outer++, position++)
   {   
      //go to the next node in the list
      node++;
      //reset the array pointer for the list
      list_node = list_node_g;
      //set the next array pointer for the list
      list_neighbor = list_neighbor_g[index_outer];
      start = list_neighbor;
   
      for (index_inner = 0; index_inner < NUMBER_OF_NODES; \
         index_inner++, list_neighbor++)
      {
         if (position == index_inner)
         {
            list_neighbor->distance = -1;
            list_neighbor->index = index_inner;
   
         }
         else
         {
            list_neighbor->index = index_inner;
            list_neighbor->distance = findDistance(node,list_node);
         }
         list_node++;
      }

      list_neighbor--;

      qsort(start, NUMBER_OF_NODES, sizeof(struct N_List), compareFunction);
   
      //for (index = 0; index < NUMBER_OF_NODES; index++,start++)
      //{
      //   printf("%lu     %lf\n", index, start->distance);
      //}
      //printf("%lu %lu\n\n", index_outer, index_inner);
      //puts("");
   }
}

double findDistance(Node *node1, Node *node2)
{

   //vars
   //find the differance of the distance
   double dist1 = node1->x - node2->x;
   double dist2 = node1->y - node2->y;

   //square the distance
   dist1 *= dist1;
   dist2 *= dist2;

   //find the sum of the distance
   dist1 += dist2;

   //find the sqrt of the distance
   return sqrt(dist1);

}

/**
* Allocate memory in the heap for the hist array which is a 2d array
* @return double** to the array of unsigned ints
*/
struct N_List **make2dNeighborList( void )
{
   //varaibles
   unsigned long i;
   struct N_List **inrange;
   
   inrange = (struct N_List**) malloc(NUMBER_OF_NODES * sizeof(struct N_List**));
   
   if (inrange == NULL)
      exit(-1);  
   

   for(i = 0; i < NUMBER_OF_NODES; i++)
   {
      inrange[i] = (struct N_List*) calloc(NUMBER_OF_NODES, sizeof(struct N_List*));
      if (inrange[i] == NULL)
         exit(-1);
   }

   return inrange;

}

/**
* Deallocate the memory used in the hist array.
* @param double** pointer to the hist array
*/
void Make2dInRangeFree(struct N_List **p)
{

   //varaibles
   unsigned long i;
   
   for (i = 0; i >= NUMBER_OF_NODES ; i--)
   {
      free(p[i]);
   }

}

int main ( void )
{
   
   //vars
   Node *list_node = (Node*) calloc(NUMBER_OF_NODES, sizeof(Node));

   if(list_node == NULL)
      exit(-1);

   struct N_List **list_neighbor = make2dNeighborList();
   
   //set the globals up
   list_node_g = list_node;
   
   //Make the node list
   generateNodes();

   //set the global pointer up for the neighbor list
   list_neighbor_g = list_neighbor;

   makeNeighborList();

 //  printf("\nHello I am here\n");

   list_node_g = NULL;
   list_neighbor_g = NULL;
   
   Make2dInRangeFree(list_neighbor);
 
   free(list_node);

   return 0;
}
