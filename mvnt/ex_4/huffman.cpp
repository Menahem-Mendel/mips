#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cctype>
#include <algorithm>
#include <map>

#include "huffman.h"

using namespace std;

// HuffmanTree default ctor
HuffmanTree::HuffmanTree()
{
	root = NULL;
}

HuffmanTree::HuffmanTree(map<char, unsigned> freq)
{
	// build min heap
	priority_queue<HuffmanTree::HuffmanNode *, vector<HuffmanTree::HuffmanNode *>, less<HuffmanTree::HuffmanNode *>> heap;

	for (map<char, unsigned>::iterator i = freq.begin(); i != freq.end(); i++)
		heap.push(new HuffmanTree::HuffmanNode(make_pair(i->first, i->second)));

	HuffmanTree::HuffmanNode *left, *right, *top;
	while (heap.size() != 1)
	{
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();

		top = new HuffmanTree::HuffmanNode(make_pair('$', left->data.second + right->data.second));

		top->left = left;
		top->right = right;

		heap.push(top);
	}

	heap.pop();
	root = heap.top();
}

HuffmanTree::HuffmanTree(string codes, string chars)
{
	buildTree(codes, chars, root, 0);
}

// !!!
void HuffmanTree::buildTree(string codes, string chars, HuffmanTree::HuffmanNode *n, int i)
{
	if (codes.length() == i)
		return;

	if (codes.at(i) == '1')
	{
		n = new HuffmanTree::HuffmanNode(make_pair(chars.at(0), 1));
		chars.erase(chars.begin());
	}
	else if (codes.at(i) == '0')
	{
		n = new HuffmanTree::HuffmanNode();
		buildTree(codes, chars, n->left, i++);
		buildTree(codes, chars, n->right, i++);
	}
}

string HuffmanTree::Decode(string codes, string chars, string encrypted)
{
	string out;

	*this = HuffmanTree(codes, chars);
	out = decode(encrypted);

	return out;
}

string HuffmanTree::decode(string s)
{
	string out = "";
	HuffmanTree::HuffmanNode *curr = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node
		if (curr->left == NULL && curr->right == NULL)
		{
			out += curr->data.first;
			curr = root;
		}
	}

	return out;
}

// Encode function returns encrypted string
string HuffmanTree::Encode(string s)
{
	root = NULL;
	codes.clear();

	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

	// build frequencies map
	map<char, unsigned> freq;
	for (int i = 0; i < s.size(); i++)
	{
		if (!freq.count(s.at(i)))
			freq[s.at(i)] = 0;

		freq[s.at(i)]++;
	}

	*this = HuffmanTree(freq);

	storeCodes(root, ""); // build letter codes map

	// return encoded string
	string out;
	for (int i = 0; i < s.size(); i++)
		out += codes.at(s.at(i));

	return out;
}

// storeCodes stores all letters with its codes in class variable of type map
void HuffmanTree::storeCodes(HuffmanTree::HuffmanNode *n, string str)
{
	if (n->left == NULL && n->right == NULL)
		codes[n->data.first] = str;

	if (n->right != NULL)
		storeCodes(n->right, str + "1");
	if (n->left != NULL)
		storeCodes(n->left, str + "0");
}

// printCodes prints all letter codes by tree leaves order
string HuffmanTree::CodeStructure()
{
	return codeStructure(root, "");
}

string HuffmanTree::codeStructure(HuffmanTree::HuffmanNode *n, string str)
{
	if (n->left == NULL && n->right == NULL)
		return str + "1";

	if (n->left != NULL)
		str = codeStructure(n->left, str + "0");

	if (n->right != NULL)
		str = codeStructure(n->right, str);

	return str;
}

// printChars prints all letters by tree leaves order
string HuffmanTree::CharStructure()
{
	return charStructure(root, "");
}

string HuffmanTree::charStructure(HuffmanTree::HuffmanNode *n, string str)
{
	if (n->left == NULL && n->right == NULL)
		return str + n->data.first;

	if (n->left != NULL)
		str = charStructure(n->left, str);
	if (n->right != NULL)
		str = charStructure(n->right, str);

	return str;
}

bool operator<(const HuffmanTree::HuffmanNode &l, const HuffmanTree::HuffmanNode &r)
{
	return l.data.second < r.data.second;
}

bool operator>(const HuffmanTree::HuffmanNode &l, const HuffmanTree::HuffmanNode &r)
{
	return l.data.second > r.data.second;
}