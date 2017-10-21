#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void pad(std::vector<int> &terms) {
	string number = "";
	for (int i : terms) {
		number = to_string(terms.at(i));
		if (number.length() < 16) {
			for (int i = number.length(); i < 16; i++)
				number = "0" + number;
		}
		terms.at(i) = stoi(number);
	}
}

void arrayToBCD(std::vector<int> &terms) {
	int number = 0;
	int remainder;
	int multiplier;
	int binary;
	for (int i = 0; i < terms.size(); i++) {
		number = terms.at(i);
		binary = 0;
		remainder = 0;
		multiplier = 1;
		do {
			remainder = number % 2;
			binary = binary + (multiplier * remainder);
			number = number / 2;
			multiplier = multiplier * 10;
		} while (number > 0);
		terms.at(i) = binary;
	}
}

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
		if (std::stoi(terms.at(i)))
			minterms.push_back(std::stoi(terms.at(i)));
	}
	arrayToBCD(minterms);
	return minterms;
}

std::vector<int> countBits(std::vector<int> terms) {
	string number = "";
	int counter;
	std::vector<int> count;
	for (int i = 0; i < terms.size(); i++) {
		counter = 0;
		number = to_string(terms.at(i));
		for (int j = 0; j < number.length(); j++) {
			if (number[j] == '1')
				counter += 1;
		}
		count.push_back(counter);
	}
	return count;
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
	std::vector<int> minterms;
	std::vector<int> mintermsBits;
	std::vector<int> dontcares;
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
		} while (malformedInput(variableCount) || variableCount.empty());
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

	for (int i = 0; i < minterms.size(); i++) {
		cout << minterms.at(i) << " " << mintermsBits.at(i) << endl;
	}

	return 0;
}
