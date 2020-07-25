#pragma once

#include <map>
#include <string>

struct TrieNode
{
    std::map<char, TrieNode*> children;
    bool endofword = false;
    int prefixes = 0;
    TrieNode() = default;
};

void insert(TrieNode* root, const std::string& word);

bool search(const TrieNode* root, const std::string& word);

void destroy(TrieNode* root);

void print_trie(const TrieNode* root);
