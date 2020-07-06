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

