////
// Author:		Nick Francisco
// School:		Everett Community College
// Class:		CS 233 Advance Data Structures and Intro to Algorithms 
// Quarter:		Spring 2021
// Assignment:  Program 2 Huffman Code
// Description: This program will build a Huffman binary tree for the given string or
//	file. It can compress and decompress the string or file by using the Huffman encoding
//  to set or read bits of an encoded char. 
////

#include "stdafx.h"
#include "HuffmanTree.h"
#include <string>
#include <vector>
#include <fstream> 
#include <iostream>
#include <queue>    
#include <algorithm>
#include <iomanip> 
#include <bitset>
#include <unordered_map>
#include <sstream>

//Gets Bits
inline bool HuffmanTree::getBit(unsigned char byte, int position) const 
{ 

	return (byte  & BITMASK[position]);
}

//Sets bits
inline unsigned char HuffmanTree::setBit(unsigned char byte, int position) const 
{
	return  byte | BITMASK[position];
}

//Prints binary bits
void HuffmanTree::printBits(char binary, std::ostream & out) const
{
	for (size_t i = 0; i < sizeof(char) * 8; i++) {
		if (getBit(binary, i)) {
			out << 1;
		}
		else {
			out << 0;
		}
	}
}

//Prints binary bytes
void HuffmanTree::printBinary(vector<char> bytes, std::ostream & out) const 
{		
	for (char byte : bytes) 
	{
		printBits(byte, out);
		out << "-";		
	}
}

//Gets code for char
string HuffmanTree::getCode(char letter) const 
{	
	string code = "";

	if (codeLookup.find(letter) == codeLookup.end()) {
		code = "";
	}
	else {
		code = codeLookup.at(letter);
	}

	return code;
}

//Deletes all tree nodes
void HuffmanTree::makeEmpty(BinaryNode *& t) 
{	
	if (t) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t; 
	}
}

//makeEmpty recursive function
void HuffmanTree::makeEmpty()
{
	makeEmpty(this->root);
}

//Prints chars and frequency
void HuffmanTree::printTree(BinaryNode *node, std::ostream & out) const 
{
	if (node == nullptr) {
		return;
	}
	
	printTree(node->left, out);

	if (node->left == nullptr && node->right == nullptr) {
		//Pseudo EOF Char
		int i = 257;
		char pseudoEOF = i;
		string stringEOF = string(1, pseudoEOF);

		//Dont print if EOF char
		if (node->element != stringEOF) 
			out << node->element << ":" << node->frequency << endl;
			
	}

	printTree(node->right, out);
}

//Prints chars and 0/1 code
void HuffmanTree::printCodes(BinaryNode* node, std::ostream& out, string code) const
{

	//Pseudo EOF Char
	int i = 257;
	char pseudoEOF = i;
	string stringEOF = string(1, pseudoEOF);

	if (node->left == nullptr && node->right == nullptr) {
		
		//Dont print if EOF char
		if (node->element != stringEOF) {
			out << node->element << ":" << code << endl;
			char temp = node->element[0];
		}
	}
	else {
		printCodes(node->left, out, code + "0");
		printCodes(node->right, out, code + "1");
	}
}

//printCodes recursive function
void HuffmanTree::printCodes(std::ostream& out) const
{
	printCodes(this->root, out, "");
}

//printTree recursive function 
void HuffmanTree::printTree(std::ostream& out) const
{
	printTree(this->root, out);
}

//Saves to unordered map
void HuffmanTree::saveTree(BinaryNode * current, string code) 
{	
	if (current->left == nullptr && current->right == nullptr) {
		char temp = current->element[0];
		codeLookup[temp] = code;
	}
	else {
		saveTree(current->left, code + "0");
		saveTree(current->right, code + "1");
	}
}

//Constructor from string
HuffmanTree::HuffmanTree(string frequencyText) 
{
	root = buildTree(frequencyText);
	saveTree(root, string());  
}

//Constructor from file
HuffmanTree::HuffmanTree(ifstream & frequencyStream) 
{ 	

	std::string frequencyText( (std::istreambuf_iterator<char>(frequencyStream)),std::istreambuf_iterator<char>() );

	frequencyStream.close();
	if (frequencyText.size() > 0) {
		root = buildTree(frequencyText);
		saveTree(root, string());  
	}
}

//Destructor 
HuffmanTree::~HuffmanTree() 
{	
	this->makeEmpty();
}

//Builds tree 
HuffmanTree::BinaryNode* HuffmanTree::buildTree(string frequencyText) 
{
	//PQ for nodes
	priority_queue<HuffmanTree::BinaryNode*, vector<HuffmanTree::BinaryNode*>, compareBinaryNodes > nodes;

	//Pseudo EOF Char
	int i = 257;
	char pseudoEOF = i;
	frequencyText.push_back(pseudoEOF);

	//Buildung Frequency Table 
	unordered_map<char, int> table;
	for (int i = 0; i < frequencyText.length(); i++) {
		char currentChar = frequencyText[i];

		//Table contains key already
		if (table.count(currentChar) > 0) {
			table[currentChar] = table[currentChar] + 1;
		}
		else {
			table[currentChar] = 1;
		}
	}

	//Creating and adding nodes to queue
	for (auto pair : table) {

		string t(1, pair.first);
		BinaryNode temp(t, pair.second, nullptr, nullptr);

		nodes.push(new BinaryNode(t, pair.second, nullptr, nullptr));
	}

	//Building Tree
	while (nodes.size() > 1) {

		//Parent String
		string parentString = "";

		//Child nodes
		BinaryNode* tempLeft = nodes.top();
		parentString += tempLeft->element;
		nodes.pop();

		BinaryNode* tempRight = nodes.top();
		parentString += tempRight->element;
		nodes.pop();

		//Parent node
		int totalFrequency = tempLeft->frequency + tempRight->frequency;
		BinaryNode* parentNode = new BinaryNode(parentString, totalFrequency, tempLeft, tempRight);

		nodes.push(parentNode);
	}

	return nodes.top();
}

//Returns decodes char vector
string HuffmanTree::decode(vector<char> encodedBytes) {

	//Pseudo EOF Char
	int i = 257;
	char pseudoEOF = i;

	string decoded;
	string code = "";

	//Getting 0/1s from char vector
	for (int i = 0; i < encodedBytes.size() - 1; i++) {

		//Reading bits of char
		for (int j = 0; j <= 7; j++)
		{
			if ((encodedBytes[i] >> j) & 0x1) {
				code += "1";
			}
			else {
				code += "0";
			}
		}
	}

	string stringCode = "";

	//Decoding 0/1s string to chars
	for (int i = 0; i < code.length(); i++) {

		stringCode += code[i];

		//Check if code = value
		for (auto it = codeLookup.begin(); it != codeLookup.end(); ++it) {

			if (it->second == stringCode) {

				//Pseudo EOF found
				if (it->first == pseudoEOF) {
					return decoded; // Jumping out of function here
				}

				decoded = decoded + it->first;
				stringCode = "";
			}
		}
	}

	return decoded;
}

//Returns encoded char vector 
vector<char> HuffmanTree::encode(string stringToEncode) {

	//Pseudo EOF Char
	int i = 257;
	char pseudoEOF = i;
	stringToEncode.push_back(pseudoEOF);

	vector<char> encoded;	
	unsigned char encodedChar = 0;
	string code = "";
	string tempCode = "";

	//Loop through each letter in string to encode
	for (int i = 0; i < stringToEncode.length(); i++) {

		//Find code for letter
		tempCode = this->getCode(stringToEncode[i]);
		code += tempCode;
	}

	//0s and 1s string not seperated by groupd of 8
	//Seperate code string into groups of 8 
	vector<string> bitsVector;
	string eightChars = "";

	//Adds 8 0/1s to string then to vector 
	for (int i = 0; i < code.length(); i++) {
	
		eightChars += code[i];
		
		if (eightChars.length() > 7) {
			bitsVector.push_back(eightChars);
			eightChars = "";
		}
	}

	//Adding leftover 0/1s to vector with padded 0s
	if (eightChars.length() > 0) {

		int zerosToAdd = 8 - eightChars.length();

		for (int i = 0; i < zerosToAdd; i++)
			eightChars += "0";
	}

	bitsVector.push_back(eightChars);

	for (vector<string>::iterator t = bitsVector.begin(); t != bitsVector.end(); ++t) {
		
		string bits = *t;

		//Setting bits of encoded char
		for (int i = 0; i < 8; i++) {
			if (bits[i] == '1') {
				encodedChar = setBit(encodedChar, i);
			}
		}

		encoded.push_back(encodedChar);
		encodedChar = 0;
	}

	return encoded;
}

//Decodes and writes to file
void HuffmanTree::uncompressFile(string compressedFileName, 
								 string uncompressedToFileName) {	

	std::ifstream input(compressedFileName, std::ios::in | std::ios::binary);
	std::ofstream output(uncompressedToFileName, ios::out | ios::binary);

	vector<char> encoded;

	//Reads compressed file into char vector
	while (!input.eof()) 
		encoded.push_back(input.get());	

	//Decodes chars
	string decodedString = this->decode(encoded);

	//Writing to file
	for (int i = 0; i < decodedString.size(); i++)
		output << decodedString[i];

	input.close();
	output.close();
}

//Encodes and writes to file
void HuffmanTree::compressFile(string compressToFileName, 
							   string uncompressedFileName) {	

	std::ifstream input(uncompressedFileName, ios::in | ios::binary);
	std::ofstream output(compressToFileName, ios::out | ios::binary);

	unsigned char encodedChar;
	string encodedString;

	//Reads from file and adds to string
	while (!input.eof()) {
		encodedChar = input.get();
		encodedString.push_back(encodedChar);
	}

	//Endoded chars 
	vector<char> codeChar = this->encode(encodedString);

	//Writing to file
	output.write(reinterpret_cast<const char*>(&codeChar[0]), codeChar.size() * sizeof(char));

	input.close();
	output.close();
}

