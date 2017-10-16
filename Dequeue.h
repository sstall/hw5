//Dequeue.h
//Samuel Stall
//COP3503 Data Structures and Algorithms
//Defines the ADT Dequeue

#ifndef Dequeue_H
#define Dequeue_H

template <typename E>
class Dequeue {
public:
     virtual ~Dequeue() {};
     virtual void push_front(E element) = 0;
     virtual void push_back(E element) = 0;
     virtual E pop_front() = 0;
     virtual E pop_back() = 0;
     virtual E peek_front() = 0;
     virtual E peek_back() = 0;
     virtual bool is_empty() = 0;
     virtual bool is_full() = 0;
     virtual void clear() = 0;
};

#endif
