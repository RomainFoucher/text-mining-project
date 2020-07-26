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
        trie_insert(root, word);
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

static void write_node(const patricia::TrieNode* node, std::ofstream& output)
{
    output << node->end_of_word;
    output << node->children.size();
    for (const auto&[c, data] : node->children)
    {
        output << c;
        output << data.index;
        output << data.len;
        write_node(data.child, output);
    }
}

void patricia_write(const patricia::Patricia* trie, char* output_name)
{
    std::ofstream output_file(output_name);
    if (not output_file.is_open()) {
        std::cerr << "Cannot open " << output_name;
        return;
    }
    write_node(trie->root, output_file);
    output_file.close();
}
