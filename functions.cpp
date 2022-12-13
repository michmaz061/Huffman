#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstring>
#include "head.h"
#define EMPTY_STRING ""
using namespace std;
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}

void compress(string str,fstream& out){
    for (int i = 0; i < str.length(); i+=8)
    {
        unsigned char byte = 0;
        string str8 = "";
        if (i + 8 < str.length())
            str8 = str.substr(i, i + 8);
        else
            str8 = str.substr(i, str.length());
        for (int b = 0; b != 8; ++b)
        {
            if (b < str8.length())
                byte |= (str8[b] & 1) << b;
            else
                byte |= 1 << b;
        }
        out.put(byte);
    }
}
void decompress(fstream& out,fstream& in){
    char c;
    while (in.get(c))
    {
        for (int i = 0; i < 8; i++)
            out << ((c >> i) & 1);
    }

}
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode, Node* head)
{
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode,head);
    encode(root->right, str + "1", huffmanCode,head);
}

//void decode(Node* root, int &index, string str, Node* head,fstream& out)
//{
//    if (root == nullptr) {
//        return;
//    }
//
//    if (isLeaf(root)) {
//        out << root->ch;
//        return;
//    }
//
//    index++;
//
//    if (str[index] == '0') {
//        decode(root->left, index, str,head,out);
//    } else {
//        decode(root->right, index, str,head,out);
//    }
//}

void buildHuffmanTree(string text,fstream& out,fstream& dict,fstream& in)
{
    struct Node* head = NULL;
    struct Node* temp;
    struct Node* current = NULL;
    Node *fix;
    if (text.empty()) {
        return;
    }
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;

    for (auto pair: freq) {
        fix =getNode(pair.first, pair.second, nullptr, nullptr);
        fix->next = NULL ;
        if(head==NULL){
            head=fix;
            head->next=NULL;
        }
        else{
            fix->next=head;
            head=fix;
        }
        pq.push(fix);
    }

    while (pq.size() != 1)
    {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top();    pq.pop();
        int sum = left->freq + right->freq;
        //pq.push(getNode('\0', sum, left, right));
        fix = getNode('\0', sum, left, right);
        fix->next = NULL ;
        if(head==NULL){
            head=fix;
            head->next=NULL;
        }
        else{
            fix->next=head;
            head=fix;
        }
        pq.push(fix);
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode,head);

    for (auto pair: huffmanCode) {
        dict << pair.first << " " << pair.second << '\n';
    }

    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    compress(str,out);

//    if (isLeaf(root)) {
//        while (root->freq--) {
//            out << root->ch;
//        }
//    } else {
//        int index = -1;
//        while (index < (int) str.size() - 1) {
//            decode(root, index, str,head,out);
//        }
//    }
//    out << endl;

    current=head;
    while(current)
    {
        temp = current->next;
        delete(current);
        current = temp;
    }
    head = NULL;
    delete(head);
}