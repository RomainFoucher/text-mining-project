#pragma once

#include <string>
#include <map>
#include <vector>

#include "patricia_builder.hh"

namespace compiler::trie
{
    /*!
     * Simple trie.
     */
    struct TrieNode
    {
        uint32_t frequency = 0;
        std::map<std::string, TrieNode*> children;
    };

    /*!
     * Return if this node is terminal (not a leaf).
     *
     * @param node the node to check.
     * @return the boolean value.
     */
    bool end_of_word(const TrieNode&);

    /*!
     * Merge a trie to produce a patricia.
     * Also keep count of number of nodes seen.
     *
     * @param root first node.
     * @param nb_node reference to number of node.
     * @return the build patricia.
     */
    patricia::Patricia trie_merge(TrieNode* root, uint32_t& nb_node);

    /*!
     * Insert string in a trie.
     *
     * @param root first node.
     * @param word word to insert.
     * @param freq frequency of given word.
     */
    void trie_insert(TrieNode *root, const std::string &word, uint32_t freq);

    /*!
     * Destroy a trie.
     * Calls delete.
     *
     * @param root to destroy recursively.
     */
    void trie_destroy(struct TrieNode* root);

    /* DEBUG */
    /*!
    * Print a trie.
    *
    * @param patricia the patricia to print.
    */
    [[maybe_unused]] void trie_print(const TrieNode *root);
}
