#ifndef STACK
#define STACK

#include "linkedlist.h"
#include "flightdata.h"
#include "node.h"

template <class T>
class Stack
{
private:
    LinkedList<T> elements;
    T top;

public:
    // Purpose: Default constructor: Doesn't do anything because there's nothing to initialize
    // Parameters: None
    // Return: None
    Stack()
    {
        // Do nothing
    }

    // Purpose: determine whether the stack is empty
    // Parameters: None
    // Return: a bool representing where the stack is empty or not
    bool isEmpty()
    {
        return elements.front == nullptr;
    }

    // Purpose: get the top element in the stack
    // Parameters: None
    // Return: a variable of type T representing the value of the top element in the stack
    T getTop()
    {
        return top;
    }

    // Purpose: add an element to the stack
    // Parameters: a variable of type T representing the element to add to the stack
    // Return: None
    void push(T val)
    {
        elements.push_front(val);
        top = val;
    }

    // Purpose: remove the top element from the stack
    // Parameters: None
    // Return: a variable of type T representing the value removed from the stack
    T pop()
    {
        T returnValue;
        if(!isEmpty())
        {
            // Pop top element
            returnValue = elements.pop_front();
            // Redefine the top element
            if(elements.front != 0)
            {
                top = elements.front->data;
            }
            return returnValue;
        }
        // If stack is already empty print error and return empty value
        std::cout << "Error: Attempt to pop from empty stack\n";
        return returnValue;
    }
};

#endif // STACK

