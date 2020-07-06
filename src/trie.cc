#include "trie.hh"

#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

void insert(TrieNode *root, const string& word)
{
    TrieNode *current=root;
    for(const char& i : word)
    {
        char ch=i;
        TrieNode *node=current->children[ch];
        if(!node)
        {
            node=new TrieNode();
            current->children[i]=node;
        }
        current=node;
        current->prefixes++;
    }
    current->endofword=true;
}

bool search(TrieNode *root,const string& word)
{
    TrieNode *current=root;
    for(const char& ch : word)
    {
        TrieNode *node=current->children[ch];
        if(!node)
            return false;
        current=node;
    }
    return current->endofword;
}

void destroy(TrieNode * root)
{
    for(const auto& i : root->children)
    {
        destroy(i.second);
    }
    delete(root);
}