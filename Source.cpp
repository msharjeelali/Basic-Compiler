#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>

using namespace std;

const set<string> keywords = { "int","char","bool","if","while","for","read","print","function","return","mod" };
const set<char> punctuators = { ',',';','(',')','{','}' };
const set<char> airthematicOperators = { '+','-','*','/' };
const set<char> relationalOperators = {'>', '<', '!' };

// read the source code from the file
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
	cout << "Data reading successful..." << endl << endl;
	return data;
}

// generate tokens from the given source code
vector<pair<string, string>> GenerateTokens(string filedata) {
	vector<pair<string, string>> tokens;

	stringstream ss(filedata);
	string temp = "";
	while (ss >> temp) {
		int i = 0;
		while (i < temp.length()) {
			// if puctuator
			if (punctuators.find(temp[i]) != punctuators.end()) {
				tokens.push_back({ string{temp[i]},"NULL" });
				i++;
			}
			// if = or == operator
			else if (temp[i] == '=') {
				if (i + 1 < temp.length() && temp[i + 1] == '=') {
					tokens.push_back({ "==", "RelOp" });
					i+=2;
				}
				else {
					tokens.push_back({ "=", "AssOp" });
					i++;
				}
			}
			// if airthematic or airthematic + assignment operator
			else if (airthematicOperators.find(temp[i]) != airthematicOperators.end()) {
				if (i + 1 < temp.length() && temp[i + 1] == '=') {
					tokens.push_back({ string{temp[i] } + "=" , "AirOp"
				});
					i += 2;
				}
				else {
					tokens.push_back({ string{temp[i]},"AirOp" });
					i++;
				}
			}
			// if realtional operator
			else if (relationalOperators.find(temp[i]) != relationalOperators.end()) {
				if (i + 1 < temp.length() && temp[i + 1] == '=') {
					tokens.push_back({ string{temp[i]} + "=", "RelOp" });
					i += 2;
				}
				else {
					tokens.push_back({ string{temp[i]}, "RelOp"
				});
					i++;
				}
			}
			// if logical or relational operator
			else if (temp[i] == '!') {
				if (i + 1 < temp.length() && temp[i + 1] == '=') {
					tokens.push_back({ "!=" , "RelOp"});
					i += 2;
				}
				else {
					tokens.push_back({ "!" , "LogOp"});
					i++;
				}
			}
			// if and operator
			else if (temp[i] == '&') {
				if (i + 1 < temp.length() && temp[i + 1] == '&') {
					tokens.push_back({ "&&", "LogOp"});
					i += 2;
				}
				else
					throw runtime_error("Incorrect Operator");
			}
			// if or operator
			else if (temp[i] == '|') {
				if (i + 1 < temp.length() && temp[i + 1] == '|') {
					tokens.push_back({ "||", "LogOp"});
					i += 2;
				}
				else
					throw runtime_error("Incorrect Operator");
			}
		}
	}
	return tokens;
}

// write token lexem pairs in file
void WriteLexicalAnalyzerOutput(vector<pair<string, string>> tokens) {
	cout << "Writing data in file..." << endl;
	ofstream write("lexicalanalyzeroutput.txt");
	for (auto& ite : tokens) {
		write << "( " << ite.first << ", " << ite.second << " )" << endl;
	}
	cout << "Data writing successful..." << endl << endl;
}

int main(int* count, char **arguments) {
	// access file name passed from argument
	string fileName = arguments[1];
	cout << "File to compiler and execute: " << fileName << endl << endl;

	// call function to read file data
	string fileData = ReadInputFile(fileName);

	// call function to generate tokens
	vector<pair<string, string>> tokens;
	try {
		tokens = GenerateTokens(fileData);
	}
	catch (exception& e) {
		cout << "Caugth an exception : " << e.what() << endl;
		return 0;
	}

	cout << "Lexical Analyzer processing successful" << endl;
	// write lexical analyzer output in file
	WriteLexicalAnalyzerOutput(tokens);


	return 0;
}