
#include "HuffmanCoding.h"



void HuffmanCoding::makeHuffmanTree(map<char,int> map) { // In this method create tree with respect to char-freq map.
    vector<TreeNode *> trees;
    for (auto keyValue : map) { // Create tree nodes.
        TreeNode *newNode = new TreeNode;
        newNode->data = keyValue.first;
        newNode->freq = keyValue.second;
        newNode->right = nullptr;
        newNode->left = nullptr;
        trees.push_back(newNode);
    }
    redesignOrder(trees); // Sort nodes with respect to frequency.
    while (trees.size() != 1) { // Merging operation.
        TreeNode *left = trees[0];
        trees.erase(trees.begin());
        TreeNode *right = trees[0];
        trees.erase(trees.begin());
        int sumFreq = left->freq + right->freq;
        TreeNode *temp = new TreeNode;
        temp->data = '#'; // Represents empty node.
        temp->freq = sumFreq;
        temp->left = left;
        temp->right = right;
        trees.push_back(temp);
        redesignOrder(trees);
    }
    root = trees[0]; // Set root.
    trees.erase(trees.begin());
}
void HuffmanCoding::redesignOrder(vector<TreeNode *> &trees) { // Sorting method with compering freq.
    for (int i = 0; i < trees.size(); i++) {
        for (int j = i; j < (trees.size()); j++) {
            if (trees[i]->freq > trees[j]->freq ) {
                swap(trees[i], trees[j]);
            }
        }
    }
}

bool HuffmanCoding::isLeaf(TreeNode *node) { // Checks if given node leaf.
    return  node->left == nullptr && node->right == nullptr;
}

void HuffmanCoding::encodingHuffmanTree(vector<char>*v) { // Encode created tree and print encoded string from encode method.
    encode(root, "");
    string encodedString;
    if (v != nullptr){
        for (const char c:*v) {
            for (const pair<char,string>p:encodeDict) {
                if (tolower(c) == p.first){
                    encodedString= encodedString+p.second;
                }
            }
        }
        cout<<encodedString<<endl;
    }
}

/* In this method , traverse in tree and while reaching a leaf
 * if node goes right it adds 1 , if node goes left it adds 0.
 * */
void HuffmanCoding::encode(TreeNode *node,string str) {
    if (node == nullptr) { // Check if node equals nullptr.
        return;
    }
    if (isLeaf(node)) { // If method reaches a leaf. It makes pairs char-encoded number.
        if (node->data != '#') {
            encodeDict[node->data] = str;
        }
    } else {
        if (node->left) { // Controls if node goes left.
            encode(node->left, str + "0");
        }
        if (node->right) { // Controls if node goes right.
            encode(node->right, str + "1");
        }
    }
}

// Decodes encoded numbers and then prints out decoded numbers
void HuffmanCoding::decodingHuffmanTree(string encodedString) {
    if (isLeaf(root)){ // Controls if created tree has only one child.
        while (root->freq--) {
            cout << root->data;
        }
        return;
    }
    int shiftNumber = -1; // For traverse in encodedString.
    string decodedNumbers;
    while (shiftNumber<(int)encodedString.size()-1){
        decode(root,encodedString,decodedNumbers,shiftNumber);
    }
    cout << decodedNumbers<<endl;
}

/*
 * In this method , traverses in tree according to encodedString's bits
 * if '0' it goes left, if '1' it goes right way.And also check
 * if node it reached is a leaf then returns node's data.
 */
void HuffmanCoding::decode(TreeNode *node, string encodedString,string &decodedString ,int &shiftNumber) {

    if (node == nullptr){ // Check if node equals nullptr.
        return;
    }
    while (!isLeaf(node)){ // If incoming node is not a leaf , It keeps going searching.
        if (encodedString[shiftNumber] == '0'){
                node = node->left;
        }
        else if (encodedString[shiftNumber] == '1'){
                node = node->right;
        }
        shiftNumber++;
    }
    decodedString = decodedString+node->data;
}

/*
 * It traverses in tree and print out each nodes and edges.
 */
void HuffmanCoding::printTree(TreeNode *node,int spaceNumber) {
    if (node == nullptr){
        return;
    }
    for (int i = 0; i <spaceNumber ; i++) {
        if (i % 5 == 1){
            cout<<"|";
        }
        cout<<" ";

    }
    if (node->data == ' '){ // Special symbol for space(' ').
        cout<<"''" << "==="<<"("<<node->freq<<")"<<endl;
    } else{
        cout << node->data <<"==="<<"("<<node->freq<<")"<<endl;
    }
    printTree(node->left,spaceNumber+5);
    printTree(node->right,spaceNumber+5);
}

void HuffmanCoding::display() {
    int spaceNumber = 0;
    printTree(root,spaceNumber);
}








