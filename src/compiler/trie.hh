#pragma once

#include <string>
#include <map>
#include <vector>

namespace trie
{
    struct TrieNode
    {
        std::map<std::string, TrieNode*> children;
        bool end_of_word = false;
    };

    void trie_insert(TrieNode *root, const std::string &word);

    void trie_destroy(struct TrieNode* root);

    void trie_print(const TrieNode *root);
}
