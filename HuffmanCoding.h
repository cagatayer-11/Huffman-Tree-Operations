
#ifndef ASSIGNMENT_4_HUFFMANCODING_H
#define ASSIGNMENT_4_HUFFMANCODING_H
#include <map>
#include <vector>
#include <iostream>
using namespace std;
class HuffmanCoding {
private:
    struct TreeNode{
        char data;
        int freq;
        TreeNode* right;
        TreeNode* left;

    };
    TreeNode *root;


public:
    map<char,string>encodeDict; // For using "-s character" command.

    void makeHuffmanTree(map<char,int>map);
    void redesignOrder(vector<TreeNode*>&trees);
    void encodingHuffmanTree(vector<char>*v = nullptr);
    void encode(TreeNode* node,string str);
    void decodingHuffmanTree(string encodedString);
    void decode(TreeNode* node,string encodedString,string &decodedString,int &shiftNumber);
    void display();
    void printTree(TreeNode *node,int spaceNumber);
    bool isLeaf(TreeNode *node);





};


#endif //ASSIGNMENT_4_HUFFMANCODING_H
