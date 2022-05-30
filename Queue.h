#ifndef QUEUE_H
#define QUEUE_H


#include <iostream>
#include <new>

static int EXPANSION = 7;
static int START_OF_QUEUE = 0;
static int NEXT_ITEM = 1;

// start working inside Class Queue
template <class T>
class Queue
{
    int m_numOfItems;
    int m_length;
    T* m_items;

    //method for getting item from the array
    // in Private
    T* getItems() const
    {
        return m_items;
    }


    // method for expanding the array for new items if there no empty space in the array
    //in Private
    void expand()
    {
        try {
            T* newArray= new T[m_length+EXPANSION];
            for (int i = START_OF_QUEUE; i < m_numOfItems; ++i) {
                newArray[i] = m_items[i];
            }
            delete[] m_items;
            m_items=newArray;
            m_length+=EXPANSION;
        }
        catch (const std::bad_alloc &e) {
            throw std::bad_alloc();
        }
    }


public:
    class EmptyQueue{};
    Queue()
    {
        m_length = START_OF_QUEUE;
        m_numOfItems = START_OF_QUEUE;
        m_items= nullptr;
    }

    Queue(const Queue<T>& otherQueue)
    {
        try {
            T* newArray= new T[otherQueue.size()];
            for (int i = START_OF_QUEUE; i < otherQueue.size(); ++i) {
                newArray[i] = otherQueue.getItems()[i];
            }
            m_items=newArray;
            m_length=otherQueue.size();
            m_numOfItems=otherQueue.size();
        }
        catch (const std::bad_alloc &e) {
            throw std::bad_alloc();
        }
    }


    Queue<T>& operator=(const Queue<T>& otherQueue)
    {
        if(this==&otherQueue){
            return *this;
        }
        try {
            T *newArray = new T[otherQueue.size()];
            for (int i = START_OF_QUEUE; i < otherQueue.size(); ++i) {
                newArray[i] = otherQueue.getItems()[i];
            }
            delete[] m_items;
            m_items = newArray;
            m_length = otherQueue.size();
            m_numOfItems = otherQueue.size();
        }
        catch (const std::bad_alloc &e) {
            throw std::bad_alloc();
        }
        return *this;
    }


    ~Queue()
    {
        delete[] m_items;
    }


    int size() const
    {
        return m_numOfItems;
    }


    void pushBack(const T& newItem)
    {
        if(m_numOfItems>=m_length){
            expand();
        }
        m_items[m_numOfItems++]=newItem;
    }

    T& front() const
    {
        if(m_numOfItems==START_OF_QUEUE){
            throw EmptyQueue();
        }
        return m_items[START_OF_QUEUE];
    }

    
    void popFront()
    {
        if(m_numOfItems==START_OF_QUEUE){
            throw EmptyQueue();
        }
        for(int i=START_OF_QUEUE;i<size()-1;++i){
            m_items[i]=m_items[i+NEXT_ITEM];
        }
        --m_numOfItems;
    }

    //Start working on  class ConstIterator 
    class ConstIterator 
    {
        const Queue<T>* m_queue;
        int m_index;
        explicit ConstIterator(const Queue<T>* queue,int index):
        m_queue(queue), m_index(index)
        {}
        friend class Queue;
        // using friend to let Queue use the c'tor of ConstIterator

    public:
        ~ConstIterator() {}
        class InvalidOperation{};
        ConstIterator(const ConstIterator&) = default;
        ConstIterator& operator=(const ConstIterator&) = default;

        bool operator!=(Queue<T>::ConstIterator otherIterator)
            {
                return m_index!=otherIterator.m_index;
            }

        T& operator*() const
        {
            if(m_index<START_OF_QUEUE||
               m_index>=m_queue->size()){
                throw InvalidOperation();
            }
            return m_queue->m_items[m_index];
        }

        ConstIterator& operator++()
        {
            if(m_index>=m_queue->size()){
                throw InvalidOperation();
            }
            ++m_index;
            return *this;
        }
    };

    // stop working inside Class ConstIterator
    ConstIterator begin() const
    {
        ConstIterator toSend(this, START_OF_QUEUE);
        return toSend;
    }

    ConstIterator end() const
    {
        ConstIterator toSend(this, m_numOfItems);
        return toSend;
    }

    // start working inside class Iterator
    class Iterator
    {
        Queue<T>* m_queue;
        int m_index;
        explicit Iterator(Queue<T>* queue,int index):
            m_queue(queue), m_index(index)
        {}
        friend class Queue;
        // using friend to let Queue use the c'tor of Iterator

    public:
        ~Iterator() {}
        class InvalidOperation{};
        Iterator(const Iterator&) = default;
        Iterator& operator=(const Iterator&) = default;


        bool operator!=(Queue<T>::Iterator otherIterator)
        {
            return m_index!=otherIterator.m_index;
        }


        T& operator*()
        {
            if(m_index<START_OF_QUEUE||
               m_index>=m_queue->size()){
                throw InvalidOperation();
            }
            return m_queue->m_items[m_index];
        }

        Iterator& operator++()
        {
            if(m_index>=m_queue->size()){
                throw InvalidOperation();
            }
            ++m_index;
            return *this;
        }
    };
    // stop working inside class Iterator


    Iterator begin()
    {
        Iterator toSend(this, START_OF_QUEUE);
        return toSend;
    }


    Iterator end()
    {
        Iterator toSend(this, m_numOfItems);
        return toSend;
    }
};

// stop working inside Class Queue
template<class T, typename F>
Queue<T> filter(const Queue<T>& queue, F condition)
{
    Queue<T> newQueue;
    for(typename Queue<T>::ConstIterator i=queue.begin();i!=queue.end();++i){
        if(condition(*i)) {
            newQueue.pushBack(*i);
        }
    }
    return newQueue;
}

template<class T, typename F>
void transform(Queue<T>& queue, F condition)
{
    for(typename Queue<T>::Iterator i=queue.begin();i!=queue.end();++i){
        condition(*i);
    }
}

#endif
