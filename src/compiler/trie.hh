#pragma once

#include <string>
#include <map>
#include <vector>

struct TrieNode
{
    std::map<std::string, TrieNode*> children;
    bool end_of_word = false;
    TrieNode() = default;
};

void insert(TrieNode* root, const std::string& word);

bool search(const TrieNode* root, const std::string& word);

void destroy(struct TrieNode* root);

void print_trie(const TrieNode* root);
