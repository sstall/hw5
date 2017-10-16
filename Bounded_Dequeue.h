//Bounded_Dequeue.h
//Samuel Stall
//COP3503 hw1
//Implements the ADT Dequeue using a fixed sized array as the data store

#include "Dequeue.h"
#include <stdexcept>

template <typename E>
class Bounded_Dequeue : public Dequeue<E> {
public:
     Bounded_Dequeue(size_t cap);
     ~Bounded_Dequeue() override;
     void push_front(E element) override;
     void push_back(E element) override;
     E pop_front() override;
     E pop_back() override;
     E peek_front() override;
     E peek_back() override;
     bool is_empty() override;
     bool is_full() override;
     void clear() override;
private:
     E * const data;
     size_t capacity;
     size_t head = 0;
     size_t tail = 0;
     size_t index_forw(size_t i);
     size_t index_back(size_t i);
};

//Constructor
template <typename E>
Bounded_Dequeue<E>::Bounded_Dequeue(size_t cap)
: data(new E[cap + 1]), capacity(cap + 1) {}

//Destructor
template <typename E>
Bounded_Dequeue<E>::~Bounded_Dequeue() {
     delete [] data;
}

//Returns next index when advancing forwards through the array
template <typename E>
size_t Bounded_Dequeue<E>::index_forw(size_t i) {
     if(++i == capacity) {
          return 0;
     }
     return i;
}

//Returns next index when advancing backwards through the array
template <typename E>
size_t Bounded_Dequeue<E>::index_back(size_t i) {
     int j = i;
     if(--j == -1) {
          return capacity - 1;
     }
     return j;
}

//Pushes new element to front of Dequeue
template <typename E>
void Bounded_Dequeue<E>::push_front(E element) {
     if(is_full()) {
          throw std::runtime_error("Bounded_Dequeue<E>.push_front(): Full Dequeue");
     }
     head = index_back(head);
     data[head] = element;
}

//Pushes new element to back of Dequeue
template <typename E>
void Bounded_Dequeue<E>::push_back(E element) {
     if(is_full()) {
          throw std::runtime_error("Bounded_Dequeue<E>.push_back(): Full Dequeue");
     }
     data[tail] = element;
     tail = index_forw(tail);
}

//Head points to the head of the Dequeue so just needs to return that element
//and use index_forw() to advance to the next element in the Dequeue
template <typename E>
E Bounded_Dequeue<E>::pop_front() {
     if(is_empty()) {
          throw std::runtime_error("Bounded_Dequeue<E>.pop_front(): Empty Dequeue");
     }
     E pop = data[head];
     head = index_forw(head);
     return pop;
}

//Tail points to empty space with elements to the 'left' of it so first goes to
//the next valid index using index_back() and then returns that item
template <typename E>
E Bounded_Dequeue<E>::pop_back() {
     if(is_empty()) {
          throw std::runtime_error("Bounded_Dequeue<E>.pop_back(): Empty Dequeue");
     }
     tail = index_back(tail);
     E pop = data[tail];
     return pop;
}

template <typename E>
E Bounded_Dequeue<E>::peek_front() {
     if(is_empty()) {
          throw std::runtime_error("Bounded_Dequeue<E>.peek_front(): Empty Dequeue");
     }
     return data[head];
}

template <typename E>
E Bounded_Dequeue<E>::peek_back() {
     if(is_empty()) {
          throw std::runtime_error("Bounded_Dequeue<E>.peek_back(): Empty Dequeue");
     }
     return data[index_back(tail)];
}

//The Dequeue is only ever empty when head and tail have the same index value
template <typename E>
bool Bounded_Dequeue<E>::is_empty() {
     return (head == tail);
}

//The Dequeue is only ever full when head and tail are one index away
template <typename E>
bool Bounded_Dequeue<E>::is_full() {
     if(capacity == 1) {
          return true;
     }
     return (head == index_forw(tail));
}

template <typename E>
void Bounded_Dequeue<E>::clear() {
     head = tail = 0;
}
