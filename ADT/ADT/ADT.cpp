// ADT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
#define MAX 100
struct polynomial {
	float coef; //係數
	int expon;  //指數

	polynomial() {
		coef = 0;
		expon = 0;
	}

	polynomial(float coef_, int expon_) {
		coef = coef_;
		expon = expon_;
	}

	void Add(float coef_) { coef = coef + coef_; }
};

struct MyPoly {
	polynomial terms[MAX]; //陣列可以放一百個
	int size;

	MyPoly() { size = 0; }

	MyPoly(char *) {}

	string
		formatFloat(float f) { // float 轉 string 並且捨去0 的部分  1.23000 => "1.23"
		string str = to_string(f);

		for (int index = str.size() - 1; index >= 0; index--) {
			if (str[index] != '0') {
				str = str.substr(0, index + 1);
			}
		}

		if (str[str.size() - 1] == '.')
			return str.substr(0, str[str.size() - 1]);
		return str;
	}

	void ShowPloy() { // ?啣憭?撘摰?
		if (size == 0)
			return;
		SortPoly();
		string result = "";
		result +=
			formatFloat(terms[0].coef) + "X^" + to_string(terms[0].expon) + " ";
		for (int index = 1; index < size; index++) {
			if (terms[index].expon != 0)
				result += "+ " + formatFloat(terms[index].coef) + "X^" + //?嗾??撘停頝嗾甈? 
				to_string(terms[index].expon) + " ";
			else
				result += "+ " + formatFloat(terms[index].coef) + " ";
		}

		cout << result << endl;
	}

	void SortPoly() { // 依係數排序多項式 泡沫排序法 
		polynomial temp;
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

	void Attach(float coef, int expon) { // 新增項式
		polynomial p = polynomial(coef, expon);
		Add(p);
	}

	int GetExponIndex(int expon) { // 取得該指數在terms裡面的index如果不存在回傳-1
		for (int index = 0; index < size; index++)
			if (terms[index].expon == expon)
				return index;
		return -1;
	}

	void Add(MyPoly poly) { // 多項式相加
		for (int index = 0; index < poly.size; index++) {
			Add(poly.terms[index]);
		}
	}

	void Add(polynomial poly) { // 新增項式
		if (GetExponIndex(poly.expon) == -1) {
			terms[size] = poly;
			size++;
		}
		else {
			terms[GetExponIndex(poly.expon)].Add(poly.coef);
		}
	}

	void SingleMult(int num) { //多項式乘上數字
		for (int index = 0; index < size; index++)
			terms[index].coef = terms[index].coef * num;
	}

	float Lead_Exp() { // 回傳最高指數的係數

		SortPoly();
		return terms[0].coef;
	}

	void Remove(int expon) { // 移除該指數的項式
		for (int index = GetExponIndex(expon); index < size - 1; index++)
			terms[index] = terms[index + 1];
		size--;
	}

	void Reset() { // 清空多項式

		for (int index = 0; index < size; index++)
			terms[index] = polynomial(0, 0);
		size = 0;
	}

	void Assign(MyPoly poly) { // 存入傳進來的多項式
		Reset();
		for (int index = 0; index < poly.size; index++)
			terms[index] = poly.terms[index];
		size = poly.size;
	}

	void Mult(MyPoly p) { // 乘上傳入的多項式
		MyPoly result = MyPoly();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < p.size; j++)
				result.Add(polynomial(terms[i].coef * p.terms[j].coef,
					terms[i].expon + p.terms[j].expon));
		Assign(result);
	}
};

MyPoly ReadFile(string filename) { // 讀黨
	MyPoly p = MyPoly();
	int num = 1;
	FILE *fptr;
	float coef;
	int expon;
	fptr = fopen(filename.c_str(), "r");
	if (fptr != NULL) {
		while (true) {
			num = fscanf(fptr, "%f%d", &coef, &expon);
			if (num == -1) // End Of File
				break;
			p.Add(polynomial(coef, expon));
		}
	}
	else
		cout << "cant find " << filename << endl;
	p.ShowPloy();
	return p;
}

int main() {
	MyPoly p = MyPoly();
	MyPoly p2 = MyPoly();
	int option = -1, num = 0;
	int expon;
	float coef;
	while (option != 0) {
		cout << "------------------------------" << endl;
		cout << "1.讀入多項式" << endl;
		cout << "2.印出多項式內容" << endl;
		cout << "3.多項式相加" << endl;
		cout << "4.多項式乘上一數值" << endl;
		cout << "5.印出多項式中指數最大的係數" << endl;
		cout << "6.新增項式" << endl;
		cout << "7.刪除多項式中的項式" << endl;
		cout << "8.多項式相乘" << endl;
		cout << "0.結束程式" << endl;
		cout << "------------------------------" << endl;

		cin >> option;

		if (option == 1) {
			p = ReadFile("B1.txt");
			p2 = ReadFile("B2.txt");
		}
		else if (option == 2)
			p.ShowPloy();
		else if (option == 3)
			p.Add(p2);
		else if (option == 4) {
			cout << "乘上的數值是多少 " << endl;
			cin >> num;
			p.SingleMult(num);
		}
		else if (option == 5)
			cout << p.Lead_Exp() << endl;
		else if (option == 6) {
			cout << "輸入係數" << endl;
			cin >> coef;
			cout << "輸入指數" << endl;
			cin >> expon;
			p.Attach(coef, expon);
		}
		else if (option == 7) {
			cout << "要刪除的項式" << endl;
			cin >> num;
			p.Remove(num);
		}
		else if (option == 8) {
			p.Mult(p2);
		}
		else if (option == 0)
			cout << "888";
	}
	// MyPoly m = MyPoly();
	// m.Attach(2, 7);
	// m.ShowPloy();
	/*
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
	std::cout << "Hello World!\n"; */
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
