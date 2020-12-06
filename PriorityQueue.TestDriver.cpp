//Programmer: Jiefeng Yang
// Programmer's ID: 1791121

#include <iostream>
#include <string>
using namespace std;

#include <cassert>

#include <cstdlib>
#include "PriorityQueue.h"
#include "PriorityQueue.h" //#ifndef test

/*int main( )
{
    //String
    PriorityQueue<string> strQue;

    // PriorityQueue size test
    cout << "PriorityQueue test: string " << endl;
    cout << "----------------------------" << endl;
    cout << "Test PriorityQueue::size" << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual: " << strQue.size() << endl;
    assert(0 == strQue.size());
    cout << "Pass." << endl << endl;

    // PriorityQueue peek and push test
    cout << "Test PriorityQueue::push & PriorityQueue::top" << endl;
    strQue.push("A");
    cout << "Expected: A" << endl;
    cout << "Actual: " << strQue.top() << endl;
    assert("A" == strQue.top());
    cout << "Pass." << endl << endl;

    // PriorityQueue pop test
    cout << "Test PriorityQueue::pop" << endl;
    strQue.push("B");
    cout << "Before pop: B" << endl;
    strQue.pop();
    cout << "After pop: " << strQue.top() << endl;
    assert("A" == strQue.top());
    cout << "Pass." << endl << endl;


    // Copy constructor
    cout << "Test copy constructor" << endl;
    PriorityQueue<string> strQue1 = strQue;
    assert(strQue1.size() == strQue.size());
    cout << "Pass." << endl << endl;

    // Assignment operator
    cout << "Test assignment operator" << endl;
    PriorityQueue<string>strQue2; strQue2 = strQue;
    while (!strQue.empty())
    {
        assert(strQue.top() == strQue2.top());
        strQue.pop();
        strQue2.pop();
    }
    cout << "Pass." << endl << endl;

    // PriorityQueue clear and empty test
    cout << "Test PriorityQueue::clear & empty" << endl;
    strQue.clear();
    assert(true == strQue.empty());
    cout << "Pass." << endl << endl;

    // Constant object test
    cout << "Constant object test:" << endl;
    strQue.push("A");
    strQue.push("B");
    const PriorityQueue<string> strQue3 = strQue;
    cout << "size: " << strQue.size() << endl;
    assert(strQue3.size() == strQue.size());
    assert(strQue3.size() == strQue.size());
    assert(strQue3.top() == strQue.top());
    cout << "It's NOT empty!" << endl;

    
    // Double
    PriorityQueue<double> doubleQue;
    
    cout << "PriorityQueue test: double" << endl;
    cout << "-------------------" << endl;
    
    // PriorityQueue size test
    cout << "Test PriorityQueue::size" << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual: " << doubleQue.size() << endl;
    assert(0 == doubleQue.size());
    cout << "Pass." << endl << endl;
    
    // PriorityQueue push and Top test
    cout << "Test PriorityQueue::push & PriorityQueue::top" << endl;
    doubleQue.push(1.6);
    cout << "Expected: 1.6" << endl;
    cout << "Actual: " << doubleQue.top() << endl;
    assert(1.6 == doubleQue.top());
    cout << "Pass." << endl << endl;
    
    // PriorityQueue pop test
    cout << "Test Stack::pop" << endl;
    doubleQue.push(2.8);
    cout << "Before pop:" << endl;
    doubleQue.pop();
    cout << "After pop: " << doubleQue.top() << endl;
    assert(1.6 == doubleQue.top());
    cout << "Pass." << endl << endl;
    
   
    // Copy constructor
    cout << "Test copy constructor" << endl;
    PriorityQueue<double> doubleQue2 = doubleQue;
    assert(doubleQue2.size() == doubleQue.size());
    cout << "Pass." << endl << endl;
    
    // Assignment operator
    cout << "Test assignment operator" << endl;
    PriorityQueue<double>doubleQue3; doubleQue3 = doubleQue;
    assert(doubleQue3.size() == doubleQue.size());
    assert(doubleQue3.top() == doubleQue.top());
    cout << "Pass." << endl << endl;
    
    // Stack clear and empty test
    cout << "Test PriorityQueue::clear & empty" << endl;
    doubleQue.clear();
    assert(true == doubleQue.empty());
    cout << "Pass." << endl << endl;

    // Constant object test
    doubleQue.push(1.6);
    doubleQue.push(2.8);
    cout << "Constant object test:" << endl;
    const PriorityQueue<double> doubleQue4 = doubleQue;
    cout << "size: " << doubleQue4.size() << endl;
    assert(doubleQue4.size() == doubleQue.size());
    assert(doubleQue4.empty() == doubleQue.empty());
    assert(doubleQue4.top() == doubleQue.top());
    cout << "It's NOT empty!" << endl;

    cout << "Done!";
}*/
