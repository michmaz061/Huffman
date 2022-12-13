#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "head.h"
#define EMPTY_STRING ""
using namespace std;
int main(int argc, char *argv[]) {
    string text;
    string input;
    string output;
    string result;
    string dictionary;
    fstream in;
    fstream out;
    fstream dict;
    size_t operatorIndicator = 1;
    char mode;
    while(operatorIndicator < argc && argv[operatorIndicator][0] == '-'){

        switch (argv[operatorIndicator][1]) {
            case 'i':
                operatorIndicator = operatorIndicator + 1;
                input=argv[operatorIndicator];
                in.open(input, ios::in|ios::binary);
                if (in.fail()) {
                    cout << "Input file does not exist.\n";
                    return 0;
                }
                cout<<"Input: "<<input<<endl;
                operatorIndicator = operatorIndicator + 1;
                break;
            case 'o':
                operatorIndicator = operatorIndicator + 1;
              output=argv[operatorIndicator];
              cout<<"Output: "<<output<<endl;
                    out.open(output,ios::out|ios::binary);
                operatorIndicator = operatorIndicator + 1;
                break;
            case 'm':
                operatorIndicator = operatorIndicator + 1;
                switch (argv[operatorIndicator][1]) {
                    case 'c':
                        cout<<"Compression mode was chosen.\n";
                        operatorIndicator = operatorIndicator + 1;
                        mode='c';
                        break;
                    case 'd':
                        cout<<"Decompression mode was chosen.\n";
                        operatorIndicator = operatorIndicator + 1;
                        mode='d';
                        break;
                    default:
                        break;
                }
                break;
            case 'd':
                operatorIndicator = operatorIndicator + 1;
                dictionary=argv[operatorIndicator];
                cout<<"Dictionary: "<<dictionary<<endl;
                operatorIndicator = operatorIndicator + 1;
                break;
            default:
                break;
        }
    }

    if(mode=='c') {
        if (!input.empty()) {
            while (getline(in, text))
                result += text;
            dict.open(dictionary, ios::out);
            buildHuffmanTree(result,out, dict, in);
        }
    }
if (mode=='d') {
        dict.open(dictionary, ios::in);
    decompress(out,in);
}
    cout<<"Done"<<endl;
    dict.close();
    in.close();
    out.close();
    return 0;
}
