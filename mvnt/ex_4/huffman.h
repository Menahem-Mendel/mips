#pragma once

#include <string>
#include <map>
#include <queue>
#include <utility>

using namespace std;

struct HuffmanTree
{

	HuffmanTree();
	HuffmanTree(map<char, unsigned>);
	HuffmanTree(string, string); // reverse ctor
	HuffmanTree(HuffmanTree &ht);

	string Encode(string);
	string Decode(string, string, string);
	string Decode(string);

	string CodeStructure();
	string CharStructure();

	struct HuffmanNode
	{
		pair<char, unsigned> data;
		HuffmanNode *left, *right;

		HuffmanNode() : data(make_pair('$', 0)), left(NULL), right(NULL){};
		HuffmanNode(pair<char, unsigned> d) : data(d), left(NULL), right(NULL){};
		HuffmanNode(pair<char, unsigned> d, HuffmanNode *l, HuffmanNode *r) : data(d), left(l), right(r){};
		HuffmanNode(const HuffmanNode &hn) : data(hn.data), left(hn.left), right(hn.right){};

		// friend bool operator<(const HuffmanNode *l, const HuffmanNode *r);
		// friend bool operator>(const HuffmanNode *l, const HuffmanNode *r);

		struct compareNode
		{
			bool operator()(const HuffmanNode *l, const HuffmanNode *r)
			{
				return l->data.second > r->data.second;
			}
		};
	};

private:
	HuffmanNode *root;
	map<char, string> codes;
	map<string, char> chars;

	void buildTree(string, string &, HuffmanNode *&, int &);
	void storeCodes(HuffmanNode *, string);
	void storeChars();
	string decode(string);
	string encode(string);
	string codeStructure(HuffmanNode *, string);
	string charStructure(HuffmanNode *, string);
};