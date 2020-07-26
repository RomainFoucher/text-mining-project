#pragma once

#include "trie.hh"
#include "patricia.hh"

#include <iostream>
#include <fstream>

trie::TrieNode* get_trie_from_file(char*);
void patricia_write(const patricia::Patricia&, char*);