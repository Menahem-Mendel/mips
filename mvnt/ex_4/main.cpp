// Menahem Mendel Gelfand - 342795218
// Roy Barak -

#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "huffman.h"

using namespace std;

int main()
{
	char choice;
	HuffmanTree t;

	cout << "enter E to encode a text" << endl;
	cout << "enter D to decode a text" << endl;
	cout << "enter X to exit" << endl;

	string encrypted;
	do
	{
		cin >> choice;
		string word;

		switch (choice)
		{
		case 'E':
			cout << "enter the original text" << endl;
			cin >> word;

			cout << "The encoded string is:" << endl;
			encrypted = t.Encode(word);
			cout << encrypted << endl;
			break;
		case 'D':
			// int n;
			// string lt, st, txt;
			// cout << "enter n ";
			// cin >> n;
			// cout << "enter the letters ";
			// cin >> lt;
			// cout << "enter the encoded structure ";
			// cin >> st;
			// cout << "enter the encoded text ";
			// cin >> txt;
			cout << "The decoded string is:" << endl;
			cout << t.Decode(encrypted) << endl;
			break;
		}

	} while (choice != 'X');

	return 0;
}
