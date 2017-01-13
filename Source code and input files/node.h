#ifndef NODE_H
#define NODE_H

template <class T>
class Node
{
private:
    T data;
    Node<T>* next;

public:
    // Purpose: Set default values for Node object
    // Parameters: None
    // Return: None
    Node() : next(nullptr) {}

    // Purpose: create a node with a data value
    // Parameters: a variable of type T representing the value of the new node
    // Return: None
    Node(T d) : data(d), next(nullptr) {}

    // Purpose: set the data field of the node
    // Parameters: a variable of type T representing the value to set data to
    // Return: None
    void setData(T x)
    {
        data = x;
    }

    // Purpose: get what is in the data field of the node
    // Parameters: None
    // Return: a variable of type T representing the value of data
    T getData()
    {
        return data;
    }

    template<class Type> friend class LinkedList;
    template<class Type> friend class AdjacencyList;
    template<class Type> friend class Stack;
    friend class FlightPlanner;
};

#endif // NODE_H
