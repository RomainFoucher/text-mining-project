#include "patricia.hh"

#include <fstream>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>


using namespace std;
using namespace app;

void app::trie_node_clean(TrieNode& root)
{
    for (size_t i = 0; i < root.nb_children; ++i)
        trie_node_clean(root.children[i].child);
    delete[] root.children;
}


template<typename T>
static void read_(std::ifstream& input, T& elm)
{
    input.read((char *)&elm, sizeof(elm));
}

static void store_node(std::ifstream& input, TrieNode& root)
{
    read_(input, root.end_of_word);
    read_(input, root.frequency);
    read_(input, root.nb_children);
    root.children = new struct Data[root.nb_children];

    for (uint8_t i = 0; i < root.nb_children; ++i)
    {
        Data& data = root.children[i];
        read_(input, data.next_char);
        read_(input, data.index);
        read_(input, data.len);
        store_node(input, data.child);
    }
}

static void store_table_size(std::ifstream& input, uint32_t& table_size)
{
    read_(input, table_size);
}

static void skip_table(std::ifstream& input, uint32_t table_size)
{
    input.ignore(table_size);
}

static void store_table(int fd, Patricia& patricia)
{
    size_t mmap_size = patricia.table_size + Patricia::size_of_table_size;
    auto mmap_pointer = (char *) mmap(
            nullptr, // No address to start with
            mmap_size, // Size is table_size + 1
            PROT_READ, // Read only
            MAP_PRIVATE, // No flag
            fd, // Read from input file
            // FIXME Seems like you cannot do it?
            //sizeof(patricia.table_size) // Skip size bytes
            // Instead just take offset 0
            0
    );
    patricia.fd = fd;
    patricia.mmap_pointer = mmap_pointer;
    patricia.mmap_size = mmap_size;
    patricia.table = mmap_pointer + Patricia::size_of_table_size;

}

[[maybe_unused]] static void store_table_input(std::ifstream& input, Patricia& patricia)
{
    patricia.table = new char[patricia.table_size];
    input.read(patricia.table, patricia.table_size);
}


Patricia app::get_patricia_from_file(char* input_name)
{
    Patricia patricia;

    std::ifstream input(input_name, std::ifstream::binary | std::ifstream::in);
    if (not input.is_open())
        std::cerr << "Cannot open " << input_name << '\n';
    else
    {
        store_table_size(input, patricia.table_size);
        //std::cerr << "table size: " << patricia.table_size << std::endl; // DEBUG
        skip_table(input, patricia.table_size);
        store_node(input, patricia.root);

        input.close();

        int fd = open(input_name, O_RDONLY);
        if (fd == -1)
            std::cerr << "Cannot open " << input_name << '\n';
        else
            store_table(fd, patricia);
    }
    return patricia;
}

static char get_char_from_table(const Patricia& patricia, uint32_t index)
{
    // std::cerr << patricia.table[index] << std::endl; DEBUG
    return patricia.table[index];
}

std::string app::get_string_from_table(const Patricia& patricia, uint32_t index, uint8_t len)
{
    std::string str;
    for (uint8_t i = 0; i < len; ++i)
        str.push_back(get_char_from_table(patricia, index + i));
    return str;
}

char* app::get_chars_from_table(const Patricia& patricia, uint32_t index)
{
    return patricia.table + index;
}

/* DEBUG */
static void patricia_print_dot_aux(const TrieNode& node,
                                   const Patricia& patricia, unsigned &nb)
{
    unsigned i = nb;
    std::string color = node.end_of_word ? "cyan" : "white";
    std::string label = node.frequency ? std::to_string(node.frequency) : "";
    std::cout << "    " << nb << " ["
              << " label=\"" << label << "\""
              << " fillcolor=\"" << color << "\""
              << " style=filled"
              << " ]\n";
    for (uint8_t child_i = 0; child_i < node.nb_children; ++child_i)
    {
        const Data& data = node.children[child_i];
        ++nb;
        std::string link_str { data.next_char };
        auto node_str = get_string_from_table(patricia, data.index, data.len);
        std::cout << "    " << i << " -> " << nb
                  << " [label  = \"" << link_str << node_str <<"\"]\n";
        patricia_print_dot_aux(data.child, patricia, nb);
    }
}

void patricia_print(const Patricia& patricia)
{
    std::cout << "digraph Trie {\n";
    std::cout << "    node [fontname=\"Arial\"];\n";

    const TrieNode& root = patricia.root;
    unsigned i = 0;
    patricia_print_dot_aux(root, patricia, i);

    std::cout << "}\n";
}
/* END DEBUG */
