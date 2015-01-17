#include "gop.h"

/**
 * Generate the location randomly for each node based on the global
 * values from X_MAX and Y_MAX.
 *
 */
void generateNodes( void )
{

   //vars
   unsigned long index;
   double random_num;
   Node *list_node = list_node_g;
   
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

      //set the index value
      list_node->index = index;

      //set the k_hops_left value
      list_node->k_hops_left = 0;
 
   }
   
}

void push(Node *new_node)
{

   //check to ensure that the stack has room for another plate
   if (stack_index > STACK_SIZE)
   {
      puts("Stack will overflow since the stack is full.");
      puts("Program will now exit");
      exit(-1);
   }

   //increase the stack pointer by one
   stack++;
   
   //give the stack pointer a new value
   *stack = new_node;

   //increase the number of plates on the stack
   stack_index++;

}

/**   
 *    Peak at the top of the stack.
 *    @return the node on the top of the statck, but does not pop the Node from the stack
 */
Node* peak( void )
{

   return *stack;

}

/**
 *    Get the number of Nodes in the stack.
 *    @return the number of nodes in the stack
 */
unsigned long getNumberInStack( void )
{

   return stack_index;

}

/**
 *    Pop the node from the stack. Returns the node from the top of the stack.
 *    @return Node *
 */
Node* pop( void )
{

   Node *output = *stack;   

   //check to ensure that the stack has something on it
   if (!stack_index)
   {  
      puts("tried to pop when the stack is empty.");
      puts("Program will now exit");
      exit(-1);
   }

   //decrease the number of items on the stack by one   
   stack_index--;

   //decrease the pointer by 1
   stack--;

   //return the new top of the stack
   return output;

}


Node* findNodeRandomly( void )
{

   //vars
   double random_number;
   unsigned long index;
   Node *output = list_node_g;

   //seed the random number
   srand(time(NULL));

   //find the random number
   random_number = rand();

   //scale the random numbernsmitMsg
   random_number /= RANDOM_NUMBER_MAX_D;

   //scale the random number to the number of nodes that were generated to an index value
   index = (unsigned long) (random_number * NUMBER_OF_NODES);

   //return the node
   return &output[index];
}

void transmitMsg( void )
{

   //vars
   Node *tx, *rx, *current;
   boolean finished = false;
   double random_number;
   unsigned long number_of_tx = 0;
   //current will be the node that the msg is currently at 
   //tx is the node that the msg started from
   //rx will be the node the msg wants to go to

   //seed the random number generator with a time
   srand(time(NULL));

   //find the rx and tx nodes
   rx = findNodeRandomly();
   tx = findNodeRandomly();

   //set the current node to the tx so we can know where the msg started at
   current = tx;

   //loop though and keep tx untill is equal to rx  
   while(!finished)
   {

      //get the random number
      random_number = rand();

      //scale the random number from 0 to 1
      random_number /= RANDOM_NUMBER_MAX_D;
   
      printf("this is the dice roll number %lf\n", random_number);

      //if the node will transmit bassed on the percentage to transmit
      if((random_number < TX_PROBAILITY_PERCENTAGE))
      {

         printf("The node that will be TX is %lu\n", current->index);
         //find the nodes that will be RCVD the msg send by the TX node.
         findNodesRCVD(current);
         number_of_tx++;

      }
      
      //only tx if there is a node in the stack else the msg is done being tx
      if(getNumberInStack())
      {
         //pick the next node that will be transmitting from the stack
         current = pop();
      }
      else
         finished = true;
   }
   
   
   printf("This is the node that is meant to RX the mesg index  %lu\n", rx->index);
   printf("The node that was meant to rx RCVD msg %i\n", rx->rx);
   printf("The number of times the msg was transmitted is %lu\n",number_of_tx);

}

void findNodesRCVD(Node *current)
{

   //vars
   Node *list_node = list_node_g;
   struct N_List **list_neighbor = list_neighbor_g;
   struct N_List *neighbor_p;

   //go to the node that is currently tx the msg neighbor list
   list_neighbor += current->index;
   neighbor_p = *list_neighbor;

   while(neighbor_p->distance <= MAX_RANGE)
   {

      //add the node to the stack if the node has yet to RCVD the msg
      if(!list_node[neighbor_p->index].tx)
      {
         //add the node to the stack
         push(&list_node[neighbor_p->index]);

         //add one to the tx count of the node
         list_node[neighbor_p->index].tx += 1;
         list_node[neighbor_p->index].rx += 1;

      }
      else
         list_node[neighbor_p->index].rx += 1;

      //increase the pointer by one to the next index
      neighbor_p++;
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
   unsigned long index_inner, index_outer, position = 0;
   struct N_List *list_neighbor = *list_neighbor_g;
   struct N_List *start = list_neighbor;
   Node *node = list_node_g;
   Node *list_node;// = list_node_g;

   for (index_outer = 0; index_outer < NUMBER_OF_NODES-1; \
      index_outer++, position++)
   {   //start of outer for loop
      
      //go to the next node in the list
      node++;
      
      //reset the array pointer for the list
      list_node = list_node_g;
      
      //set the next array pointer for the list
      list_neighbor = list_neighbor_g[index_outer];
      
      //set the starting index for the array for qsort
      start = list_neighbor;
   
      //loop though the list and find the distance from node to the list_node
      for (index_inner = 0; index_inner < NUMBER_OF_NODES; \
         index_inner++, list_neighbor++)
      {//start of inner for loop
         //if the list_node == node
         if (position == index_inner)
         {
            list_neighbor->distance = -1;
            list_neighbor->index = index_inner;
   
         }
         else
         {
            //else find the distance and save the index
            list_neighbor->index = index_inner;
            list_neighbor->distance = findDistance(node,list_node);
         }
         //go to the next node
         list_node++;
      }//end of inner for loop

      //a safety check to put the pointer back to the bounds of the array
      list_neighbor--;

      //sort the array using quick sort
      qsort(start, NUMBER_OF_NODES, sizeof(struct N_List), compareFunction);

#ifdef __DEBUG__
      for (index = 0; index < NUMBER_OF_NODES; index++,start++)
      {
         printf("%lu     %lf\n", index, start->distance);
      }
      printf("outer inter == %lu %lu\n\n", index_outer, index_inner);
      puts("");
#endif      
   }//end of outer for loop
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
   
   //allocate memory for the 2d array
   inrange = (struct N_List**) malloc(NUMBER_OF_NODES * sizeof(struct N_List**));
   
   //Check to see if program could allocate memory
   if (inrange == NULL)
   {
      puts("Program failed to allocate memory for the neighbor list.");
      puts("Program will now exit.");
      exit(-1);  
   }

   //go though the 2d array and allocte memory for each element
   for(i = 0; i < NUMBER_OF_NODES; i++)
   {
      //allocate memory for the element
      inrange[i] = (struct N_List*) calloc(NUMBER_OF_NODES, sizeof(struct N_List*));

      //check to see if the program could allocate the memory
      if (inrange[i] == NULL)
      {
         puts("Program failed to allocate memory for the neighbor list.");
         puts("Program will now exit.");
         exit(-1);
      }
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
 
   //free the memory of each element  
   for (i = 0; i >= NUMBER_OF_NODES ; i--)
   {
      free(p[i]);
   }

}

int main ( void )
{
   
   //vars
   Node *list_node = (Node*) calloc(NUMBER_OF_NODES, sizeof(Node));
   stack = (Node**) calloc(STACK_SIZE, \
      sizeof(Node*));

   //check to see if the program could allocate memory for the array
   if(list_node == NULL)
   {
      puts("Program failed to allocate memory for the node array.");
      puts("Program will now exit.");
      return -1;
   }

   //make a 2d array for the neighbor list
   struct N_List **list_neighbor = make2dNeighborList();
   
   //set the globals up
   list_node_g = list_node;
   
   //Make the node list
   generateNodes();

   //set the global pointer up for the neighbor list
   list_neighbor_g = list_neighbor;

   //makes the neighbor list for each node
   makeNeighborList();

   transmitMsg();


#ifdef _TEST_STACK_
#warning Testing the stack code to see if it works
   Node *p;

   push(&list_node[0]);
   push(&list_node[1]);
   push(&list_node[2]);
   push(&list_node[3]);

   p = pop();   

   printf("Pop %lf\n", p->x);
   p = peak();
   printf("Peak %lf\n", p->x );
   printf("%lf\n",list_node[0].x);
   printf("%lf\n",list_node[1].x);
   printf("%lf\n",list_node[2].x);
   printf("%lf\n",list_node[3].x);
#endif

/////Nothing below this line./////////////////////////////////////////////////

   //start cleaning the memory
   list_node_g = NULL;
   list_neighbor_g = NULL;
   
   //clean the 2d array memory
   Make2dInRangeFree(list_neighbor);
 
   //clean the 1d array
   free(list_node);

   //reset the stack value
   //this is only needed in testing the stack function and the stack should be empty
   //But this will be kept here if something happens
   if (stack_index)
   {
      puts("Warning: The stack still have Nodes in it and the program is ending.");
   }
   stack -= stack_index;

   free(stack);

   return 0;
}
