// Student name: Berk Tinaz
// Student ID  : 40115829

/*
	Submission deadline: Sunday, 21 April 2019, 11:59 pm.

	*** Weighting of this exercise is 2 times the weighting of other tutorials. ***

	What you need to do in this exercise:

	1. A Huffman code table is given to you in the file HuffmanCodeTable.txt
	   Format of the data file:
	   line 1 : contains 1 number, which is equal to the number of alphabets
	   lines 2 to n+1 : contain the ASCII code (2 hex digits) of the symbol and the Huffman code

	   You need to write a function to read in the Huffman codes and 
	   create the Huffman tree from the given code table.

	2. An encoded message is given to you in the file CodedMsg.txt
	   A function to read in the encoded message to a bit-vector is given to you.
	   Refer to the pdf file for the organization of the bit-vector.

	   You need to design a function to decode the message and save the decoded message
	   to the char array text[].
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct treeNode
{
	char info;
	treeNode *left, *right;
};

void createHuffmanTree(treeNode *root, const string& filename)
{
	//Precondition: root is not nullptr

	ifstream infile(filename); //open file
	if (!infile.is_open()) 
	{
		cout << "Error: cannot open " << filename << endl;
		system("pause");
		exit(0);
	}

	string ascii;
	string code;
	treeNode *p = root;

	int len;
	infile >> len; //get number of coded ascii chars

	for(int i = 0; i < len; i++) //for next len number of lines
	{
		if (infile >> ascii >> code) //get space seperated ascii and code strings
		{
			for (int i = 0; i < code.length(); i++)
			{
				if (code[i] == '0') //move to left when bit is 0
				{
					if (p->left == nullptr) //if left node doesn't exist, create 
					{
						treeNode *temp = new treeNode;
						temp->info = '\0';
						temp->left = nullptr;
						temp->right = nullptr;
						p->left = temp;
					}
					p = p->left; //advance to left node
				}
				else //else move to right
				{
					if (p->right == nullptr) //if right node doesn't exist, create 
					{
						treeNode *temp = new treeNode;
						temp->info = '\0';
						temp->left = nullptr;
						temp->right = nullptr;
						p->right = temp;
					}
					p = p->right;  //advance to right node
				}
			}
			p->info = (char)strtol(ascii.c_str(), 0, 16); //convert ascii string to char value
			p = root; //return to root
		}
 	}
	infile.close(); //close file
}


void decode(treeNode *root, const unsigned char *code,
	char *msg, int len)
{
	// Precondition: User is responsible for creating
	// sufficient storage space for the decoded message.
	// code[] is a bit-vector.

	unsigned char mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

	treeNode *p = root;
	int k = 0;
	int temp = 0;

	int num_of_bytes = ceil((double)len / 8); //num of bytes is the num of bits divided by 8 and rounded to smallest bigger integer
	int current = 0; //num of bits processed

	for (int i = 0; i < num_of_bytes; i++)
	{
		temp = (int) code[i]; //convert code to integer
		for (int j = 7; j >= 0 && current < len; j--)
		{
			current += 1;
			if (temp < mask[j]) //if temp is bigger than mask[j] then jth bit location is 1, 0 otherwise.
				p = p->left;
			else
			{
				p = p->right;
				temp -= mask[j]; //if bit is 1, remove mask[j] to get integer value of remaining bits on the right.
			}
			if (p->left == nullptr && p->right == nullptr) //if reached to leaf, add stored info on leaf to the decoded message array. Move back to root.
			{
				msg[k++] = p->info;
				p = root;
			}
		}
	}
	msg[k] = '\0'; //end the message
}

void readCodedMsg(const string& filename, unsigned char *bitVec, int& len)
{
	// Read in the encoded message from the data file to a bit-vector.
	// The encoded message is stored in 1 line in the data file.

	// The bit-vector (bitVec) is an array of unsigned char.
	// len = number of bits in the bit-vector

	unsigned char mask[8] = {1, 2, 4, 8, 16, 32, 64, 128};

	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Error: cannot open " << filename << endl;
		system("pause");
		exit(0);
	}

	len = 0;
	char c;

	// end-of-line delimiter in Windows is '\n'
	// end-of-line delimiter in Mac is "\r\n"
	while ((c = infile.get()) != '\n' && c != '\r')  
	{					
		int byteIndex = len / 8;
		int bitIndex = 7 - len % 8;
		if (len % 8 == 0)
			bitVec[byteIndex] = 0;
		
		if (c == '1')		
			bitVec[byteIndex] = bitVec[byteIndex] | mask[bitIndex];  // bit-wise OR

		len++;
	}
	infile.close();
}

int main()
{		
	string codeTableFile = "HuffmanCodeTable.txt";
	string codedMsgFile = "CodedMsg.txt";

	unsigned char buffer[256];  // 256-byte buffer, up to 2K bits for the coded message
	int len = 0;                // number of bits in the encoded message

	readCodedMsg(codedMsgFile, buffer, len);	

	char text[256];
	text[0] = '\0';

	// Your codes to decode the message and 
	// save the decoded message to the char array text[].

	treeNode *huffman = nullptr; //initialize head of the tree
	huffman = new treeNode;
	huffman->info = '\0';
	huffman->left = nullptr;
	huffman->right = nullptr;
	createHuffmanTree(huffman, codeTableFile);

	decode(huffman, buffer, text, len);

	cout << "Decoded message:\n";
	cout << text << endl << endl;

	system("pause");
	return 0;
}