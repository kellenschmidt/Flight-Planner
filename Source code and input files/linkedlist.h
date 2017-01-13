#ifndef LINKEDLIST
#define LINKEDLIST

#include "node.h"
#include "flightdata.h"
#include <iostream>

template <class T>
class LinkedList
{
private:
    Node<T>* front;

public:
    // Purpose: Set default values for LinkedList object
    // Parameters: None
    // Return: None
    LinkedList() : front(nullptr) {}

    // Purpose: add new node to the front of the list
    // Parameters: a variable of type T representing the value to be inserted
    // Return: None
    void push_front(T val)
    {
        Node<T>* x = new Node<T>;
        x->data = val;
        x->next = front;
        front = x;
    }

    // Purpose: add new node to the back of the list
    // Parameters: a variable of type T representing the value to be inserted
    // Return: None
    void push_back(T val)
    {
        Node<T>* curr = front;
        if(front == nullptr)
        {
            front = new Node<T> (val);
        }
        else{
            // Temporary node used to iterate along linked list
            while(curr->next != nullptr)
            {
                curr = curr->next;
            }
            curr->next = new Node<T> (val);
        }
    }

    // Purpose: remove a node from the front of the list
    // Parameters: None
    // Return: a variable of type T representing the value in the node that was removed
    T pop_front()
    {
        T temp = front->data;
        front = front->next;
        return temp;
    }

    // Purpose: output all the the elements in the list
    // Parameters: None
    // Return: None
    void print()
    {
        Node<T>* curr = front;
        while(curr != nullptr)
        {
            std::cout << curr->data.getDestination() << " ";
            curr = curr->next;
        }
    }

    template<class Type> friend class AdjacencyList;
    template<class Type> friend class Stack;
    friend class FlightPlanner;
};

#endif // LINKEDLIST

