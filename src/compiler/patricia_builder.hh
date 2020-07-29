#pragma once


#include <vector>
#include <string>
#include <map>

namespace compiler::patricia {
    struct TrieNode;

    // TODO 32
    struct Data {
        uint32_t index = 0;
        // 256 character MAX
        uint8_t len = 0;
        TrieNode* child = nullptr;
    };

    struct TrieNode {
        uint32_t id{};
        uint32_t frequency = 0;
        std::map<char, Data> children;
    };

    bool end_of_word(const TrieNode&);

    void trie_node_delete(TrieNode*);

    class Patricia {
    public:
        TrieNode *root;
        std::string table;
        Patricia()
        {
            root = new TrieNode();
        }
        ~Patricia()
        {
            trie_node_delete(root);
        }
    };

    std::string get_string_from_table(const std::string& table,
            uint32_t index, uint8_t len);

    /* DEBUG */
    [[maybe_unused]] void patricia_print(const Patricia&);
}

