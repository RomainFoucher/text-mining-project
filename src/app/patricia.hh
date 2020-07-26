#pragma once


#include <cstdint>
#include <string>
#include <vector>

struct Data;

struct TrieNode {
    bool end_of_word = false;
    // Array of Data
    size_t nb_children = 0;
    struct Data* children = nullptr;
};

// TODO 32
struct Data {
    char next_char{};
    uint64_t index{};
    uint64_t len{};
    TrieNode child;
};

void trie_node_clean(TrieNode);

class Patricia {
public:
    TrieNode root;
    std::vector<std::string> *table = new std::vector<std::string>;

    ~Patricia()
    {
        trie_node_clean(root);
        free(table);
    }
};


bool search(const Patricia* root, const std::string& word);
Patricia get_patricia_from_file(char*);



