// DynamicArray.TestDriver.cpp : This is a test driver for DynamicArray.
//
//Programmer: Jiefeng Yang 
//Programmer's ID: 1791121  

#include <iostream>
#include <iomanip>
using namespace std;

#include <cassert> 
#include "DynamicArray.h"  
#include "DynamicArray.h" // ifndef test

void testInt();
void testDouble();
void testChar();
void testString();

/*int main()
{
	// Do tests with int , double , and char .
	// Also do tests with an object, like string
	testInt();
	testDouble();
	testChar();
	testString();

	return 0;
}*/


void testInt()
{
	// test code for test driver.
	// Code Refrence from course section "Apps And Test Drivers, Reading" 
	// and "Dynamic Memory And Test Drivers, Reading"
	DynamicArray<int> a; //capacity =2  (default constructor) 

	// Array::capacity
	cout << "\nTesting Data Type Int\n";
	cout << "\nTesting Array::capacity\n";
	cout << "EXPECTED: 2\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(2 == a.capacity());

	cout << "\nTesting change the capacity\n";
	a.capacity(4);
	cout << "Change capacity to 4,EXPECTED: 4\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(4 == a.capacity());

	// Array::operator[ ] setter
	cout << "\nTesting the Array::operator[ ] setter\n";
	a[0] = 6456;
	cout << "\nTesting Array::operator[ ] setter\n";
	cout << "AEXPECTED: 6456 for a[0]\n";
	cout << "ACTUAL: " << a[0] << endl;
	assert(6456 == a[0]);

	a[6] = 31231;  //apply capacity auto-adjusting for the setter if out of range high.
	a[7] = 5222;
	cout << "Auto-adjusting when out of range high. EXPECTED: 31231 for a[6]\n";
	cout << "ACTUAL: " << a[6] << endl;
	assert(31231 == a[6]);
	cout << "EXPECTED: 5222 for a[7]\n";
	cout << "ACTUAL: " << a[7] << endl;
	assert(5222 == a[7]);
	a[-1000] = int();
	cout << "Index range-checking, EXPECTED: 0 for a[-1000]\n";
	cout << "ACTUAL: " << a[-1000] << endl;
	assert(int() == a[-6]); // any out-of-range uses dummy
	assert(int() == a[100]); // checks upper end of range


	cout << "\nTesting the Array::operator[ ] getter\n";
	const DynamicArray<int> b = a;
	for (int i = 0; i < 10; i++)
		assert(a[i] == b[i]);


	// const object test
	cout << "\nConst object test\n";
	const DynamicArray<int> c(100); // if this compiles, Array::Array main constructor exists
	assert(c.capacity() == 100); // if this compiles, Array::capacity is a getter
	assert(c[0] == c[0]); // if this compiles, there is an Array::operator[ ] getter
	assert(c[-1] == c[-1]); // tests the getter's range checking

	cout << "\nTesting the copy constructor Function: Object copy test\n";
	const DynamicArray<int> d = a; // making a copy
	assert(a.capacity() == d.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == d[i]); // uses the setter version for both a and d
	  // change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i]++;
		assert(a[i] != d[i]);
	}


	// object assignment test
	cout << "\nTesting Object assignment\n";
	DynamicArray<int> e; e = a;
	assert(a.capacity() == e.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == e[i]);
	// change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i]++;
		assert(a[i] != e[i]);
	}

}

void testDouble()
{
	// test code for test driver.
    // Code Refrence from course section "Apps And Test Drivers, Reading" 
    // and "Dynamic Memory And Test Drivers, Reading"
	DynamicArray<double> a; //capacity =2  (default constructor) 

	// Array::capacity
	cout << "\nTesting Data Type Double\n";
	cout << "\nTesting Array::capacity\n";
	cout << "EXPECTED: 2\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(2 == a.capacity());

	cout << "\nTesting change the capacity\n";
	a.capacity(4);
	cout << "Change capacity to 4,EXPECTED: 4\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(4 == a.capacity());

	// Array::operator[ ] setter
	cout << "\nTesting the Array::operator[ ] setter\n";
	a[0] = 6456.4;
	cout << "\nTesting Array::operator[ ] setter\n";
	cout << "AEXPECTED: 6456.4 for a[0]\n";
	cout << "ACTUAL: " << a[0] << endl;
	assert(6456.4 == a[0]);

	a[6] = 31231.43;  //apply capacity auto-adjusting for the setter if out of range high.
	a[7] = 5222.82;
	cout << "Auto-adjusting when out of range high. EXPECTED: 31231.43 for a[6]\n";
	cout << "ACTUAL: " << a[6] << endl;
	assert(31231.43 == a[6]);
	cout << "EXPECTED: 5222.82 for a[7]\n";
	cout << "ACTUAL: " << a[7] << endl;
	assert(5222.82 == a[7]);
	a[-1000] = double();
	cout << "Index range-checking, EXPECTED: 0 for a[-1000]\n";
	cout << "ACTUAL: " << a[-1000] << endl;
	assert(double() == a[-6]); // any out-of-range uses dummy
	assert(double() == a[100]); // checks upper end of range


	cout << "\nTesting the Array::operator[ ] getter\n";
	const DynamicArray<double> b = a;
	for (int i = 0; i < 10; i++)
		assert(a[i] == b[i]);


	// const object test
	cout << "\nConst object test\n";
	const DynamicArray<double> c(100); // if this compiles, Array::Array main constructor exists
	assert(c.capacity() == 100); // if this compiles, Array::capacity is a getter
	assert(c[0] == c[0]); // if this compiles, there is an Array::operator[ ] getter
	assert(c[-1] == c[-1]); // tests the getter's range checking

	cout << "\nTesting the copy constructor Function: Object copy test\n";
	const DynamicArray<double> d = a; // making a copy
	assert(a.capacity() == d.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == d[i]); // uses the setter version for both a and d
	  // change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i]++;
		assert(a[i] != d[i]);
	}


	// object assignment test
	cout << "\nTesting Object assignment\n";
	DynamicArray<double> e; e = a;
	assert(a.capacity() == e.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == e[i]);
	// change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i]++;
		assert(a[i] != e[i]);
	}



}


void testChar()
{
	// test code for test driver.
    // Code Refrence from course section "Apps And Test Drivers, Reading" 
    // and "Dynamic Memory And Test Drivers, Reading"
	DynamicArray<char> a; //capacity =2  (default constructor) 

	// Array::capacity
	cout << "\nTesting Data Type char\n";
	cout << "\nTesting Array::capacity\n";
	cout << "EXPECTED: 2\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(2 == a.capacity());

	cout << "\nTesting change the capacity\n";
	a.capacity(4);
	cout << "Change capacity to 4,EXPECTED: 4\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(4 == a.capacity());

	// Array::operator[ ] setter
	cout << "\nTesting the Array::operator[ ] setter\n";
	a[0] = 'c';
	cout << "\nTesting Array::operator[ ] setter\n";
	cout << "AEXPECTED: c for a[0]\n";
	cout << "ACTUAL: " << a[0] << endl;
	assert('c' == a[0]);

	a[6] = 'a';  //apply capacity auto-adjusting for the setter if out of range high.
	a[7] = 'b';
	cout << "Auto-adjusting when out of range high. EXPECTED: a for a[6]\n";
	cout << "ACTUAL: " << a[6] << endl;
	assert('a' == a[6]);
	cout << "EXPECTED: b for a[7]\n";
	cout << "ACTUAL: " << a[7] << endl;
	assert('b' == a[7]);
	a[-1000] = char();
	cout << "Index range-checking, EXPECTED: '' for a[-1000]\n";
	cout << "ACTUAL: " << a[-1000] << endl;
	assert(char() == a[-6]); // any out-of-range uses dummy
	assert(char() == a[100]); // checks upper end of range


	cout << "\nTesting the Array::operator[ ] getter\n";
	const DynamicArray<char> b = a;
	for (int i = 0; i < 10; i++)
		assert(a[i] == b[i]);


	// const object test
	cout << "\nConst object test\n";
	const DynamicArray<char> c(100); // if this compiles, Array::Array main constructor exists
	assert(c.capacity() == 100); // if this compiles, Array::capacity is a getter
	assert(c[0] == c[0]); // if this compiles, there is an Array::operator[ ] getter
	assert(c[-1] == c[-1]); // tests the getter's range checking

	cout << "\nTesting the copy constructor Function: Object copy test\n";
	const DynamicArray<char> d = a; // making a copy
	assert(a.capacity() == d.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == d[i]); // uses the setter version for both a and d
	  // change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i]++;
		assert(a[i] != d[i]);
	}


	// object assignment test
	cout << "\nTesting Object assignment\n";
	DynamicArray<char> e; e = a;
	assert(a.capacity() == e.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == e[i]);
	// change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i]++;
		assert(a[i] != e[i]);
	}


}


void testString()
{
	// test code for test driver.
    // Code Refrence from course section "Apps And Test Drivers, Reading" 
    // and "Dynamic Memory And Test Drivers, Reading"
	DynamicArray<string> a; //capacity =2  (default constructor) 

	// Array::capacity
	cout << "\nTesting Data Type string\n";
	cout << "\nTesting Array::capacity\n";
	cout << "EXPECTED: 2\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(2 == a.capacity());

	cout << "\nTesting change the capacity\n";
	a.capacity(4);
	cout << "Change capacity to 4,EXPECTED: 4\n";
	cout << "ACTUAL: " << a.capacity() << endl;
	assert(4 == a.capacity());

	// Array::operator[ ] setter
	cout << "\nTesting the Array::operator[ ] setter\n";
	a[0] = "ced";
	cout << "\nTesting Array::operator[ ] setter\n";
	cout << "AEXPECTED: ced for a[0]\n";
	cout << "ACTUAL: " << a[0] << endl;
	assert("ced" == a[0]);

	a[6] = "abcef";  //apply capacity auto-adjusting for the setter if out of range high.
	a[7] = "higk";
	cout << "Auto-adjusting when out of range high. EXPECTED: abcef for a[6]\n";
	cout << "ACTUAL: " << a[6] << endl;
	assert("abcef" == a[6]);
	cout << "EXPECTED: higk for a[7]\n";
	cout << "ACTUAL: " << a[7] << endl;
	assert("higk" == a[7]);
	a[-1000] = string();
	cout << "Index range-checking, EXPECTED:   for a[-1000]\n";
	cout << "ACTUAL: " << a[-1000] << endl;
	assert(string() == a[-6]); // any out-of-range uses dummy
	assert(string() == a[100]); // checks upper end of range


	cout << "\nTesting the Array::operator[ ] getter\n";
	const DynamicArray<string> b = a;
	for (int i = 0; i < 10; i++)
		assert(a[i] == b[i]);


	// const object test
	cout << "\nConst object test\n";
	const DynamicArray<string> c(100); // if this compiles, Array::Array main constructor exists
	assert(c.capacity() == 100); // if this compiles, Array::capacity is a getter
	assert(c[0] == c[0]); // if this compiles, there is an Array::operator[ ] getter
	assert(c[-1] == c[-1]); // tests the getter's range checking

	cout << "\nTesting the copy constructor Function: Object copy test\n";
	const DynamicArray<string> d = a; // making a copy
	assert(a.capacity() == d.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == d[i]); // uses the setter version for both a and d
	  // change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i] += "d";
		assert(a[i] != d[i]);
	}


	// object assignment test
	cout << "\nTesting Object assignment\n";
	DynamicArray<string> e; e = a;
	assert(a.capacity() == e.capacity());
	for (int i = 0; i < a.capacity(); i++)
		assert(a[i] == e[i]);
	// change the content in the original array to verify it's not a shallow copy
	for (int i = 0; i < a.capacity(); i++)
	{
		a[i] += "a";
		assert(a[i] != e[i]);
	}

	
}

