#pragma once

#include <iostream>
#include <string>

using namespace std;

const int ALPHABET = 26;

class Trie
{
protected:
	class TrieNode
	{
	public:
		char c;
		TrieNode *children[ALPHABET] = {0};
		TrieNode *father;
		bool isEndWord = false;
		// int countChildren = 0;
	public:
		TrieNode(){};
	};

	TrieNode *root;

public:
	Trie() {}

	// all functions
	void insert(string str);
	void del(string str);
	bool search(string str);
	void printAllWordsFromPrefix(TrieNode *);

private:
	bool searchWord(string str, TrieNode *node);
};