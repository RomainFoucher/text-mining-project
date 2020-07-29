#include <patricia/patricia.hh>
#include "parser.hh"

using namespace std;

namespace compiler
{
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
            while (c != ' ' && c != '\t')
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

    trie::TrieNode* get_trie_from_file(char* input_name)
    {
        std::ifstream input_file(input_name);
        if (not input_file.is_open())
        {
            std::cerr << "Cannot open " << input_name;
            return nullptr;
        }
        trie::TrieNode* root = get_trie_node_from_file(input_file);
        input_file.close();
        return root;
    }


    template<typename T>
    static void write_(std::ofstream& output, const T& elm)
    {
        output.write(reinterpret_cast<const char*>(&elm), sizeof(elm));
    }

    static void write_node(std::ofstream& output, const patricia::TrieNode* node,
                           uint64_t& data_offset)
    {
        write_(output, data_offset);
        write_(output, node->frequency);
        uint8_t nb_children = node->children.size();
        write_(output, nb_children);
        // Padding bits
        write_(output, (uint16_t) 0);
        write_(output, (uint8_t) 0);

        // Children
        data_offset += sizeof(common::Data) * nb_children;
        for (const auto&[c, data] : node->children)
        {
            write_node(output, data.child, data_offset);
        }
    }

    static void write_data(std::ofstream& output,
            const patricia::TrieNode* node, uint64_t& chars_offset)
    {
        for (const auto&[c, data] : node->children)
        {
            uint8_t cur_chars_len = data.len + 1;

            //std::cerr << "child " << data.child->id << std::endl; // DEBUG
            uint64_t node_offset = sizeof(common::TrieNode) * data.child->id;
            write_(output, node_offset);

            write_(output, chars_offset);
            chars_offset += cur_chars_len;

            write_(output, cur_chars_len);

            // Padding bits
            write_(output, (uint8_t) 0);
            write_(output, (uint16_t) 0);
            write_(output, (uint32_t) 0);
        }

        for (const auto&[c, data] : node->children)
            write_data(output, data.child, chars_offset);
    }

    static void write_table(std::ofstream& output, const patricia::Patricia& patricia,
            const patricia::TrieNode& node)
    {
        for (const auto& [c, data] : node.children)
        {
            write_(output, (char) c);
            output.write(
                    patricia::get_string_from_table(patricia.table, data.index, data.len).c_str(),
                    data.len
            );
        }

        for (const auto&[c, data] : node.children)
            write_table(output, patricia, *data.child);
    }

    void patricia_write(char* output_name, const patricia::Patricia& patricia, uint32_t nb_node)
    {
        std::ofstream output_file(output_name, std::ofstream::out | std::ofstream::binary);
        if (not output_file.is_open())
        {
            std::cerr << "Cannot open " << output_name << '\n';
            return;
        }
        uint32_t nb_total_children = nb_node - 1;
        //std::cerr << nb_node << std::endl; // DEBUG
        //std::cerr <<  sizeof(common::Data) << std::endl; // DEBUG
        //std::cerr <<  sizeof(common::TrieNode) << std::endl; // DEBUG

        uint64_t data_offset = sizeof(common::TrieNode) * nb_node;
        uint64_t chars_offset = data_offset + sizeof(common::Data) * nb_total_children;

        //std::cerr << "tell\n"; // DEBUG
        //std::cerr << output_file.tellp() << std::endl; // DEBUG
        uint64_t data_offset_tmp = data_offset;
        write_node(output_file, patricia.root, data_offset_tmp);

        //std::cerr << "tell\n"; // DEBUG
        //std::cerr << data_offset << std::endl; // DEBUG
        //std::cerr << output_file.tellp() << std::endl; // DEBUG

        uint64_t chars_offset_tmp = chars_offset;
        write_data(output_file, patricia.root, chars_offset_tmp);

        //std::cerr << "tell\n"; // DEBUG
        //std::cerr << chars_offset << std::endl; // DEBUG
        //std::cerr << output_file.tellp() << std::endl; //DEBUG

        write_table(output_file, patricia, *patricia.root);

        output_file.close();
    }
}
