#ifndef Queue_H
#define Queue_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template <typename V>
class Queue
{
private:
    struct Node
    {
        V value;
        Node* next;
    };
    Node* firstNode; // head pointer
    Node* lastNode; // tail pointer
    int siz; // tracking the number of nodes
    V dummy;

public:
    Queue();                                   //  default
    Queue(const Queue<V>&);                    //  copy
    ~Queue();                                  //  delete
    Queue<V>& operator=(const Queue<V>&);      //  assignment
    void push(const V&);                       //  push
    const V& front( ) const;                   //  front
    const V& back( ) const;                    //  back
    void pop( );                               //  pop
    int size() const {return siz;}             //  size
    bool empty();                              //  empty
    void clear( );                             //  clear

};


template <typename V>       //  default main constructor
Queue<V>::Queue()
{
    firstNode = 0;
    lastNode = 0;
    siz = 0;
}




template <typename V>
Queue<V>::Queue(const Queue<V>& original)   //  copy constructor
{
    firstNode = 0;
    lastNode = 0; //  tail
    siz = original.siz;
    for (Node* p = original.firstNode; p; p = p->next)
    {
        Node* temp = new Node;
        temp->value = p->value;
        temp->next = 0;
        if (lastNode) lastNode->next = temp;
        else firstNode = temp;
        lastNode = temp;
    }
}



template <typename V> // delete
Queue<V>::~Queue( )
{
    while (firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
    }
}


template <typename V>                  // assignment
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
    if (this != &original)
    {
        // deallocate existing list
        while (firstNode)
        {
            Node* p = firstNode;
            firstNode = firstNode->next;
            delete p;
        }

        // build new queue
        lastNode = 0; //  tail
        for (Node* p = original.firstNode; p; p = p->next)
        {
            Node* temp = new Node;
            temp->value = p->value;
            temp->next = 0;
            if (lastNode) lastNode->next = temp;
            else firstNode = temp;
            lastNode = temp;
        }
        siz = original.siz;
    }
    return *this;
}




template <typename V>
void Queue<V>::push(const V& value) //  push
{
    Node* temp = new Node;
    temp->value = value;
    temp->next = 0;

    if (lastNode) lastNode->next = temp;
    else firstNode = temp;

    lastNode = temp;
    ++siz;




}





template <typename V> // empty
bool Queue<V>::empty()
{
    if (size() == 0) return true;
}


template <typename V>        //    front
const V& Queue<V>::front() const
{
    if (firstNode == 0) return dummy;
    return firstNode->value;

};

template <typename V>        //    back
const V& Queue<V>::back() const
{
    if (lastNode == 0) return dummy;
    return lastNode->value;


};

template <typename V> // clear
void Queue<V>::clear( )
{
    while (firstNode)
    {

        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --siz;
    }
    lastNode = 0;
}

template <typename V> // pop
void Queue<V>::pop( )
{
    if (firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --siz;
    }
    if (siz == 0) lastNode = 0;
}


#endif
