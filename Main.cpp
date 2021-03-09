#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "HuffmanCoding.h"

using namespace std;

map<char,int> makingMap(){ // Returns map , for using -decode, -l and -s char.
    ifstream inFile;
    // open the file stream
    inFile.open("forTree.txt");
    // check if opening a file failed
    if (inFile.fail()) {
        cerr << "Error opening a file" << endl;
        inFile.close();
        exit(1);
    }
    map<char, int> charFreq;
    string line;
    while (getline(inFile, line)){ // Splitting by "\n"
        int x = line[1];
        charFreq.insert({line[0],x-48}); // Create a char-freq map.
    }
    return charFreq;
}
int main(int argc,char*argv[]) {

    // Take arguments in a string.
    if (argc > 1){
        string arg1(argv[1]);
    }
    vector<string> allArgs(argv, argv + argc);
    string command;
    for_each(allArgs.begin(), allArgs.end(), [&](const string &piece){ command = command+piece+" "; });
    //---------------------------------------------------------


    HuffmanCoding huffmanCoding;
    stringstream ss(command);
    string segment;
    vector<string> seglist;
    while(getline(ss, segment, ' ')){ // Splitting line by delimiter ' '.
        seglist.push_back(segment);
    }

    // Apply commands accordingly created previous command string.
    if (seglist[1] == "-i"){
        if (seglist[3] == "-encode"){

            ifstream inFile;
            // open the file stream
            inFile.open(seglist[2]);
            // check if opening a file failed
            if (inFile.fail()) {
                cerr << "Error opening a file" << endl;
                inFile.close();
                exit(1);
            }

            ofstream o;
            o.open("forTree.txt"); // Save char-freq pair for creating tree again.
            string s;
            string line;
            while (getline(inFile, line)){ // Splitting by "\n"
                s=line;
            }
            map<char, int> charFreq;
            vector<char> v(s.begin(), s.end()); // Vector which includes each char in input file.
            for (const char c:v) {
                charFreq[tolower(c)]++; // Find frequency each char and make pair.
            }
            for (auto p:charFreq) {
                o<<p.first<<p.second<<endl; // Write info to forTree.txt.
            }
            huffmanCoding.makeHuffmanTree(charFreq); // Create Huffman Tree.
            huffmanCoding.encodingHuffmanTree(&v); // Encode Huffman Tree.
            o.close();
        }

        else if (seglist[3] == "-decode"){

            ifstream inFile;
            // open the file stream
            inFile.open(seglist[2]);
            // check if opening a file failed
            if (inFile.fail()) {
                cerr << "Error opening a file" << endl;
                inFile.close();
                exit(1);
            }
            string s;
            string line;
            while (getline(inFile, line)){
                s=line;
            }

            // With using makingMap() method create a new char-freq map according to forTree.txt.
            huffmanCoding.makeHuffmanTree(makingMap());
            huffmanCoding.decodingHuffmanTree(s+" "); // Decode Huffman Tree.
        }
    }
    else if (seglist[1] == "-s"){
        huffmanCoding.makeHuffmanTree(makingMap()); // Again create a map and tree.
        huffmanCoding.encodingHuffmanTree(); // Encode operation
        for (auto p:huffmanCoding.encodeDict) {  // Searching incoming character in encodeDict map.
            char chr = seglist[2][0];
            if (chr == '\000'){
                if (p.first == ' '){
                     cout<<"Encoded form "<<"''"<<" : "<<p.second<<endl;
                }
            }
            if (chr == p.first){
                cout<<"Encoded form "<<chr<<" : "<<p.second<<endl;
            }
        }
    }
    else if (seglist[1] == "-l"){
        huffmanCoding.makeHuffmanTree(makingMap()); //Again create a map and tree.
        huffmanCoding.display(); // Print tree list.
    }
}
