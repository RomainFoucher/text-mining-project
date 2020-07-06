#pragma once

#include <map>

using namespace std;

struct TrieNode
{
    map<char,TrieNode*> children;
    bool endofword;
    TrieNode()
    {
        endofword=false;
    }
};

void insert(TrieNode *root,const string& word);

bool search(TrieNode *root,const string& word);

void destroy(TrieNode * root);
