#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>


class Trie {
private:
	struct Word { // Struct that holds the word and the word length
		std::string word;
		int length;

		Word(std::string w, int l) : word(w), length(l){}
	};

	struct TrieNode {
		std::vector<Word*> words; // At each node, it holds a list with all the words with the current prefix

		TrieNode* children[26];

		TrieNode() { for (int i = 0; i < 26; i++) children[i] = nullptr; }
	};

	TrieNode* root;
public:
	Trie() : root(new TrieNode){}
	~Trie() { freeNode(root); }
	void freeNode(TrieNode* node);
	void insert(std::string s); // Inserts word into trie, at each node, the word should be inserted into the vector
	void printAll(std::string s, int x); // Prints all words in the vector, for the current prefix or word entered in the console
};

void Trie::freeNode(TrieNode* node) {
	if (!node) return;
	for (int i = 0; i < 26; i++) freeNode(node->children[i]);

	for (auto w : node->words) delete w;

	delete node;
}

void Trie::insert(std::string line) {
	TrieNode* curr = root;

	Word* entry = new Word(line, line.length());

	for (int i = 0; i < line.size(); i++) {
		int idx = line[i] - 'a';
		if (curr->children[idx] == nullptr) {
			curr->children[idx] = new TrieNode;
		}
		curr->words.push_back(entry);
		curr = curr->children[idx];
	}
}

void Trie::printAll(std::string line, int x) {
	std::istringstream iss(line);
	std::string word;

	std::string str;

	if (x <= 0 || x > 20) {
		std::cout << "Please enter a number greater than 0 or less than 20!" << std::endl;
		return;
	}
	if (iss >> word) str = word;
	else return;

	
	TrieNode* curr = root;
	std::cout << str << std::endl;
	for (int i = 0; i < str.size(); ++i) {
		int idx = str[i] - 'a';
		if (curr->children[idx] == nullptr) return;
		curr = curr->children[idx];
	}

	for (auto& e : curr->words) {
		if (x >= e->length) std::cout << e->word << std::endl;
	}
	return;
}