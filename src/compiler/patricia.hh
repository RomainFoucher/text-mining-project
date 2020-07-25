#pragma once


#include <vector>
#include <string>
#include <map>

namespace patricia {
    struct TrieNode;

    // TODO 32
    struct Data {
        uint64_t index;
        uint64_t len;
        TrieNode *child;
    };

    struct TrieNode {
        bool end_of_word = false;
        std::map<char, Data> children;
    };

    void trie_node_delete(TrieNode*);

    class Patricia {
        TrieNode *root;
        std::vector<std::string> *table = new std::vector<std::string>;

        ~Patricia()
        {
            trie_node_delete(root);
            free(table);
        }
    };

}

