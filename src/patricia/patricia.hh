#pragma once


#include <cstdint>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


namespace common
{
    struct TrieNode
    {
        uint64_t data_offset = 0;
        uint32_t frequency = 0;
        uint8_t nb_children = 0;
        // Padding
        uint8_t padding_1{};
        uint16_t padding_2{};
    };

    bool end_of_word(const TrieNode&);

    struct Data
    {
        uint64_t next_node_offset = 0;
        uint64_t chars_offset = 0;
        uint8_t chars_size = 0;
        // Padding
        uint8_t padding_1{};
        uint16_t padding_2{};
        uint32_t padding_3{};
    };

    class Patricia
    {
    public:
        TrieNode root;

        // Memory
        int fd = -1;
        char* mmap_pointer = nullptr;
        size_t mmap_size = 0;

        ~Patricia()
        {
            close(fd);
            munmap(mmap_pointer, mmap_size);
        }
    };

    Patricia get_patricia_from_file(char*);

    Data get_data_i(const Patricia&, const TrieNode&, uint8_t child_nb);

    char* get_chars(const Patricia&, const Data&);

    TrieNode get_child(const Patricia&, const Data&);

    /* DEBUG */
    [[maybe_unused]] void patricia_print(const Patricia& patricia);
}
