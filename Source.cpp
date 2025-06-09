/*

Lexical Analyzer:

- Scans the high level language code line by line
- Tokens lexemes as input and produces tokens as output

Tokens:

- identifier
- operator
- constant
- keyword
- literal
- punctuator
- special character

*/

#include<iostream>
#include<fstream>

using namespace std;

string ReadInputFile(string filename) {
	cout << "Reading file data..." << endl;
	ifstream read(filename);
	string data = "";
	while (!read.eof()) {
		string temp = "";
		read >> temp;
		data += temp;
		data += " ";
	}
	cout << "Data reading successful..." << endl;
	return data;
}


int main(int* count, char **arguments) {
	// access file name passed from argument
	string fileName = arguments[1];
	cout << "File to compiler and execute: " << fileName << endl;

	// call function to read file data
	string fileData = ReadInputFile(fileName);
	cout << fileData << endl;


	return 0;
}