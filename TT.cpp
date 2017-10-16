//TT.cpp
//Samuel Stall
//Creates a tournament tree in packed array representation give an array of scores
//COP3530 Data Structures and Algorithms

#include <iostream>
#include <cmath>
#include "Bounded_Dequeue.h"

int* makeTT(int* scores_begin, int* scores_end);

int main() {

     int array[] = {50, 5, 3, 4, 20, 9, 100};

     int* tournament = makeTT(array, &array[7]);

     for(unsigned int i = 0; i < 14; i++) {
          std::cout << tournament[i] << " ";
     }

     std::cout << std::endl;

     delete [] tournament;

     int array2[] = {60, 4, 1000, 251, 43, 56, 67, 67, 89, 1000};

     int* tournament2 = makeTT(array2, &array2[10]);

     for(unsigned int i = 0; i < 21; i++) {
          std::cout << tournament2[i] << " ";
     }

     std::cout << std::endl;

     delete [] tournament2;

     return 0;
}

int* makeTT(int* scores_begin, int* scores_end) {
     //Finds the size of the array passed
     unsigned int size = scores_end - scores_begin;

     //Calculates the height of the tournament
     unsigned int height = ceil(log2(size)) + 1;

     //Keeps track of how many nodes the overall tree contains
     unsigned int node_num = size;

     //Creates an array from the array pointers passed to the function
     int* scores = new int[size];
     unsigned int i = 0;
     for(int* element = scores_begin; element < scores_end; i++, element++) {
          scores[i] = *element;
     }

     //Creates two stacks, one to keep track of each level of the tree, and the other
     //to keep track of how large each level of the other stack is
     Bounded_Dequeue<int*> stack = Bounded_Dequeue<int*>(height + 1);
     Bounded_Dequeue<unsigned int> stack_size = Bounded_Dequeue<unsigned int>(height + 1);
     stack.push_front(scores);
     stack_size.push_front(size);

     //Loops for each level the tree needs to be
     for(unsigned int k = 1; k < height; k++) {
          //Take in the last level and how large the last level was to process the next level
          int* level = stack.peek_front();
          unsigned int level_size = stack_size.peek_front();

          //Each level will be half the size of the last level
          unsigned int next_size = level_size / 2;

          //If the last level was odd than add 1 to the next size
          if(level_size % 2 == 1) {
               next_size++;
          }

          int* next_level = new int[next_size];

          //Loops through the last level comparing adjacent values and adding the
          //winner to the next level
          for(unsigned int i = 0, index = 0; i < next_size; i++, index = index + 2) {

               //If there is no other element to compare add that element to the next level
               if(index + 1 == level_size) {
                    next_level[i] = level[index];
               }
               else {
                    if(level[index] > level[index + 1]) {
                         next_level[i] = level[index];
                    }
                    else {
                         next_level[i] = level[index + 1];
                    }
               }
          }

          //Push the new level to the stack and its size
          stack.push_front(next_level);
          stack_size.push_front(next_size);
          //Add the size of this level to the overall size of the tree
          node_num += next_size;

     }

     //Create array the size of the tree
     int* array = new int[node_num];

     //Convert the stack into the array to be returned
     for (unsigned int i = 0, t = 0; i < height; i++) {
          int* level = stack.pop_front();
          unsigned int level_size = stack_size.pop_front();

          for(unsigned int j = 0; j < level_size; j++, t++) {
               array[t] = level[j];
          }

          //Frees dynamically allocated memory of each level
          delete [] level;
     }

     std::cout << "node_num: " << node_num << std::endl;


     return array;
}
