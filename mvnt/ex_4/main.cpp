// Menahem Mendel Gelfand - 342795218
// Roy Barak -

#include <iostream>
#include <queue>
#include <string>

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
		string word;

		cin >> choice;

		switch (choice)
		{
		case 'E':
			cout << "enter the original text" << endl;
			cin >> word;

			cout << "The encoded string is" << endl;
			encrypted = t.Encode(word); // encrypt word

			cout << t.CharStructure() << endl; // print all characters
			cout << t.CodeStructure() << endl; // print all character codes
			cout << encrypted << endl;		   // print encrypted string

			break;
		case 'D':
			int n;
			string letters, treeStructure, encodedText;
			cout << "enter n " << endl;
			cin >> n;

			cout << "enter the letters " << endl;
			cin >> letters;
			cout << "enter the encoded structure " << endl;
			cin >> treeStructure;
			cout << "enter the encoded text " << endl;
			cin >> encodedText;
			cout << "The decoded string is" << endl;

			// t.Encode(treeStructure, letters);
			cout << t.Decode(encrypted) << endl;
			break;
		}
	} while (choice != 'X');

	cout << "bye" << endl;

	return 0;
}
