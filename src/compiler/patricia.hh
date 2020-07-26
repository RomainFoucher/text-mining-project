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
        TrieNode* child;
    };

    struct TrieNode {
        bool end_of_word = false;
        std::map<char, Data> children;
    };

    void trie_node_delete(TrieNode*);

    class Patricia {
    public:
        TrieNode *root;
        std::string table;

        ~Patricia()
        {
            trie_node_delete(root);
        }
    };

    void patricia_print(const Patricia&);

    std::string get_string_from_table(const std::string& table,
            uint64_t index, uint64_t len);
}

