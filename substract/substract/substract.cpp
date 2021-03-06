// substract.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream> 
#include <string> 
using namespace std;

string binary2int(string str);
int char2int(char c);
string formatStringBinary(string str);
string addBinary(string str1, string str2);
string twosComplement(string str);
string substract(string str1, string str2);

int main() {
	string str1;
	string str2;
	char  c1[8];
	char  c2[8];
	string filename = "hw2.txt";
	FILE * fptr;
	fptr = fopen(filename.c_str(), "r");
	if (fptr != NULL) {
		fscanf(fptr, "%s%s", &c1, &c2);
		str1 = string(c1);
		str2 = string(c2);
	}
	else
		cout << "cant find " << filename << endl ;

	string result = formatStringBinary(str1) + " - " + formatStringBinary(str2) + " = " + substract(str1, str2) + " ( ";
		   result += binary2int(formatStringBinary(str1)) + " - " + binary2int(formatStringBinary(str2)) + " = " + binary2int(substract(str1, str2)) + " )";
	cout << result;

	filename = "result.txt";
	fptr = fopen(filename.c_str(), "w");
	if (fptr != NULL) {
		fprintf(fptr, "%s", result.c_str());
	}
	else
		cout << "cant find " << filename << endl ;
	fclose(fptr);

	return 0;
}

string binary2int(string str) {
	int num = 0;
	str = formatStringBinary(str);
	bool nagative = false;
	if (str[0] == '1') {
		str = twosComplement(str), "10";
		nagative = true;
	}
	for (int value = 1, index = str.length() -1 ; index >= 0 ; index--, value *= 2) {
		if (str[index] == '1')
			num += value;
		
	}
	return nagative ? "-"+to_string(num) : to_string(num) ;
}

int char2int(char c) {
	return (int)c-48;
}

string formatStringBinary(string str) {
	if (str.length() <= 8)
		return string(8 - str.length(), '0') + str;
	else
		return str.substr(str.length() - 8, 8);
}

string addBinary(string str1, string str2) {
	string result = string(8, '0');
	int carry = 0;
	for (int index = 7,sum = 0; index >= 0; index--) {
		 sum = carry + char2int(str1[index]) + char2int(str2[index]);
		 if (sum == 3) {
			 carry = 1;
			 result[index] = '1';
		 }
		 else if (sum == 2) {
			 carry = 1;
			 result[index] = '0' ;
		 }
		 else if (sum == 1) {
			 carry = 0;
			 result[index] = '1';
		 }
		 else if (sum == 0) {
			 carry = 0;
			 result[index] = '0';
		 }
	}
	return result;
}

string twosComplement(string str) {
	str = formatStringBinary(str);
	for (int index = 0; index < 8; index++) {
		if (str[index] == '0')
			str[index] = '1';
		else
			str[index] = '0';
	}
	return addBinary(str, formatStringBinary("1"));
}

string substract(string str1, string str2) {
	return addBinary(formatStringBinary(str1), twosComplement(str2));
}