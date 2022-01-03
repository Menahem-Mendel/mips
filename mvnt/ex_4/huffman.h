#pragma once

#include <string>
#include <map>

using namespace std;

class HuffmanTree
{
	class HuffmanNode
	{
	public:
		char data;
		unsigned freq;
		HuffmanNode *left, *right;

		HuffmanNode(char d, unsigned f);

		struct compare
		{
			bool operator()(HuffmanNode *l, HuffmanNode *r)
			{
				return (l->freq > r->freq);
			}
		};
	};

	HuffmanNode *root;
	map<char, string> codes;

	void storeCodes(HuffmanNode *, string);
	void printCodes(HuffmanNode *, string);
	void printChars(HuffmanNode *);

public:
	HuffmanTree();
	HuffmanTree(HuffmanTree &ht);

	string Encode(string);
	string Decode(string);
};