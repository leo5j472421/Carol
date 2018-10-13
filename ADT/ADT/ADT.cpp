// ADT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string> 
using namespace std;
#define MAX 100 
struct polynomial {
	float coef;
	int expon;

	polynomial() {
		coef = 0;
		expon = 0;
	}

	polynomial(float coef_, int expon_) {
		coef = coef_;
		expon = expon_;
	}

	void Add(float coef_) {
		coef += coef_;
	}
};

struct MyPoly {
	polynomial terms[MAX];
	int size;
	MyPoly() {
		size = 0;
	}
	MyPoly(char*) {

	}

	void ShowPloy() {
		if (size == 0)
			return;
		SortPoly();
		string result = "" ;
		result += to_string(terms[0].coef) + "X^" + to_string(terms[0].expon) + " ";
		for (int index = 1; index < size; index++) {
			result += "+ " + to_string(terms[index].coef) + "X^" + to_string(terms[index].expon) + " ";
		}

		cout << result << endl ;
	}

	void SortPoly() {
		polynomial temp ;
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (terms[i].expon < terms[j].expon) {
					temp = terms[i]; 
					terms[i] = terms[j];
					terms[j] = temp;
				}
			}
		}
	}

	void Attach(float coef, int expon) {
		polynomial p = polynomial(coef,expon);
		terms[size] = p;
		size ++ ;
	}

	int GetExponIndex(int expon) {
		for (int index = 0; index < size; index++)
			if (terms[index].expon == expon)
				return index;
		return -1 ;
	}

	void Add(MyPoly poly) {
		for (int index = 0; index < poly.size; index++) {
			Add(poly.terms[index]);
		}
	}

	void Add(polynomial poly) {
		if (GetExponIndex(poly.expon) == -1) {
			terms[size] = poly;
			size++;
		}
		else {
			terms[GetExponIndex(poly.expon)].Add(poly.coef);
		}
	}

	void SingleMult(int num) {
		for (int index = 0; index < size; index++) 
			terms[index].coef *= num;
	}

	float Lead_Exp() {
		SortPoly();
		return terms[0].expon;
	}

	void Remove(int expon) {
		for (int index = GetExponIndex(expon); index < size - 1; index++)
			terms[index] = terms[index + 1];
		size--;
	}

	void Reset() {
		for (int index = 0; index < size; index++) 
			terms[index] = polynomial(0, 0);
		size = 0;
	}

	void Assign(MyPoly poly) {
		Reset();
		for (int index = 0; index < poly.size; index++) 
			terms[index] = poly.terms[index];
		size = poly.size;
	}

	void Mult(MyPoly p) {
		MyPoly result = MyPoly();
		for (int i = 0; i < size; i++) 
			for (int j = 0; j < p.size; j++) 
				result.Add(polynomial(terms[i].coef * p.terms[j].coef, terms[i].expon + p.terms[j].expon));
		Assign(result);
	}

};
int main()
{
	MyPoly m = MyPoly();
	m.Attach(2, 7);
	m.Attach(5, 9);
	m.Attach(4.2, 6);
	m.Attach(2, 3);
	m.ShowPloy();
	MyPoly n = MyPoly();
	n.Attach(3, 5);
	n.Attach(4, 7);
	n.ShowPloy();
	m.Add(n);
	m.ShowPloy();
	m.Remove(6);
	m.ShowPloy();
	m.Mult(n);
	m.ShowPloy();
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
