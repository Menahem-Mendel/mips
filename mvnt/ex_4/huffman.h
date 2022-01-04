#pragma once

#include <string>
#include <map>
#include <queue>
#include <utility>

using namespace std;

struct HuffmanTree
{

	HuffmanTree();
	HuffmanTree(HuffmanTree &ht);

	string Encode(string);
	string Encode(string, string);
	string Decode(string);

	string CodeStructure();
	string CharStructure();

	struct HuffmanNode
	{
		pair<char, unsigned> data;
		HuffmanNode *left, *right;

		HuffmanNode(pair<char, unsigned> d) : data(d), left(NULL), right(NULL){};
		HuffmanNode(pair<char, unsigned> d, HuffmanNode *l, HuffmanNode *r) : data(d), left(l), right(r){};
		HuffmanNode(const HuffmanNode &hn) : data(hn.data), left(hn.left), right(hn.right){};

		friend bool operator<(const HuffmanNode &l, const HuffmanNode &r);
		friend bool operator>(const HuffmanNode &l, const HuffmanNode &r);
	};

private:
	HuffmanNode *root;
	map<char, string> codes;

	void storeCodes(HuffmanNode *, string);
	string codeStructure(HuffmanNode *, string);
	string charStructure(HuffmanNode *, string);
};