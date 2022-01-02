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
		int countChildren = 0;

	public:
		TrieNode(char ch, int children = 0) : c(ch), countChildren(children){};
	};

	TrieNode *root;

public:
	Trie();
	// all functions
	void insert(string str);
	void del(string str);
	bool search(string str);
	void printAllWordsFromPrefix(TrieNode *r, string str);
	int printAutoSuggestions(string str);
	bool isLeafNode(TrieNode *root)
	{
		bool flag = true;
		for (size_t i = 0; i < ALPHABET; i++)
		{
			if (root->children[i] != NULL)
			{
				//ther is a son - not a leaf
				flag = false;
				break;
			}
		}
		return flag;
	}

private:
	bool searchWord(string str, TrieNode *node);
};