#pragma once
#include<string>
#include<iostream>
using namespace std;

template<class T>
void changeArrayLength(T*& a, int oldLength, int newLength)
{

	T* temp = new T[newLength];              // new array
	//int number = min(oldLength, newLength);  // number to copy
	copy(a, a + oldLength, temp);
	delete[] a;                             // deallocate old memory
	a = temp;
}