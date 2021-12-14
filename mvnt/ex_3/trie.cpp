#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

Trie::Trie()
{
	root = new TrieNode();
}

void Trie::insert(string str)
{
	TrieNode *curr = root;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (curr->children[c - 'a'] == 0)
			curr->children[c - 'a'] = new TrieNode();
		curr = curr->children[c - 'a'];
	}

	curr->isEndWord = true;
}

void Trie::del(string str)
{
}

bool Trie::search(string str)
{
	TrieNode *curr = root;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (curr->children[c - 'a'] == 0)
			return 0;
		curr = curr->children[c - 'a'];
	}

	return curr && curr->isEndWord;
}

void Trie::printAllWordsFromPrefix(TrieNode *)
{
}

// Trie::TrieNode::TrieNode()
// {
// 	c = '\0';
// }