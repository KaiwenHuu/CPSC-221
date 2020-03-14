/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

#include "deque.h"
#include <iostream>

/* No argument constructor */
template<class T>
Deque<T>::Deque(): n1(-1), n2(0)
{
    /* do nothing */
    /* constructor creates an empty deque */
}



/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    if (n1 == -1) { /* if deque is empty */
        n1++;
    }
    // increase num of size by 1
    n2++;
    // push item to back of vector
    data.push_back(newItem);
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL() {
    // store left most element in a local variable
    T temp = data[n1];
    // instantiate an empty vector
    vector<T> tempVector;
    // reduce size by 1
    n2--;
    // shift the left most index by one to the right
    n1++;
    // case if deque is empty after popL()
    if (isEmpty()) {
        n1 = -1;
        data = tempVector;
    }
    // resize if data elements can fit in 0...n1-1
    if (n1 >= n2) {
        for (int i = n1; i < n1 + n2; i++) {
            tempVector.push_back(data[i]);
        }
        n1 = 0;
        data = tempVector;
    }
        return temp;
}



/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR() {
    // store right most element in a local variable
    T temp = data[n1 + n2 - 1];
    data.pop_back();
    vector<T> tempVector;
    n2--;
    // case if data is empty after data.popback()
    if (isEmpty()) {
        n1 = -1;
        data = tempVector;
    }
    // resize if data elements can fit in 0...n1-1
    if (n1 >= n2) {
        for (int i = n1; i < n1 + n2 ; i++) {
            tempVector.push_back(data[i]);
        }
        n1 = 0;
        data = tempVector;
    }
    return temp;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    cout << "size: " << data.size() << endl;
    return data[n1];
}



/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[n1+n2-1];
}



/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return n2 == 0;
}
