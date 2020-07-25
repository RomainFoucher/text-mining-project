#pragma once


#include <cstdint>
#include <string>

// TODO uint32...
struct TrieNode {
    uint64_t index_bst_start;
    uint64_t index_bst_end;
    bool end_of_word;
};


bool search(const TrieNode* root, const std::string& word);


