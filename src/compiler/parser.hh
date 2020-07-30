#pragma once

#include "trie.hh"
#include "patricia_builder.hh"

#include <iostream>
#include <fstream>


namespace compiler
{
    /*!
     * Build trie from a file with dictionary format
     *
     * @param input_name file name
     * @return the built trie
     */
    trie::TrieNode* get_trie_from_file(char* input_name);

    /*!
     * Write a patricia builder on file with patricia format.
     *
     * @param output_name file name
     * @param patricia the builder to serialize
     * @param nb_node number of node in the tree; optimization purpose
     */
    void patricia_write(char* output_name, const patricia::Patricia& patricia, uint32_t nb_node);
}
