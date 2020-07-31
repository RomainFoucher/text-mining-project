#include "patricia.hh"

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


using namespace std;

namespace common
{
    bool end_of_word(const TrieNode* node)
    {
        return node->frequency;
    }

    static void load_patricia(Patricia& patricia, int fd)
    {
        struct stat st{};
        fstat(fd, &st);

        patricia.fd = fd;
        patricia.mmap_size = st.st_size;
        patricia.mmap_pointer = (char*) mmap(
                nullptr, // No address to start with
                patricia.mmap_size, // Size is table_size + 1
                PROT_READ, // Read only
                MAP_PRIVATE, // Private
                fd, // Read from input file
                0 // No offset
        );
    }

    static void load_root(Patricia& patricia)
    {
        TrieNode& root = patricia.root;
        root = *reinterpret_cast<TrieNode*>(patricia.mmap_pointer);
    }

    Patricia get_patricia_from_file(char* input_name)
    {
        Patricia patricia;

        int fd = open(input_name, O_RDONLY);
        if (fd == -1)
            std::cerr << "Cannot open " << input_name << '\n';
        else
        {
            load_patricia(patricia, fd);
            load_root(patricia);
        }
        return patricia;
    }

    Data* get_data_i(const Patricia& patricia, uint64_t data_offset, uint8_t child_nb)
    {
        return reinterpret_cast<Data*>(
                patricia.mmap_pointer + data_offset + sizeof(Data) * (size_t) child_nb
        );
    }

    char* get_chars(const Patricia& patricia, uint64_t chars_offset)
    {
        return patricia.mmap_pointer + chars_offset;
    }

    TrieNode* get_child(const Patricia& patricia, uint64_t next_node_offset)
    {
        return reinterpret_cast<TrieNode*>(
                patricia.mmap_pointer + next_node_offset
        );
    }


    /* DEBUG */
    static void patricia_print_dot_aux(const TrieNode* node,
                                       const Patricia& patricia, unsigned& nb)
    {
        unsigned i = nb;
        std::string color = end_of_word(node) ? "cyan" : "white";
        std::string label = node->frequency ? std::to_string(node->frequency) : "";
        std::cout << "    " << nb << " ["
                  << " label=\"" << label << "\""
                  << " fillcolor=\"" << color << "\""
                  << " style=filled"
                  << " ]\n";
        for (uint8_t child_i = 0; child_i < node->nb_children; ++child_i)
        {
            ++nb;
            const Data* data = get_data_i(patricia, node->data_offset, child_i);
            std::string link_str(get_chars(patricia, data->chars_offset), data->chars_size);

            std::cout << "    " << i << " -> " << nb
                      << " [label  = \"" << link_str << "\"]\n";
            auto child = get_child(patricia, data->next_node_offset);
            patricia_print_dot_aux(child, patricia, nb);
        }
    }

    [[maybe_unused]] void patricia_print(const Patricia& patricia)
    {
        std::cout << "digraph Trie {\n";
        std::cout << "    node [fontname=\"Arial\"];\n";

        const TrieNode* root = &patricia.root;
        unsigned i = 0;
        patricia_print_dot_aux(root, patricia, i);

        std::cout << "}\n";
    }
/* END DEBUG */
}
