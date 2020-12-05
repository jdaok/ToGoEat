//
//  Queue.h
//  
//Programmer:Jiefeng Yang
//Programmer's ID:1791121

#ifndef Queue_h
#define Queue_h

template <typename V>
class Queue
{
    struct Node
    {
        V value;
        Node* next;
    };

    Node* firstNode; //head pointer
    Node* lastNode; //tail pointer
    int siz;
    V dummy;

public:
    Queue(); //main constructor
    Queue(const Queue<V>&);
    ~Queue();
    Queue<V>& operator=(const Queue<V>&);
    void push(const V&);
    const V& front() const; //return a immutable reference to the oldest node
    const V& back() const; //return a immutable reference to the newest node
    void pop();
    int size() const;
    bool empty() const;
    void clear();
};

template <typename V>
Queue<V>::Queue()
{
    firstNode = 0;
    lastNode = 0;
    siz = 0;
    dummy = V();
};

//Copy Constructor
template <typename V>
Queue<V>::Queue(const Queue<V>& original)
{
    firstNode = 0;
    lastNode = 0; //tail
    siz = original.siz;
    dummy = V();
    for(Node* p = original.firstNode; p; p = p->next)
    {
        Node* temp = new Node;
        temp->value = p->value;
        temp->next = 0;
        if(lastNode)
            lastNode->next = temp;
        else
            firstNode = temp;
        lastNode = temp;
    }
}

//Assignment Operator
template <typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
    if(this != &original)
    {
        //deallocate existing list
        while(firstNode)
        {
            Node* p = firstNode;
            firstNode = firstNode->next;
            delete p;
        }

        //build new queue
        lastNode = 0; //tail
        for(Node* p = original.firstNode; p; p = p->next)
        {
            Node* temp = new Node;
            temp->value = p->value;
            temp->next = 0;
            if(lastNode)
                lastNode->next = temp;
            else
                firstNode = temp;
            lastNode = temp;
        }
        siz = original.siz;
    }
    return *this;
}


//Push
template <typename V>
void Queue<V>::push(const V& value)
{
    Node* temp = new Node;
    temp->value = value;
    temp->next = 0;
    if(lastNode) 
        lastNode->next = temp;
    else 
        firstNode = temp;
    lastNode = temp;
    ++siz;
}

//Destructor
template <typename V>
Queue<V>::~Queue()
{
    while(firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
    }
}


//Front
template <typename V>
const V& Queue<V>::front() const
{
    if(firstNode == 0)
        return dummy;
    else
        return firstNode->value;
}

//Back
template <typename V>
const V& Queue<V>::back() const
{
    if(lastNode == 0)
        return dummy;
    else
        return lastNode->value;
}

//Pop
template <typename V>
void Queue<V>::pop()
{
    if(firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --siz;
        if (siz == 0)
            lastNode = 0;
    }
}

//Clear
template <typename V>
void Queue<V>::clear()
{
    while(firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --siz;
    }
    lastNode = 0;
}


template <typename V>
int Queue<V>::size() const
{
    return siz;
}

template <typename V>
bool Queue<V>::empty() const
{ 
    return siz == 0; 
}


#endif 
