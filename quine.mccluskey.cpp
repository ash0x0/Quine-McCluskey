#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::vector<int> inputToArray(string input) {
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
		cout << terms.at(i) << endl;
		if (std::stoi(terms.at(i)))
			minterms.push_back(std::stoi(terms.at(i)));
	}
	return minterms;
}

int bitCount(string binary) {
	for (int i = 0; i < binary.length(); i++) {

	}
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
	std::vector<int> minterms;
	std::vector<int> dontcares;

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
		} while (malformedInput(mintermsInput));
		counter = 0;
		do {
			if (counter > 0)
				cout << "Wrong Input!" << endl;
			cout << "Please enter don't cares comma seperated: ";
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
	dontcares = inputToArray(dontCaresInput);

	return 0;
}



