#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

Trie::Trie()
{
	root = new TrieNode('\0');
}

void Trie::insert(string str)
{
	if (search(str))
		return;

	TrieNode *curr = root;
	TrieNode *temp = root;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (curr->children[c - 'a'] == 0)
		{
			curr->children[c - 'a'] = new TrieNode(c);
			curr->countChildren++;
		}
		temp = curr;
		curr = curr->children[c - 'a'];
		curr->father = temp;
	}

	curr->isEndWord = true;
}
void Trie::del(string str)
{
	TrieNode *curr = root;
	if (!search(str))
		return;
	char ch = '\0';
	//2 possbile cases : the word end in a leaf or word end in a node
	/*case one: the word end in a node*/
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		curr = curr->children[c - 'a'];
		ch = c;
	}
	if (curr->isEndWord && curr->countChildren != 0)
		curr->isEndWord = false;
	/*case two: the word end in a leaf*/
	else if (curr->isEndWord && curr->countChildren == NULL)
	{
		while (curr->countChildren == 0)
		{
			char c = curr->c;
			if (curr == this->root)
			{
				delete[] curr->children[c - 'a'];
				return;
			}
			curr = curr->father;
			if (curr->isEndWord)
			{
				break;
			}
			curr->countChildren--;
			delete[] curr->children[c - 'a'];
			curr->children[c - 'a'] = NULL;
		}
	}
}
bool Trie::search(string str)
{
	TrieNode *curr = root;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (curr->children[c - 'a'] == NULL)
			return false;
		curr = curr->children[c - 'a'];
	}

	return curr && curr->isEndWord;
}
void Trie::printAllWordsFromPrefix(TrieNode *r, string str)
{
	if (r->countChildren == 0)
	{
		cout << str << endl;
		return;
	}

	for (int i = 0; i < ALPHABET; i++)
	{
		if (!r->children[i])
			continue;
		if (r->isEndWord)
			cout << str << endl;
		str += r->children[i]->c;
		printAllWordsFromPrefix(r->children[i], str);
		str.pop_back();
	}
}
int Trie::printAutoSuggestions(string str)
{
	TrieNode *curr = root;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (curr->children[c - 'a'] == 0)
			return false;
		curr = curr->children[c - 'a'];
	}
	this->printAllWordsFromPrefix(curr, str);
	return true;
}
bool Trie::searchWord(string str, TrieNode *node)
{
	TrieNode *curr = node;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (curr->children[c - 'a'] == 0)
			return false;
		curr = curr->children[c - 'a'];
	}
	return true;
}
