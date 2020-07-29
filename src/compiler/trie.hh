#pragma once

#include <string>
#include <map>
#include <vector>

#include "patricia_builder.hh"

namespace compiler::trie
{
    struct TrieNode
    {
        uint32_t frequency = 0;
        std::map<std::string, TrieNode*> children;
    };

    bool end_of_word(const TrieNode&);

    patricia::Patricia trie_merge(TrieNode *, uint32_t&);

    void trie_insert(TrieNode *root, const std::string &word, uint32_t);

    void trie_destroy(struct TrieNode* root);

    /* DEBUG */
    [[maybe_unused]] void trie_print(const TrieNode *root);
}
