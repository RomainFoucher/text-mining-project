#pragma once


#include <vector>
#include <string>
#include <map>

namespace patricia {
    struct TrieNode;

    // TODO 32
    struct Data {
        uint32_t index;
        // 256 character MAX
        uint8_t len;
        TrieNode* child;
    };

    struct TrieNode {
        bool end_of_word = false;
        uint32_t frequency = 0;
        std::map<char, Data> children;
    };

    void trie_node_delete(TrieNode*);

    class Patricia {
    public:
        TrieNode *root;
        std::string table;
        Patricia();
        ~Patricia()
        {
            trie_node_delete(root);
        }
    };

    void patricia_print(const Patricia&);

    std::string get_string_from_table(const std::string& table,
            uint32_t index, uint32_t len);
}

