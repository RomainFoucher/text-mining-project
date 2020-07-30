#pragma once


#include <vector>
#include <string>
#include <map>

namespace compiler::patricia {
    struct TrieNode;

    /*!
     * Struct representing the link between two nodes.
     */
    struct Data {
        uint32_t index = 0;        /**< Index of first char */
        // 256 character MAX
        uint8_t len = 0;           /**< Length of string */
        TrieNode* child = nullptr; /**< Child to jump to */
    };

    /*!
     * A node.
     */
    struct TrieNode {
        uint32_t id{};                 /**< Id of the node by prefix order */
        uint32_t frequency = 0;        /**< Frequency */
        std::map<char, Data> children; /**< Children with at least a char to link */
    };

    /*!
     * Return if this node is terminal (not a leaf).
     *
     * @param node the node to check.
     * @return the boolean value.
     */
    bool end_of_word(const TrieNode& node);

    /*!
     * Delete node (calls delete).
     *
     * @param node the node to delete.
     */
    void trie_node_delete(TrieNode* node);

    /*!
     * Patricia builder.
     */
    class Patricia {
    public:
        TrieNode *root;    /**< Root of trie */
        std::string table; /**< Collection of all string in the trie */

        /*!
         * Constructor.
         * Create root.
         */
        Patricia() { root = new TrieNode(); }

        /*!
         * Destructor.
         * Delete root.
         */
        ~Patricia() { trie_node_delete(root); }
    };

    /*!
     * Get a string from table.
     *
     * @param table the table to get from.
     * @param index beginning of the string.
     * @param len length of the string.
     * @return the built string.
     */
    std::string get_string_from_table(const std::string& table,
            uint32_t index, uint8_t len);

    /* DEBUG */
    /*!
     * Print a patricia.
     *
     * @param patricia the patricia to print.
     */
    [[maybe_unused]] void patricia_print(const Patricia& patricia);
}

