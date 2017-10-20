#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void pad(std::vector<int> &terms) {
	if (terms.size() < 16) {
		terms.insert(terms.begin(), 0);
	}
}

std::vector<std::vector<int> > arrayToBCD(std::vector<int> terms) {
	std::vector<int> binary;
	std::vector<std::vector<int> > allterms;
	int number;
	int remainder;
	for (int i = 0; i < terms.size(); i++) {
		number = terms.at(i);
		while (number != 0) {
			binary.push_back(number % 2);
			number = number / 2;
		}
		allterms.push_back(binary);
	}
	return allterms;
}

std::vector<std::vector<int> > inputToArray(string input) {
	std::vector<string> terms;
	std::vector<int> minterms;
	int firstComma = input.find(',');
	terms.push_back(input.substr(0, firstComma));
	int comma = firstComma;
	int next = 0;
	for (; comma < input.length() - 2;) {
		next = input.find(',', comma + 1);
		terms.push_back(input.substr(comma + 1, next - comma - 1));
		comma = next;
	}
	int lastComma = input.find_last_of(',');
	terms.push_back(input.substr(lastComma + 1));
	for (int i = 0; i < terms.size(); i++) {
		if (std::stoi(terms.at(i)))
			minterms.push_back(std::stoi(terms.at(i)));
	}
	std::vector<std::vector<int> > allterms = arrayToBCD(minterms);
	return allterms;
}

std::vector<int> countBits(std::vector<std::vector<int> > terms) {
	std::vector<int> binary;
	std::vector<int> number(terms.size(), 0);
	for (int i = 0; i < terms.size(); i++) {
		binary = terms.at(i);
		for (int j = 0; j < binary.size(); j++) {
//			cout << terms.at(i).at(j);
			if (binary.at(j) == 1) {
				number.at(i) += 1;
			}
		}
//		cout << endl;
	}
	return number;
}

bool malformedInput(string input) {
	// Check if input contains other than digit/space/comma
	char currentCharacter;
	for (int i = 0; i < input.length(); i++) {
		currentCharacter = input[i];
		if (currentCharacter == ' ' || currentCharacter == ','
				|| currentCharacter == '\n'
				|| (currentCharacter <= 57 && currentCharacter >= 48))
			continue;
		else
			return true;
	}
	return false;
}


int main(int argc, const char *argv[]) {
	string mintermsInput;
	string dontCaresInput;
	int variableNumber;
	string variableCount;
	std::vector<std::vector<int> > minterms;
	std::vector<int> mintermsBits;
	std::vector<std::vector<int> > dontcares;
	std::vector<int> dontcaresBits;

	if (argc > 1) {
		// The program is being executed with input files
		// File should contain two lines only, first minterms, second don't cares
		std::string line;
		ifstream inputFile(argv[1]);
		for (int i = 0; i < 2; i++) {
			if (i == 0) {
				getline(inputFile, variableCount);
				variableNumber = stoi(variableCount);
			}
			if (i == 1)
				getline(inputFile, mintermsInput);
			if (i == 1)
				getline(inputFile, dontCaresInput);
		}
		inputFile.close();
	} else {
		int counter = 0;
		do {
			if (counter > 0)
				cout << "Wrong Input!" << endl;
			cout << "Please enter number of variables [1-16]: ";
			getline(std::cin, variableCount);
			variableNumber = stoi(variableCount);
			counter += 1;
		} while (malformedInput(mintermsInput) || mintermsInput.empty());
		counter = 0;
		do {
			if (counter > 0)
				cout << "Wrong Input!" << endl;
			cout << "Please enter minterms as numbers comma seperated: ";
			getline(std::cin, mintermsInput);
			counter += 1;
		} while (malformedInput(mintermsInput));
		counter = 0;
		do {
			if (counter > 0)
				cout << "Wrong Input!" << endl;
		cout << "Please enter don't cares as numbers comma seperated: ";
			getline(std::cin, dontCaresInput);
			counter += 1;
		} while (malformedInput(dontCaresInput));
	}

	if (malformedInput(mintermsInput) || malformedInput(dontCaresInput)) {
		cout << "Detected malformed input, shutting down" << endl
				<< "Goodbye...";
		return 0;
	}

	minterms = inputToArray(mintermsInput);
	if (!dontCaresInput.empty())
	dontcares = inputToArray(dontCaresInput);
	mintermsBits = countBits(minterms);
	if (!dontCaresInput.empty())
	dontcaresBits = countBits(dontcares);

	return 0;
}
