#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <conio.h>

#include "Trie.h"

void clearScreen() {
	system("cls");
}

int main() {

	Trie wordSearch;
	
	// file reading stuff
	std::fstream f;
	f.open("words.txt");
	assert(f.is_open());
	std::string line;
	int i = 0;

	std::cout << "Loading..." << std::endl;
	while (std::getline(f, line)) {
		wordSearch.insert(line);
		++i;
	}
	f.close();
	assert(i == 370105);
	std::cout << "Ready to use!" << std::endl << std::endl;
	
	std::cout << "Spelling Bee Helper! (press esc to quit, press # to set max Length)" << std::endl;
	std::cout << std::string(67, '*') << std::endl;

	char c;
	std::string input;
	int maxLen = 5;

	while (true) {
		if (_kbhit()) {
			c = _getch();

			if (c == 27) {
				std::cout << "Goodbye! :)" << std::endl;
				break;
			}

			if (c == 8) {
				if (!input.empty()) input.pop_back();
			}
			else if (c == 35) {
				clearScreen();
				std::cout << "Enter maximum length: ";
				std::cin >> maxLen;
				std::cin.ignore();
			}
			else if (isalpha(c)) {
				input += c;
			}

			clearScreen();

			if (!input.empty()) {
				wordSearch.printAll(input, maxLen);
			}
		}
	}


}
