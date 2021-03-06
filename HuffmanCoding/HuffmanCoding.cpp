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
#include <fstream>
#include <streambuf>
#include <queue>
#include <functional>

using namespace std;

int main() {

	//Test 1 
	//Using String to create tree and printing codes
	cout << "Test 1\n";
	cout << "Building the tree from: HHHHEELLLLLLLOO WOOOOORRLLLLLLDP\n\n";
	HuffmanTree tree("HHHHEELLLLLLLOO WOOOOORRLLLLLLDP");
	
	cout << "printTree: \n";
	tree.printTree();
	
	cout << "\nprintCodes:\n";
	tree.printCodes();

	cout << endl;
	cout << "Code L :" <<tree.getCode('L') << endl;
	cout << "Code D :" << tree.getCode('D') << endl;
	cout << endl;

	//Test 2
	//Encoding and decoding using first tree
	cout << "Test 2\n";
	cout << "Encoding and decoding using first tree \n\n"; 
	vector<char> encoded = tree.encode("HELP"); 

	cout << "Encoding: \"HELP\" \n";

	cout << "\nprintBinary:\n";
	tree.printBinary(encoded);
	
	cout << "\n\nDecoded: " << tree.decode(encoded) << endl;

	//Test 3
	//Reading from small file to create tree, compress, and duncompress
	cout << "\nTest 3\n";
	cout << "Building new tree from small file, compressing and decompressing \n\n";
	std::ifstream frequencyStream("Bigo.txt");
	HuffmanTree tree2(frequencyStream);

	cout << "printTree: \n";
	tree2.printTree();

	cout << "\nprintCodes:\n";
	tree2.printCodes();

	cout << "\nCompressing...\n";
	tree2.compressFile("Bigo.bin", "Bigo.txt");

	cout << "Uncompressing...\n";
	tree2.uncompressFile("Bigo.bin", "Bigo_Rebuilt.txt");


	//Test 4
	//Reading from large file to create tree, compress, and uncompress
	cout << "\nTest 4\n";
	cout << "Building new tree from large file, compressing and decompressing \n\n";
	std::ifstream frequencyStream2("20000leagues.txt");
	HuffmanTree tree3(frequencyStream2);

	cout << "printTree: \n";
	tree3.printTree();

	cout << "\nprintCodes:\n";
	tree3.printCodes();

	cout << "Code L :" << tree3.getCode('L') << endl;

	cout << "\nCompressing...\n";
	tree3.compressFile("20000leaguesComp.bin" ,"20000leagues.txt");

	cout << "Uncompressing...\n";
	tree3.uncompressFile("20000leaguesComp.bin", "20000leagues_Rebuilt.txt");

	system("pause");
    return 0;
}

//Output 
/*
Test 1
Building the tree from: HHHHEELLLLLLLOO WOOOOORRLLLLLLDP

printTree:
L:13
D:1
R:2
H:4
 :1
W:1
P:1
E:2
O:7

printCodes:
L:0
D:10000
R:1001
H:101
 :11000
W:11001
P:11010
E:11011
O:111

Code L :0
Code D :10000

Test 2
Encoding and decoding using first tree

Encoding: "HELP"

printBinary:
10111011-01101010-00100000-

Decoded: HELP

Test 3
Building new tree from small file, compressing and decompressing

printTree:
r:7
h:7
c:7
O:2
F:1
D:1
x:1
y:1
A:1
e:16
g:4
":2
0:1
=:1
.:4
k:4
 :61
t:16
d:8
::2
T:2
p:5
(:5
l:5
m:5
):5
o:20
?:3
w:1
v:2

:6
i:12
n:26
f:13
,:3
b:3
u:7
s:13
a:14

printCodes:
r:00000
h:00001
c:00010
O:0001100
F:00011010
D:00011011
x:00011100
y:00011101
A:00011111
e:0010
g:001100
":0011010
0:00110110
=:00110111
.:001110
k:001111
 :01
t:1000
d:10010
::1001100
T:1001101
p:100111
(:101000
l:101001
m:101010
):101011
o:1011
?:1100000
w:11000010
v:11000011

:110001
i:11001
n:1101
f:11100
,:1110100
b:1110101
u:111011
s:11110
a:11111

Compressing...
Uncompressing...

Test 4
Building new tree from large file, compressing and decompressing

printTree:
8:87
#:1
=:1
%:2
~:1
_:3
/:11
[:23
]:23
K:23
7:91
J:97
O:370
P:376
2:192
5:98
9:48
X:54
;:786
0:398
E:399
T:1649
N:1672
y:6875
u:13577
i:29106
e:56819
s:29148
n:30089
":3419
G:205
D:208
':416
Y:213
6:103
3:110
M:434
x:885
L:453
q:464
g:7797
v:4031
H:471
!:479
-:981
V:121
`:13
Z:6
Q:9
{:16
}:16
(:65
R:259
B:509
U:126
::133
1:283
F:287
):65
@:68
4:73
*:85
p:8261
o:32984
a:35438
l:17440
,:8650
w:9906
d:18844
f:10348
m:10562
t:41839
 :94492
A:1148
?:602
j:299
z:306
W:611
S:612
C:1385
.:5662
c:11285
k:2989
I:3017
b:6159

:12396
r:25205
h:26023

printCodes:
8:000000000000
#:000000000001000000
=:000000000001000001
%:00000000000100001
~:000000000001000100
_:00000000000100011
/:000000000001001
[:00000000000101
]:00000000000110
K:00000000000111
7:000000000010
J:000000000011
O:0000000001
P:0000000010
2:00000000110
5:000000001110
9:0000000011110
X:0000000011111
;:000000010
0:0000000110
E:0000000111
T:00000010
N:00000011
y:000001
u:00001
i:0001
e:001
s:0100
n:0101
":0110000
G:01100010000
D:01100010001
':0110001001
Y:01100010100
6:011000101010
3:011000101011
M:0110001011
x:011000110
L:0110001110
q:0110001111
g:011001
v:0110100
H:0110101000
!:0110101001
-:011010101
V:011010110000
`:011010110001000
Z:0110101100010010
Q:0110101100010011
{:011010110001010
}:011010110001011
(:0110101100011
R:01101011001
B:0110101101
U:011010111000
::011010111001
1:01101011101
F:01101011110
):0110101111100
@:0110101111101
4:0110101111110
*:0110101111111
p:011011
o:0111
a:1000
l:10010
,:100110
w:100111
d:10100
f:101010
m:101011
t:1011
 :110
A:111000000
?:1110000010
j:11100000110
z:11100000111
W:1110000100
S:1110000101
C:111000011
.:1110001
c:111001
k:11101000
I:11101001
b:1110101

:111011
r:11110
h:11111
Code L :0110001110

Compressing...
Uncompressing...
Press any key to continue . . .
*/