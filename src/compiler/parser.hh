#pragma once

#include "trie.hh"
#include "patricia_builder.hh"

#include <iostream>
#include <fstream>


namespace compiler
{
    trie::TrieNode* get_trie_from_file(char*);

    void patricia_write(const patricia::Patricia&, char*);
}