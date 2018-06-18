#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "Vector.h"
using namespace std;

template <typename T>
class MinHeap
{
private:

    Vector<T> vec;

    void bubbleDown(unsigned int);
    void bubbleUp(unsigned int);

    void constructHeap();

public:

    MinHeap(){}

    MinHeap(const T*, const unsigned int);
    MinHeap(Vector<T> const&);

    ~MinHeap(){}

    bool isEmpty() const;
    unsigned int getSize() const;

    void insertNew(T const&);
    T getMin() const;
    void deleteMin();
};

template <typename T>
MinHeap<T>::MinHeap(const T* arr, const unsigned int length)
{
    for(int i = 0; i < length; i++)
        vec.insertBack(arr[i]);

    constructHeap();
}

template <typename T>
MinHeap<T>::MinHeap(Vector<T> const& other)
{
    vec = other;
    constructHeap();
}

template <typename T>
bool MinHeap<T>::isEmpty() const
{
    return vec.isEmpty();
}

template <typename T>
unsigned int MinHeap<T>::getSize() const
{
    return vec.getSize();
}

template <typename T>
bool compare(T *f, T *s)
{
    return *(f) < *(s);
}

template <typename T>
bool compare(T f, T s)
{
    return f < s;
}

/* We assume that leaves never break the rule*/
template <typename T>
void MinHeap<T>::constructHeap()
{
    int length = vec.getSize();
    for(int i = length - 1; i >= 0; i--)
    {
        bubbleDown(i);
    }
}

template <typename T>
void MinHeap<T>::bubbleDown(unsigned int index)
{
    int length = vec.getSize();

    int indexLeft = 2 * index + 1;  // index of left child
    int indexRight = 2 * index + 2; // index of right child

    if(indexLeft >= length) // if is leaf don't
        return;

    int minIndex = index;

    if(compare(vec[indexLeft], vec[index])) // if parent is greater than his left child
    {
        minIndex = indexLeft;
    }

    if((indexRight < length) && compare(vec[indexRight], vec[minIndex]))  // if parent is greater than his right child(koeto ne izliza izwyn razmera)
    {
        minIndex = indexRight;
    }

    if(minIndex != index)
    {
        //swap index with minIndex
        T temp = vec[index];
        vec[index] = vec[minIndex];
        vec[minIndex] = temp;

        bubbleDown(minIndex);
    }
}

template <typename T>
void MinHeap<T>::bubbleUp(unsigned int index)
{
    if(index == 0)  // if is root don't
        return;

    int parentIndex = (index-1) / 2;

    if(compare(vec[index], vec[parentIndex]))
    {
        // swap index and its parent
        T temp = vec[parentIndex];
        vec[parentIndex] = vec[index];
        vec[index] = temp;

        bubbleUp(parentIndex);
    }
}

template <typename T>
void MinHeap<T>::insertNew(T const& newValue)
{
    vec.insertBack(newValue);
    bubbleUp(vec.getSize() - 1);
}

template <typename T>
T MinHeap<T>::getMin() const
{
    if(!isEmpty())
        return vec[0];
}

template <typename T>
void MinHeap<T>::deleteMin()
{
    if(isEmpty())
        return;

    int length = vec.getSize();

    //swap first and last
    T temp = vec[0];
    vec[0] = vec[length - 1];
    vec[length - 1] = temp;

    vec.deleteBack();

    bubbleDown(0);

}
#endif // HEAP_H_INCLUDED
