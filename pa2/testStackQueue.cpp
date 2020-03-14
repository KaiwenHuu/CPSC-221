#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}

TEST_CASE("deque::push pop","[weight=1][part=deque]"){
    Deque<int> intDeque;
    vector<int> result;
    vector<int> expected;
    for (int i = 7; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intDeque.pushR(i);
    }
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 1
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 2
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 3
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 4
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 5
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 6
    cout << intDeque.peekL() << endl;

//    cout << "poppedR: " << intDeque.popR() << endl; // get rid of 10;
//    cout << "poppedR: " << intDeque.popR() << endl; // get rid of 9;
//    cout << "poppedR: " << intDeque.popR() << endl; // get rid of 8;

    while (!intDeque.isEmpty()) {
        result.push_back(intDeque.popL());
    }

    cout << "peekL: " << intDeque.peekL() << endl;
    cout << "peekR: " << intDeque.peekR() << endl;
    cout << intDeque.peekL() << endl;

    REQUIRE( result == expected);
}


TEST_CASE("deque::push pop LR","[weight = 1][part = deque]") {
    Deque<int> intDeque;
    vector<int> result;
    vector<int> expected;
    for (int i = 4; i <= 10; i++) {
        expected.push_back(i);
    }

    for(int i = 1; i <= 8; i++) {
        intDeque.pushR(i);
    }

    cout << "pushed:" << intDeque.popL() << endl; //get rid of 1
    intDeque.pushR(9); 
    cout << "pushed:" << intDeque.peekR() << endl; //pushL 9
    cout << "poppedL:" << intDeque.popL() << endl; //get rid of 2
    intDeque.pushR(10); 
    cout << "pushed:" << intDeque.peekR() << endl; //pushR 10
    cout << "poppedL:" << intDeque.popL() << endl; //get rid of 3

    while (!intDeque.isEmpty()) {
        result.push_back(intDeque.popL());
    }

    REQUIRE(result == expected);
}

TEST_CASE("deque::pop PUSH","[weight=1][part=deque]"){
    Deque<int> intDeque;
    vector<int> result;
    vector<int> expected;
    for (int i = 7; i <= 12; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intDeque.pushR(i);
    }
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 1
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 2
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 3
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 4
    intDeque.pushR(11);
    cout << "pushed: " << intDeque.peekR() << endl; // pushed 11
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 5
    intDeque.pushR(12);
    cout << "pushed: " << intDeque.peekR() << endl; // pushed 12
    cout << "poppedL: " << intDeque.popL() << endl; // get rid of 6
    cout << intDeque.peekL() << endl;

//    cout << "poppedR: " << intDeque.popR() << endl; // get rid of 10;
//    cout << "poppedR: " << intDeque.popR() << endl; // get rid of 9;
//    cout << "poppedR: " << intDeque.popR() << endl; // get rid of 8;

    while (!intDeque.isEmpty()) {
        result.push_back(intDeque.popL());
    }

    cout << "peekL: " << intDeque.peekL() << endl;
    cout << "peekR: " << intDeque.peekR() << endl;
    cout << intDeque.peekL() << endl;

    REQUIRE( result == expected);
}


