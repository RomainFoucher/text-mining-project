#pragma once

#include <map>
#include <string>

namespace {
    using namespace std;
}

struct TrieNode
{
    map<char,TrieNode*> children;
    bool endofword;
    int prefixes;
    TrieNode()
    {
        endofword=false;
        prefixes=0;
    }
};

void insert(TrieNode *root, const string& word);

bool search(TrieNode *root, const string& word);

void destroy(TrieNode * root);
