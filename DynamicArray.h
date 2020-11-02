#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template <typename T>
class DynamicArray
{
private:
    T* values;
    int cap;
    T dummy = T();
public:
    DynamicArray(int=2); // default consturctor
    DynamicArray(const DynamicArray<T>&); // copy constructor
    ~DynamicArray() {
        delete [] values;}



    DynamicArray<T>& operator=(const DynamicArray<T>&); // assignment

    int capacity() const;
    T operator[ ](int) const; //GETTER
    T& operator[ ](int); //SETTER
    void capacity(int);



};

template <typename T>       // default
DynamicArray<T>::DynamicArray(int cap)
{
    this->cap = cap;
    values = new T[cap];
    for (int i = 0; i < cap; i++)
        values[i] = T();
}

template <typename T>                         // copy
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)
{
    cap = original.cap;
    values = new T[cap];

    for (int i = 0; i < cap; i++)
        values[i] = original.values[i];
    dummy = original.dummy;
}

template <typename T>
T& DynamicArray<T>::operator[ ](int index)
{
    if (index < 0 )
        return dummy;
    if (index >= cap)
        capacity(2 * index);
    return values[index];
};

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& original)
{
  if (this != &original) // if it's not a self copy...
  {
    delete [ ] values;
    cap = original.cap;
    values = new T[cap];
    for (int i = 0; i < cap; i++)
      values[i] = original.values[i];
    dummy = original.dummy;
  }
  return *this;
};

template <typename T>
DynamicArray<T>::capacity() const
{
    return cap;
}


template <typename T>
T DynamicArray<T>::operator[ ](int index) const
{
    if (index < 0 || index >= cap)
    {
        return 0;
    }
    return values[index];
};



template <typename T>
void DynamicArray<T>::capacity(int cap)
{
  T* temp = new T[cap];
  int limit = (cap < this->cap ? cap : this->cap) ;

  for (int i = 0; i < limit; i++)
    temp[i] = values[i];

  for (int i = limit; i < cap; i++)
    temp[i] = T( );

  delete [ ] values;
  values = temp;
  this->cap = cap;
  }
;



#endif

