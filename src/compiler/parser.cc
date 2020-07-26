#include "parser.hh"

using namespace std;

static trie::TrieNode *get_trie_node_from_file(std::ifstream& input)
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

trie::TrieNode *get_trie_from_file(char* input_name)
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


static void write_table(std::ofstream& output, const string& table)
{
    output << table.c_str();
}

template<typename T>
static void write_(std::ofstream& output, T elm)
{
    // DEBUG std::cerr << sizeof(elm) << std::endl;
    output.write(reinterpret_cast<const char *>(&elm), sizeof(elm));
}

static void write_node(std::ofstream& output, const patricia::TrieNode* node)
{
    write_(output, node->end_of_word);
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

void patricia_write(const patricia::Patricia& trie, char* output_name)
{
    std::ofstream output_file(output_name, std::ofstream::out | std::ofstream::binary);
    if (not output_file.is_open()) {
        std::cerr << "Cannot open " << output_name;
        return;
    }
    write_node(output_file, trie.root);
    write_table(output_file, trie.table);
    output_file.close();
}
