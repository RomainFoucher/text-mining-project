#pragma once

#include "trie.hh"

#include <iostream>
#include <fstream>

TrieNode *get_trie_from_file(std::ifstream&);
void write_trie(TrieNode*, std::ofstream&);