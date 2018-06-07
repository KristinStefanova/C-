#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

template <typename T>
class Vector{
private: // data

    T* content;
    unsigned int size;  // temporally size
    unsigned int capacity;  // maximum size

    void clearVector();
    void resizeVector();
    void copyVector(Vector<T> const&);

public: // methods && big forth

    Vector();
    Vector(unsigned int);

    Vector(Vector<T> const&);
    Vector& operator=(Vector<T> const&);

    ~Vector();

    bool isEmpty() const;
    bool isFull() const;

    T& operator[](unsigned int);
    const T& operator[](unsigned int) const;

    unsigned int getSize() const;
    unsigned int getCapacity() const;

    void insertBack(T const&);
    void deleteBack();
};

template <typename T>
Vector<T>::Vector()
{
    size = 0;
    capacity = 4;
    content = new T[capacity];
}

template <typename T>
Vector<T>::Vector(unsigned int inputCapacity)
{
    size = 0;
    capacity = inputCapacity;
    content = new T[capacity];
}

template<typename T>
Vector<T>::~Vector()
{
    this->clearVector();
}

template<typename T>
Vector<T>::Vector(Vector<T> const &otherVector)
{
    this->copyVector(otherVector);
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const &otherVector)
{
    if(this != &otherVector)
    {
        this->clearVector();
		this->copyVector(otherVector);
	}

	return *this;
}

template <typename T>
bool Vector<T>::isEmpty() const
{
    return size == 0 ? true : false;
}

template <typename T>
bool Vector<T>::isFull() const
{
    return size == capacity ? true : false;
}

template <typename T>
void Vector<T>::clearVector()
{
    delete[] content;
    content = NULL;
    capacity = 0;
    size = 0;
}

template <typename T>
void Vector<T>::copyVector(Vector<T> const &otherVector)
{
    size = otherVector.size;
    capacity = otherVector.capacity;
    content = new T[capacity];

    for(int i = 0; i < capacity; i++)
    {
        content[i] = otherVector.content[i];
    }
}

template <typename T>
void Vector<T>::resizeVector()
{
    capacity *= 2;
    T* tempContent = new T[capacity];

    for(int i = 0; i < size; i++)
    {
        tempContent[i] = content[i];
    }

    delete[] content;
    content = tempContent;
}

template <typename T>
T& Vector<T>::operator[](unsigned int index)
{
    if(index >= 0 && index < size)
        return content[index];
}

template <typename T>
const T& Vector<T>::operator[](unsigned int index) const
{
    if(index >= 0 && index < size)
        return content[index];
}

template <typename T>
unsigned int Vector<T>::getSize() const
{
    return size;
}

template <typename T>
unsigned int Vector<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
void Vector<T>::insertBack(T const& inputElement)
{
    if(isFull())
        resizeVector();
    content[size++] = inputElement;
}

template <typename T>
void Vector<T>::deleteBack()
{
    if(!isEmpty())
        size--;
}
#endif // VECTOR_H_INCLUDED
