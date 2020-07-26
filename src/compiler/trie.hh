#pragma once

#include <string>
#include <map>
#include <vector>

#include "patricia.hh"

namespace trie
{
    struct TrieNode
    {
        std::map<std::string, TrieNode*> children;
        bool end_of_word = false;
    };

    patricia::Patricia trie_merge(TrieNode *root);

    void trie_insert(TrieNode *root, const std::string &word);

    void trie_destroy(struct TrieNode* root);

    void trie_print(const TrieNode *root);
}
