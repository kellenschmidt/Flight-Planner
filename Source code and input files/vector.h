#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <class T>
class Vector
{
public:
    // Constructor: initialize memeber data
    Vector()
    {
        size = 0;
        capacity = CAPACITY_INCREMENT;
        data = new T[capacity];
    }

    // Return number of elements in array
    int getSize()
    {
        return size;
    }

    // Return allocated size of array
    int getCapacity()
    {
        return capacity;
    }

    // Return true if vector is empty (size is 0) otherwise false
    bool isEmpty()
    {
        return size == 0;
    }

    // Overloaded insert method for other data types
    // Add element to next unused spot in vector, resizing if necessary
    void push_back(T value)
    {
        // resize vector if full, the argument of zero means nothing
        resize(0);
        data[size++] = value;
    }

    // Add value to vector at location
    void insert(int loc, T value)
    {
        // increase vector capacity if full or until the index exists in the vector
        while(loc >= capacity || size==capacity)
        {
            resize(loc);
        }
        shiftRight(loc);
        data[loc] = value;
    }

    // Moves elements starting at loc one position to the right
    void shiftRight(int loc)
    {
        // loop right to left through each element that needs to be moved
        for(int i=size-1; i>=loc; i--)
        {
            // copy each element one position to the left
            data[i+1] = data[i];
        }
        size++;
    }

    // Sort numerically elements between start(inclusive) and end(inclusive)
    void sortRange(int start, int end)
    {
        // classic bubble sort
        for(int j=0; j<end-start; j++)
        {
            for(int i=start; i<end; i++)
            {
                if(data[i] > data[i+1])
                {
                    T temp = data[i];
                    data[i] = data[i+1];
                    data[i+1] = temp;
                }
            }
        }
    }

    // Remove an element at a specific location
    void removeAt(int loc)
    {
        if(validIndex(loc))
        {
            // Shift elements to the left
            for(int i=loc; i<size-1; i++)
            {
                data[i] = data[i+1];
            }
            // Forget about last element
            size--;
        }
    }

    // Access element of array using subscripting
    T& operator[](int loc)
    {
        // check for valid index size
        if(validIndex(loc))
            return data[loc];
    }

    // Return the length of the element at the index
    int getLength(int index)
    {
        T number = data[index];
        int numDigits = 0;
        // Count '0' as one digit
        if(number==0)
        {
            numDigits++;
        }
        while(number)
        {
            number /= 10;
            numDigits++;
        }
        return numDigits;
    }

    // Copy constructor
    Vector(const Vector& arg)
    {
        capacity = arg.capacity;
        size = arg.size;
        data = new T[size];
        for(int i=0; i<size; i++)
        {
            data[i] = arg.data[i];
        }
    }

    // Overloaded assignment operator
    Vector& operator=(const Vector& arg)
    {
        delete[] data;
        capacity = arg.capacity;
        size = arg.size;
        data = new T[size];
        for(int i=0; i<size; i++)
        {
            data[i] = arg.data[i];
        }
        return *this;
    }

    // Print all the elements of the vector
    void print()
    {
        // loop through all indexes and print each element
        for(int i=0; i<size; i++)
        {
            std::cout << "[" << i << "]: " << data[i] << "\n";
        }
    }

    // Check that index is populated with a value
    bool validIndex(int loc)
    {
        if(loc>=0 && loc<size)
            return true;
        else
        {
            std::cerr << "Vector index out of bounds\n";
            return false;
        }
    }

    // Destructor: deallocate memory for vectors
    /*~Vector()
    {
        delete[] data;
    }*/

private:
    T* data;
    int size;
    int capacity;
    // max amount of of unused memory in an array at any time
    // can be adjusted in future programs
    const int CAPACITY_INCREMENT = 10;

    // Increase capacity of vector
    void resize(int loc)
    {
        // true if vector is full and capacity needs to be increased
        // or if desired location is greater than capacity
        if(size==capacity || loc>=capacity)
        {
            T* tempData = new T[capacity+CAPACITY_INCREMENT];
            for(int i=0; i<size; i++)
                tempData[i] = data[i];
            delete[] data;
            data = tempData;
            // Adjust capacity for new array
            capacity+=CAPACITY_INCREMENT;
        }

        // true if vector has to much unused memory allocated to it
        // and capacity needs to be decreased
        else if(size<capacity-CAPACITY_INCREMENT)
        {
            T* tempData = new T[capacity-CAPACITY_INCREMENT];
            for(int i=0; i<size; i++)
                tempData[i] = data[i];
            delete[] data;
            data = tempData;
            // Adjust capacity for new array
            capacity-=CAPACITY_INCREMENT;
        }
    }
};

#endif // VECTOR_H
