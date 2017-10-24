//TT.cpp
//Samuel Stall
//Creates a tournament tree in packed array representation give an array of scores
//COP3530 Data Structures and Algorithms

#include <iostream>
#include <cmath>
#include "Bounded_Dequeue.h"

int* makeTT(int* scores_begin, int* scores_end);

int main() {

     int array[] = {1, 2, 3, 4, 5};

     int* tournament = makeTT(array, &array[5]);

     for(unsigned int i = 0; i < 16; i++) {
          std::cout << tournament[i] << " ";
     }

     std::cout << std::endl;


     return 0;
}

int* makeTT(int* scores_begin, int* scores_end) {
     //Finds the size of the array passed
     unsigned int size = scores_end - scores_begin;

     //Calculates the height of the tournament
     unsigned int height = ceil(log2(size)) + 1;

     //Keeps track of how many nodes the overall tree contains
     unsigned int node_num = exp2(height);

     //Creates an array from the array pointers passed to the function
     int* scores = new int[size];
     unsigned int i = 0;
     for(int* element = scores_begin; element < scores_end; i++, element++) {
          scores[i] = *element;
     }

     int* array = new int[node_num];

     //The first index of the bottom of the tree is 2^height so this transfers all the
     //passed in scores to the tree
     for(unsigned int i = exp2(height - 1), j = 0; j < size; i++, j++) {
          array[i] = scores[j];
     }

     //Goes through the tree finding the proper parent to the two children
     for(int k = height - 1; k > -1; k--) {
          for(unsigned int i = exp2(k); i < exp2(k + 1) - 1; i+=2) {
               if(array[i] > array[i + 1]) {
                    array[i/2] = array[i];
               }
               else {
                    array[i/2] = array[i + 1];
               }
          }
     }

     return array;
}
