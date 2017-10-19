/*
 * quine.mccluskey.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: ahmed
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::vector<string>> inputToArray(string input) {
	std::vector<std::vector<char>> terms;
	std::vector<char> singleTerm;
	for (int j = 0; j < input.length; j++) {

		for (int i = 0; i < input.length(); i++) {
			singleTerm.push_back(input[i]);
		}
		terms.push_back[singleTerm];
	}
	return terms;
}

int bitCount(string binary) {
	for (int i : binary.length()) {

	}
}

bool wrongInput(string input) {
	bool answer;

	return answer;
}

char[] binaryCodedDecimal(string input) {
	char[] binaryCode;



	return binaryCode;
}

bool malformedInput(string input) {
	// Check if input contains other than digit/space/comma
	char currentCharacter;
	for (int i = 0; i < input.length(); i++) {
		currentCharacter = input[i];
		if (i == 32 || i == 44 || (i <= 57 && i >= 48))
			continue;
		else
			return true;
	}
	return false;
}

int main(int argc, const char *argv[]) {
	string mintermsInput;
	string dontCaresInput;
	std::vector<char> v;

	if (argc > 1) {
		// The program is being executed with input files
		// File should contain two lines only, first minterms, second don't cares
		std::string line;
		ifstream inputFile(argv[1]);
		for (int i = 0; i < 2; i++) {
			if (i == 0)
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
			cout << "Please enter minterms comma seperated: ";
			getline(std::cin, mintermsInput);
			counter += 1;
		} while (wrongInput(mintermsInput));
		counter = 0;
		do {
			if (counter > 0)
				cout << "Wrong Input!" << endl;
			cout << "Please enter don't cares comma seperated: ";
			getline(std::cin, dontCaresInput);
			counter += 1;
		} while (wrongInput(dontCaresInput));
	}

	if (malformedInput(mintermsInput) || malformedInput(dontCaresInput)) {
		cout << "Detected malformed input, shutting down" << endl
				<< "Goodbye...";
		return 0;
	}

	binaryCodedDecimal();
	countBits();
	compareBinary();

	return 0;
}



