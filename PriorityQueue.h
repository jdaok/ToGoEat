//
//  PriorityQueue.h
//  
//Programmer:      Jiefeng Yang    
//Programmer's ID: 1791121          
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <algorithm>    // std::swap

using namespace std;

template <typename V>
class PriorityQueue
{
  V* values;
  int cap;
  int siz;
  void capacity(int);
  
public:
  PriorityQueue(int = 2);
  PriorityQueue(const PriorityQueue<V>&);
  ~PriorityQueue() {delete [] values;} //Written Inline
  PriorityQueue<V>& operator=(const PriorityQueue<V>&);
  
  void push(const V&);
  void pop();
  V top() const {return siz == 0 ? V() : values[0];} //Written Inline
  int size() const {return siz;} //Written Inline
  bool empty() const {return siz == 0 ? true : false;} //Written Inline
  void clear() {siz = 0;} // Written Inline
};

//Default Constructor
template <typename V>
PriorityQueue<V>::PriorityQueue(int cap)
{
    siz = 0;
    this->cap = cap;

    values = new V[cap];
    for (int i = 0; i < cap; i++)
    {
        values[i] = V();
    }
}

//Capacity
template <typename V>
void PriorityQueue<V>::capacity(int cap)
{
    V* temp = new V[cap];
    int limit = cap < this->cap ? cap : this->cap;

    for (int i = 0; i < limit; i++)
    {
        temp[i] = values[i];
    }

    for (int i = limit; i < cap; i++)
    {
        temp[i] = V();
    }

    this->cap = cap;
    delete[] values;
    values = temp;
}

template <typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& orignal)
{
    siz = orignal.siz;
    cap = orignal.cap;
    values = new V[cap];
    for (int i = 0; i < cap; i++)
    {
        values[i] = orignal.values[i];
    }
}

template <typename V>
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V>& original)
{
    if (this != &original)
    {
        delete[] values;

        siz = original.siz;
        cap = original.cap;
        values = new V[cap];
        for (int i = 0; i < cap; i++)
        {
            values[i] = original.values[i];
        }
    }
    return *this;
}


//Push  use "max-heap" way. The largest value is at the top.
template <typename V>
void PriorityQueue<V>::push(const V& value)
{
    //Check for Full Array
    if(siz == cap)
        capacity(2 * cap);
  
    //Copy New Value
    values[siz] = value;
    //initialize index to siz for traversing "up" the tree
    int index = siz;

    //promote the newly added value to it's right place in the tree
    while (true)
    {
        //newly added value got promoted to the top
        if (index == 0)  
            break;

        // using integer division with truncation
        int parentIndex = (index - 1) / 2;

        //no more promotions
        if (values[index] < values[parentIndex]) 
            break;
      
        //index value >= parent, then promote and demote     
        swap(values[index], values[parentIndex]);  
        // traversing up the tree
        index = parentIndex; 
    }
  
    //increment Siz
    siz++;
}

//Pop   Heap Pop Option B, Avoiding The Hole
template <typename V>
void PriorityQueue<V>::pop()
{
    //add one condition here.If the queue is empty, directly return to avoid siz becoming negative.
    if (siz == 0)   
        return;

    siz--;
    int index = 0;

    while (true)
    {
        //Compute Indexes
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;

        //start to find siz's competitors
        if (siz < leftChildIndex)  //no left child, break, the value at siz "wins" by default
        {
            break;
        }
        if (siz < rightChildIndex )  //no right child
        {
            if (values[leftChildIndex] < values[siz])  //left child < VALUE at siz, brak, the value at siz "wins"
            {
                break;
            }
            else
            {
                values[index] = values[leftChildIndex];
                index = leftChildIndex; //the left child wins, but keep going!
            }
        }
        else if (values[leftChildIndex] < values[siz] && values[rightChildIndex] < values[siz])
        {
            break;  //the value at siz wins
        }
        else if (values[leftChildIndex] < values[rightChildIndex])
        {
            values[index] = values[rightChildIndex];
            index = rightChildIndex; //the right child wins, but keep going!
        }
        else
        {
            values[index] = values[leftChildIndex];
            index = leftChildIndex; //the left child wins, but keep going!
        }
        //end of finding siz's competitors
    }

    values[index] = values[siz];
}


#endif /* PriorityQueue_h */
