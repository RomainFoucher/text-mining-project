#include "parser.hh"

using namespace std;
using namespace compiler;

static trie::TrieNode* get_trie_node_from_file(std::ifstream& input)
{
    string line;

    auto root = new trie::TrieNode;
    while (getline(input, line))
    {
        string word;
        string nb;
        int i = 0;
        char c = line[i];
        while ( c != ' ' && c != '\t')
        {
            word.push_back(c);
            c = line[++i];
        }
        while (c == ' ' || c == '\t') c = line[++i];
        while (c != '\0')
        {
            nb.push_back(c);
            c = line[++i];
        }
        //std::cout << line << '\t' << word << '\t' << nb << std::endl;
        uint32_t freq = std::stoul(nb);
        trie_insert(root, word, freq);
    }
    return root;
}

trie::TrieNode *compiler::get_trie_from_file(char* input_name)
{
    std::ifstream input_file(input_name);
    if (not input_file.is_open()) {
        std::cerr << "Cannot open " << input_name;
        return nullptr;
    }
    trie::TrieNode* root = get_trie_node_from_file(input_file);
    input_file.close();
    return root;
}


template<typename T>
static void write_(std::ofstream& output, T elm)
{
    // DEBUG std::cerr << sizeof(elm) << std::endl;
    output.write(reinterpret_cast<const char *>(&elm), sizeof(elm));
}

static void write_table(std::ofstream& output, const string& table)
{
    uint32_t table_size = (uint32_t) table.size() + 1;
    write_(output, table_size);
    output.write(table.c_str(), table_size);
}


static void write_node(std::ofstream& output, const patricia::TrieNode* node)
{
    write_(output, end_of_word(*node));
    write_(output, node->frequency);
    write_(output, (uint8_t) node->children.size());
    for (const auto&[c, data] : node->children)
    {
        write_(output, c);
        write_(output, data.index);
        write_(output, data.len);
        write_node(output, data.child);
    }
}

void compiler::patricia_write(const patricia::Patricia& trie, char* output_name)
{
    std::ofstream output_file(output_name, std::ofstream::out | std::ofstream::binary);
    if (not output_file.is_open()) {
        std::cerr << "Cannot open " << output_name << '\n';
        return;
    }
    write_table(output_file, trie.table);
    write_node(output_file, trie.root);
    output_file.close();
}
