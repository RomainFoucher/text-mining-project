#pragma once


#include <cstdint>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


namespace common
{
    /*!
     * Trie node.
     */
    struct TrieNode
    {
        uint64_t data_offset = 0; /**< Offset of first data */
        uint32_t frequency = 0;   /**< Frequency */
        uint8_t nb_children = 0;  /**< Number of children */
        // Padding
        uint8_t padding_1{};      /**< Padding. Not used. */
        uint16_t padding_2{};     /**< Padding. Not used. */
    };

    /*!
     * Return if this node is terminal (not a leaf).
     *
     * @param node the node to check.
     * @return the boolean value.
     */
    bool end_of_word(const TrieNode* node);

    /*!
     * Struct representing the link between two nodes.
     */
    struct Data
    {
        uint64_t next_node_offset = 0; /**< Child to jump to */
        uint64_t chars_offset = 0;     /**< Offset of first char */
        uint8_t chars_size = 0;        /**< Length of string */
        // Padding
        uint8_t padding_1{};           /**< Padding. Not used. */
        uint16_t padding_2{};          /**< Padding. Not used. */
        uint32_t padding_3{};          /**< Padding. Not used. */
    };

    /*!
     * Patricia holder
     */
    class Patricia
    {
    public:
        TrieNode root;                /**< Root to load in memory */

        // Memory
        int fd = -1;                  /**< File descriptor of serialized patricia trie */
        char* mmap_pointer = nullptr; /**< Mmap pointer to serialized patricia trie */
        size_t mmap_size = 0;         /**< Mmap size */

        /*!
         * Destructor.
         * Close file and clean memory.
         */
        ~Patricia()
        {
            close(fd);
            munmap(mmap_pointer, mmap_size);
        }
    };

    /*!
     * Load a patricia from a file.
     *
     * @param input_name file to load from.
     * @return build patricia. Root is correctly loaded.
     */
    Patricia get_patricia_from_file(char* input_name);

    /**
     * Get a child link (aka Data) from a node.
     *
     * @param patricia the patricia holder.
     * @param node the node to get a child from.
     * @param child_nb index of the child. Within 0 and node.nb_children.
     * @return the data.
     */
    Data* get_data_i(const Patricia& patricia, uint64_t data_offset, uint8_t child_nb);

    /*!
     * Get char pointer corresponding to a data.
     *
     * @param patricia the patricia holder.
     * @param data the data to get char pointer from.
     * @return the char pointer.
     */
    char* get_chars(const Patricia& patricia, uint64_t chars_offset);

    /*!
     * Get child from a data.
     *
     * @param patricia the patricia holder.
     * @param data the data to get node from.
     * @return the child node.
     */
    TrieNode* get_child(const Patricia& patricia, uint64_t next_node_offset);

    /* DEBUG */
    /*!
     * Print a patricia.
     *
     * @param patricia the patricia to print.
     */
    [[maybe_unused]] void patricia_print(const Patricia& patricia);
}
