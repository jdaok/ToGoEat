//Programmer: Jiefeng Yang
// Programmer's ID: 1791121

#include <iostream>
#include <string>
using namespace std;

#include <cassert>

#include <cstdlib>
#include "Queue.h"
#include "Queue.h" //#ifndef test

/*int main( )
{
    //String
    Queue<string> strQue;

    // Queue size test
    cout << "Queue test: string " << endl;
    cout << "----------------------------" << endl;
    cout << "Test Queue::size" << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual: " << strQue.size() << endl;
    assert(0 == strQue.size());
    cout << "Pass." << endl << endl;

    // Queue peek and push test
    cout << "Test Queue::push & Queue::front" << endl;
    strQue.push("A");
    cout << "Expected: A" << endl;
    cout << "Actual: " << strQue.front() << endl;
    assert("A" == strQue.front());
    cout << "Pass." << endl << endl;

    // Queue pop test
    cout << "Test Queue::pop" << endl;
    strQue.push("B");
    cout << "Before pop: A" << endl;
    strQue.pop();
    cout << "After pop: " << strQue.front() << endl;
    assert("B" == strQue.front());
    cout << "Pass." << endl << endl;

    // Queue back test
    cout << "Test Queue::back" << endl;
    strQue.push("B");
    cout << "Expected: B" << endl;
    cout << "Actual: " << strQue.back() << endl;
    assert("B" == strQue.back());
    cout << "Pass." << endl << endl;

    // Copy constructor
    cout << "Test copy constructor" << endl;
    Queue<string> strQue1 = strQue;
    assert(strQue1.size() == strQue.size());
    cout << "Pass." << endl << endl;

    // Assignment operator
    cout << "Test assignment operator" << endl;
    Queue<string>strQue2; strQue2 = strQue;
    while (!strQue.empty())
    {
        assert(strQue.front() == strQue2.front());
        assert(strQue.back() == strQue2.back());
        strQue.pop();
        strQue2.pop();
    }
    cout << "Pass." << endl << endl;

    // Queue clear and empty test
    cout << "Test Queue::clear & empty" << endl;
    strQue.clear();
    assert(true == strQue.empty());
    cout << "Pass." << endl << endl;

    // Constant object test
    cout << "Constant object test:" << endl;
    strQue.push("A");
    strQue.push("B");
    const Queue<string> strQue3 = strQue;
    cout << "size: " << strQue.size() << endl;
    assert(strQue3.size() == strQue.size());
    assert(strQue3.size() == strQue.size());
    assert(strQue3.front() == strQue.front());
    assert(strQue3.back() == strQue.back());
    cout << "It's NOT empty!" << endl;

    
    // Double
    Queue<double> doubleQue;
    
    cout << "Queue test: double" << endl;
    cout << "-------------------" << endl;
    
    // Queue size test
    cout << "Test Queue::size" << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual: " << doubleQue.size() << endl;
    assert(0 == doubleQue.size());
    cout << "Pass." << endl << endl;
    
    // Queue push and front test
    cout << "Test Queue::push & Queue::front" << endl;
    doubleQue.push(1.6);
    cout << "Expected: 1.6" << endl;
    cout << "Actual: " << doubleQue.front() << endl;
    assert(1.6 == doubleQue.front());
    cout << "Pass." << endl << endl;
    
    // Queue pop test
    cout << "Test Stack::pop" << endl;
    doubleQue.push(2.8);
    cout << "Before pop: 1.6" << endl;
    doubleQue.pop();
    cout << "After pop: " << doubleQue.front() << endl;
    assert(2.8 == doubleQue.front());
    cout << "Pass." << endl << endl;
    
    // Queue back test
    cout << "Test Queue::back" << endl;
    doubleQue.push(2.8);
    cout << "Expected: 2.8" << endl;
    cout << "Actual: " << doubleQue.back() << endl;
    assert(2.8 == doubleQue.back());
    cout << "Pass." << endl << endl;
    
    // Copy constructor
    cout << "Test copy constructor" << endl;
    Queue<double> doubleQue2 = doubleQue;
    assert(doubleQue2.size() == doubleQue.size());
    cout << "Pass." << endl << endl;
    
    // Assignment operator
    cout << "Test assignment operator" << endl;
    Queue<double>doubleQue3; doubleQue3 = doubleQue;
    assert(doubleQue3.size() == doubleQue.size());
    assert(doubleQue3.front() == doubleQue.front());
    cout << "Pass." << endl << endl;
    
    // Stack clear and empty test
    cout << "Test Queue::clear & empty" << endl;
    doubleQue.clear();
    assert(true == doubleQue.empty());
    cout << "Pass." << endl << endl;

    // Constant object test
    doubleQue.push(1.6);
    doubleQue.push(2.8);
    cout << "Constant object test:" << endl;
    const Queue<double> doubleQue4 = doubleQue;
    cout << "size: " << doubleQue4.size() << endl;
    assert(doubleQue4.size() == doubleQue.size());
    assert(doubleQue4.empty() == doubleQue.empty());
    assert(doubleQue4.back() == doubleQue.back());
    assert(doubleQue4.front() == doubleQue.front());
    cout << "It's NOT empty!" << endl;

    cout << "Done!";
}*/
