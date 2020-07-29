#pragma once

#include "trie.hh"
#include "patricia_builder.hh"

#include <iostream>
#include <fstream>


namespace compiler
{
    trie::TrieNode* get_trie_from_file(char*);

    void patricia_write(char*, const patricia::Patricia&, uint32_t nb_node);

}
