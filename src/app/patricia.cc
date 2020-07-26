#include "patricia.hh"

#include <fstream>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>


using namespace std;

void trie_node_clean(TrieNode& root)
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
    patricia.table = (char *) mmap(
            nullptr, // No address to start with
            patricia.table_size, // Size is table_size + 1
            PROT_READ, // Read only
            0, // No flag
            fd, // Read from input file
            sizeof(patricia.table_size) // Skip size bytes
            // 0
    );
    patricia.fd = fd;
}

static void store_table_input(std::ifstream& input, Patricia& patricia)
{
    patricia.table = new char[patricia.table_size];
    input.read(patricia.table, patricia.table_size);
    std::cout << patricia.table << std::endl;
}


Patricia get_patricia_from_file(char* input_name)
{
    Patricia patricia;

    std::ifstream input(input_name, std::ifstream::binary | std::ifstream::in);
    if (not input.is_open())
        std::cerr << "Cannot open " << input_name << '\n';
    else
    {
        store_table_size(input, patricia.table_size);
        std::cout << "table size: " << patricia.table_size << std::endl;
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

std::string get_string_from_table(const std::string& table,
                                  uint32_t index, uint8_t len)
{
    return table.substr(index, len);
}

/* DEBUG */
static void patricia_print_dot_aux(const TrieNode& node,
                                   const std::string& table, unsigned &nb)
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
        auto node_str = get_string_from_table(table, data.index, data.len);
        std::cout << "    " << i << " -> " << nb
                  << " [label  = \"" << link_str << node_str <<"\"]\n";
        patricia_print_dot_aux(data.child, table, nb);
    }
}

void patricia_print(const Patricia& patricia)
{
    std::cout << "digraph Trie {\n";
    std::cout << "    node [fontname=\"Arial\"];\n";

    const TrieNode& root = patricia.root;
    unsigned i = 0;
    patricia_print_dot_aux(root, patricia.table, i);

    std::cout << "}\n";
}
/* END DEBUG */
