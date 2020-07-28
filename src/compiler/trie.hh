#pragma once

#include <string>
#include <map>
#include <vector>

#include "patricia.hh"

namespace compiler::trie
{
    struct TrieNode
    {
        std::map<std::string, TrieNode*> children;
        bool end_of_word = false;
        uint32_t frequency;
    };

    patricia::Patricia trie_merge(TrieNode *, uint32_t&);

    void trie_insert(TrieNode *root, const std::string &word, uint32_t);

    void trie_destroy(struct TrieNode* root);

    void trie_print(const TrieNode *root);
}
