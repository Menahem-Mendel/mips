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
HuffmanTree::HuffmanTree() {}

string HuffmanTree::Encode(string chars, string codes)
{
	// vector<Pair> elements;
	// for (string::iterator iter = letters.begin(); iter != letters.end(); iter++)
	//     elements.push_back(Pair(*iter)); // elements.push_back(make_pair(*iter->first, *iter->second));

	// root = new BinaryTree<Pair>(treeStructure, elements, Pair(0));
	// root->setPaths();
	return "";
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

	// build min heap
	priority_queue<HuffmanTree::HuffmanNode *, vector<HuffmanTree::HuffmanNode *>, HuffmanTree::HuffmanNode::compareNode> heap;

	for (map<char, unsigned>::iterator i = freq.begin(); i != freq.end(); i++)
		heap.push(new HuffmanTree::HuffmanNode(make_pair(i->first, i->second)));

	HuffmanTree::HuffmanNode *left, *right;
	while (heap.size() != 1)
	{
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();

		root = new HuffmanTree::HuffmanNode(make_pair('$', left->data.second + right->data.second));

		root->left = left;
		root->right = right;

		heap.push(root);
	}

	heap.pop();
	root = heap.top();

	storeCodes(root, ""); // build letter codes map

	// return encoded string
	string out;
	for (int i = 0; i < s.size(); i++)
		out += codes.at(s.at(i));

	return out;
}

// Decode returns decoded string
string HuffmanTree::Decode(string s)
{
	string out;

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
