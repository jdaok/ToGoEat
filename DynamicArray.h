#ifndef DynamicArray_h
#define DynamicArray_h

//Programmer: Jiefeng Yang
//Programmer's ID: 1791121

template <typename T>
class DynamicArray
{
    T* values; //T datatype CAP compasity
    int cap;
    T dummy = T();

public:
    DynamicArray(int = 2); //constructor //default = 2
    DynamicArray(const DynamicArray<T>&); //copy constructor
    ~DynamicArray() { delete[] values; } //destructor
    DynamicArray<T>& operator=(const DynamicArray<T>&); //assignment operator
    int capacity() const;
    void capacity(int); //setter
    T operator[](int) const; //getter
    T& operator[](int); //setter
};

template <typename T>
DynamicArray<T>::DynamicArray(int cap)  //constructor
{
    this->cap = cap;
    values = new T[cap];
    for (int i = 0; i < cap; i++)
        values[i] = T();

    dummy = T();
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)  //Copy Constructor
{
    cap = original.cap; // still just a copy
    values = new T[cap]; // not a copy -- new object gets its own array

    for (int i = 0; i < cap; i++) // copy the contents of the array from the original
        values[i] = original.values[i];

    dummy = original.dummy;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& original) //assignment operator
{
    if (this != &original) // of it's not a self copy...
    {
        // do what the destructor does
        delete[] values;

        // do what the copy constructor does
        cap = original.cap; // still just a copy
        values = new T[cap]; // not a copy -- new object gets its own array
        for (int i = 0; i < cap; i++) // copy the contents of the array from the original
            values[i] = original.values[i];

        dummy = original.dummy;
    }

    return *this; // return a self reference
}

template <typename T>
int DynamicArray<T>::capacity() const
{
    return cap;
}

template <typename T>
void DynamicArray<T>::capacity(int cap) //setter
{
    T* temp = new T[cap];
    int limit = (cap < this->cap ? cap : this->cap);
    for (int i = 0; i < limit; i++)
    {
        temp[i] = values[i];
    }
    for (int i = limit; i < cap; i++)
    {
        temp[i] = T();
    }

    delete[] values;
    values = temp;
    this->cap = cap;
}

template <typename T>
T DynamicArray<T>::operator[](int index) const  //getter
{
    if (index < 0) return T();
    if (index >= cap) return T();

    return values[index];
}

template <typename T>
T& DynamicArray<T>::operator[](int index)  //setter
{
    if (index < 0) return dummy;
    if (index >= cap) capacity(2 * index); // more than enough to include this index 

    return values[index];
}


#endif