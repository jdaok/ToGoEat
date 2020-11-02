#ifndef ASSOCIATEDARRAY_H
#define ASSOCIATEDARRAY_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "Queue.h"


using namespace std;

template <typename K, typename V>
class AssociativeArray
{
    struct Node
    {
        K key;
        V value;
        bool inUse;
    };
    Node* data;
    int cap;
    int siz;
    void capacity(int);

public:

    AssociativeArray(int=2);                                          // default constructor
    AssociativeArray(const AssociativeArray<K,V>&);                   // copy constructor
    AssociativeArray<K,V>& operator=(const AssociativeArray<K,V>&);   // assignment operator
    ~AssociativeArray()
    {
        delete [] data;   // deleter
    }
    V operator[ ](const K&) const;            // getter
    V& operator[ ](const K&);                 // setter
    bool containsKey(const K&) const;
    void deleteKey(const K&);
    Queue<K> keys()const;
    int size()const
    {
        return siz;
    }
    void clear();
};




template <typename K, typename V>                                                // copy
AssociativeArray<K,V>::AssociativeArray(const AssociativeArray<K,V>& original)
{
    cap = original.cap;
    siz = original.siz;

    data = new Node[cap];

    for (int i = 0; i < cap; i++)
        data[i] = original.data[i];
}

template <typename K, typename V>                                                              // assignment
AssociativeArray<K,V>& AssociativeArray<K,V>::operator=(const AssociativeArray<K,V>& original)
{
    if (this != &original) // if it's not a self copy...
    {
        delete [ ] data;
        cap = original.cap;
        data = new Node[cap];
        for (int i = 0; i < cap; i++)
            data[i] = original.data[i];
        siz = original.siz;
    }
    return *this;
};




template <typename K, typename V>                                        // default
AssociativeArray<K,V>::AssociativeArray(int cap)
{
    this->cap = cap;
    this->siz = 0;

    data = new Node[cap];
    for (int i = 0; i < cap; i++)
        data[i].inUse = false;
};

template <typename K, typename V>                                        // getter
V AssociativeArray<K,V>::operator[ ](const K& searchKey) const
{
    for (int i = 0; i < cap; i++)
    {
        if (data[i].key == searchKey && data[i].inUse)
        {
            return data[i].value;
        }
    }
    V dummy;
    return dummy;
};

template <typename K, typename V>                                         // setter
V& AssociativeArray<K,V>::operator[ ](const K& searchKey)
{
    V dummy;
    int indexOfFirstUnusedKey = cap;
    for (int i = 0; i < cap; i++)
    {
        if (data[i].inUse)
        {
            if (data[i].key == searchKey) // K must support ==
                return data[i].value;
        }
        else if (indexOfFirstUnusedKey == cap) // no not in-use found yet
            indexOfFirstUnusedKey = i; // this is the first one -- remember it
    }

    // CREATE new node
    if (indexOfFirstUnusedKey == cap) capacity(1+ cap);
    data[indexOfFirstUnusedKey].key = searchKey;
    data[indexOfFirstUnusedKey].value = dummy;
    data[indexOfFirstUnusedKey].inUse = true;
    siz++;
    return data[indexOfFirstUnusedKey].value;




};



template <typename K, typename V>                                         // contains key?
bool AssociativeArray<K,V>::containsKey(const K& searchKey) const
{
    for (int i = 0; i < cap; i++)
    {
        if (data[i].key == searchKey && data[i].inUse)
        {
            return true;
        }
    }
    return false;
};

template <typename K, typename V>                                         // delete Key!
void AssociativeArray<K,V>::deleteKey(const K& searchKey)
{
    for (int i = 0; i < cap; i++)
    {
        if (data[i].key == searchKey && data[i].inUse)
        {
            data[i].inUse = false;
            siz--;
            return;
        }
    }
    return;
};


template <typename K, typename V>                                         // clear all
void AssociativeArray<K,V>::clear()
{
    for (int i = 0; i < cap; i++)
    {
        data[i].inUse = false;
    }
    siz = 0;
};

template <typename K, typename V>                                                      // update capacity
void AssociativeArray<K,V>::capacity(int cap)
{
    Node dummy;



    Node* temp = new Node[cap];
    int limit = (cap < this->cap ? cap : this->cap) ;

    for (int i = 0; i < limit; i++)
        temp[i] = data[i];

    for (int i = limit; i < cap; i++)
        temp[i] = dummy;

    delete [ ] data;
    data = temp;
    this->cap = cap;
}
;

template <typename K, typename V>
Queue<K> AssociativeArray<K,V>::keys() const
{
    Queue <K> keys;
    for (int i = 0; i < cap; i++)
    {
        if (data[i].inUse)
        {
            keys.push(data[i].key);
        }
    }

    return keys;
};








#endif

