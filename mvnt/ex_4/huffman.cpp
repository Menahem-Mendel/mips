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
	codes.clear();
	root = NULL;

	// build min heap
	priority_queue<HuffmanTree::HuffmanNode *, vector<HuffmanTree::HuffmanNode *>, HuffmanTree::HuffmanNode::compareNode> heap;

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

HuffmanTree::HuffmanTree(string code_s, string char_s)
{
	codes.clear();
	root = NULL;

	int i = 0;
	buildTree(code_s, char_s, root, i);
}

// !!!
void HuffmanTree::buildTree(string code_s, string &char_s, HuffmanTree::HuffmanNode *&n, int &i)
{
	if (code_s.length() == i)
		return;

	if (code_s.at(i) == '1')
	{
		n = new HuffmanTree::HuffmanNode(make_pair(char_s.at(0), 0));

		char_s.erase(char_s.begin());
	}
	else if (code_s.at(i) == '0')
	{
		n = new HuffmanTree::HuffmanNode();

		buildTree(code_s, char_s, n->left, ++i);
		buildTree(code_s, char_s, n->right, ++i);
	}
	else
	{
		cout << "ERROR" << endl;
	}
}

// Encode function returns encrypted string
string HuffmanTree::Encode(string s)
{
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());

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

	return encode(s);
}

string HuffmanTree::Decode(string code_s, string char_s, string encrypted)
{
	if (char_s.size() != count(code_s.begin(), code_s.end(), '1'))
		return "ERROR";

	string out;

	*this = HuffmanTree(code_s, char_s);
	storeChars();

	out = decode(encrypted);

	return out;
}

// printCodes prints all letter codes by tree leaves order
string HuffmanTree::CodeStructure()
{
	return codeStructure(root, "");
}

// printChars prints all letters by tree leaves order
string HuffmanTree::CharStructure()
{
	return charStructure(root, "");
}

// return encoded string
string HuffmanTree::encode(string s)
{
	string out;
	for (int i = 0; i < s.size(); i++)
		out += codes.at(s.at(i));

	return out;
}

// return decoded string
string HuffmanTree::decode(string s)
{
	string out, code;

	for (int i = 0; i < s.size(); i++)
	{
		code += s.at(i);

		if (chars.find(code) != chars.end())
		{
			out += chars.at(code);
			code = "";
		}
	}

	return out;
}

// storeCodes stores all letters with its codes in class variable of type map
void HuffmanTree::storeChars()
{
	storeCodes(root, "");

	for (map<char, string>::iterator iter = codes.begin(); iter != codes.end(); iter++)
		chars[iter->second] = iter->first;
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

// bool operator<(const HuffmanTree::HuffmanNode *l, const HuffmanTree::HuffmanNode *r)
// {
// 	return l->data.second < r->data.second;
// }

// bool operator>(const HuffmanTree::HuffmanNode *l, const HuffmanTree::HuffmanNode *r)
// {
// 	return l->data.second > r->data.second;
// }