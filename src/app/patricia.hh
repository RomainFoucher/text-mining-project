#pragma once


#include <cstdint>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

struct Data;

struct TrieNode {
    bool end_of_word = false;
    uint32_t frequency = 0;
    // Array of Data
    uint8_t nb_children = 0;
    struct Data* children = nullptr;
};

// TODO 32
struct Data {
    char next_char{};
    uint32_t index{};
    uint8_t len{};
    TrieNode child;
};

void trie_node_clean(TrieNode&);

class Patricia {
public:
    TrieNode root;
    // Array of char
    uint32_t table_size = 0;
    char* table = nullptr;

    // Memory
    int fd = -1;

    ~Patricia()
    {
        trie_node_clean(root);
        close(fd);
        munmap(table, table_size + 1);
    }
};


bool search(const Patricia* root, const std::string& word);
Patricia get_patricia_from_file(char*);
void patricia_print(const Patricia& patricia);



