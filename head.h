#ifndef HUFFMAN_HEAD_H
#define HUFFMAN_HEAD_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#define EMPTY_STRING ""
using namespace std;
///
/// \brief Tree node
/// \param ch character from the line of text
/// \param freq frequency of character
///
struct Node
{
    char ch;
    int freq;
    Node *left, *right,*next;
};
///
/// \brief comparision for object to be used to order the heap
///
struct comp
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};
///
/// \brief function to check if Huffman Tree contains only a single node
/// \param root root of the tree
/// \return true or false
///
bool isLeaf(Node* root);
///
/// \brief Traverse the Huffman Tree and store Huffman Codes in a map
/// \param root root of the tree
/// \param str coded letter as number
/// \param huffmanCode tree with huffman codes
/// \param head head of the list
///
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode, Node* head);
///
/// \param out output file which will have the decompressed data
/// \param in input file which will be decompressed
void decompress(fstream& out,fstream& in);
///
/// \param str encoded string to compress
/// \param out output file which will be compressed
void compress(string str,fstream& out);
///
/// \brief Traverse the Huffman Tree and decode the encoded string
/// \param root root of the tree
/// \param index number of which 0 or 1 checking for the decoding
/// \param str line of huffman code
/// \param head head of the list
///
void decode(Node* root, int &index, string str, Node* head);
///
/// \brief Builds Huffman Tree and helps decode given input text
/// \param text line of text from input file
/// \param out
/// \param dict
/// \param in
void buildHuffmanTree(string text,fstream& out,fstream& dict,fstream& in);
///
/// \brief Function responsible for opening files and starting the program.
/// \param argc one of argument's parameter.
/// \param argv one of argument's parameter.
/// \return returns value of exit code
int main(int argc, char *argv[]);
#endif //HUFFMAN_HEAD_H
