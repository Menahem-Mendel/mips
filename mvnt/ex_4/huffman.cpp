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

// HuffmanNode default ctor
HuffmanTree::HuffmanNode::HuffmanNode(char d, unsigned f)
{
	data = d;
	freq = f;
	left = right = NULL;
};

// Encode function returns encrypted string
string HuffmanTree::Encode(string s)
{
	root = NULL;
	codes.clear();

	// s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

	// build frequencies map
	map<char, int> freq;
	for (int i = 0; i < s.size(); i++)
	{
		if (!freq.count(s.at(i)))
			freq[s.at(i)] = 0;

		freq[s.at(i)]++;
	}

	// build min heap
	priority_queue<HuffmanTree::HuffmanNode *, vector<HuffmanTree::HuffmanNode *>, HuffmanTree::HuffmanNode::compare> heap;

	for (map<char, int>::iterator i = freq.begin(); i != freq.end(); i++)
		heap.push(new HuffmanTree::HuffmanNode(i->first, i->second));

	HuffmanTree::HuffmanNode *left, *right;
	while (heap.size() != 1)
	{
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();

		root = new HuffmanTree::HuffmanNode('$', left->freq + right->freq);

		root->left = left;
		root->right = right;

		heap.push(root);
	}

	// build letter codes map
	storeCodes(heap.top(), "");

	cout << codes.size() << endl; // print number of letters
	printChars(heap.top());		  // print unique letters
	cout << endl;
	printCodes(heap.top(), ""); // print unique letter codes
	cout << endl;

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

	// HuffmanTree::HuffmanNode *curr = root;

	// for (int i = 0; i < s.size(); i++)
	// {
	// 	if (s[i] == '0')
	// 		curr = curr->left;
	// 	else
	// 		curr = curr->right;

	// 	// reached leaf node
	// 	if (curr->left == NULL && curr->right == NULL)
	// 	{
	// 		out += curr->data;
	// 		curr = root;
	// 	}
	// }

	return out + '\0';
}

// storeCodes stores all letters with its codes in class variable of type map
void HuffmanTree::storeCodes(HuffmanTree::HuffmanNode *n, string str)
{
	if (n == NULL)
		return;
	if (n->data != '$')
		codes[n->data] = str;

	storeCodes(n->left, str + "0");
	storeCodes(n->right, str + "1");
}

// printCodes prints all letter codes by tree leaves order
void HuffmanTree::printCodes(HuffmanTree::HuffmanNode *n, string str)
{
	if (n == NULL)
		return;
	if (n->data != '$')
		cout << str;

	printCodes(n->left, str + "0");
	printCodes(n->right, str + "1");
}

// printChars prints all letters by tree leaves order
void HuffmanTree::printChars(HuffmanTree::HuffmanNode *n)
{
	if (n == NULL)
		return;
	if (n->data != '$')
		cout << n->data;

	printChars(n->left);
	printChars(n->right);
}
