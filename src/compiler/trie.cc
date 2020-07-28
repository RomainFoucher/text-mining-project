#include "trie.hh"

#include <iostream>


namespace compiler::trie {

    std::pair<uint64_t , uint64_t> find_table_position(const std::string& str, std::string& table)
    {
        if (str.empty())
        {
            return {0, 0};
        }
        /*std::size_t pos = table.find(str);
        if (pos != std::string::npos)
        {
            return {pos, str.size()};
        }
        else*/
        {
            table.append(str);
            return {table.size() - str.size(), str.size()};
        }
    }

    trie::TrieNode* rec_merge_single_node(trie::TrieNode* node, std::string& str) // return a multi node
    {
        if (node->end_of_word)
        {
            return node;
        }
        else if (node->children.size() == 1)
        {
            str.append(node->children.begin()->first);
            return rec_merge_single_node(node->children.begin()->second, str);
        }
        else
        {
            return node;
        }
    }

    void rec_merge_multi_nodes(trie::TrieNode *node, patricia::TrieNode *p, std::string& table, uint32_t & nb_node)
    {
        p->end_of_word = node->end_of_word;
        p->frequency = node->frequency;
        nb_node += node->children.size();
        for (const auto &i : node->children)
        {

            // Create new patricia node
            auto* nw_node = new patricia::TrieNode();
            std::string value({i.first[0]});

            // Merge single node
            auto next_node = rec_merge_single_node(i.second, value);

            // Put value in table and return position
            auto pos_table = find_table_position(value.substr(1, value.size() - 1), table);

            // Create new data struct
            patricia::Data nw_dt{};
            nw_dt.index = pos_table.first;
            nw_dt.len = pos_table.second;
            nw_dt.child = nw_node;

            // Add new data struct to node
            p->children[value[0]] = nw_dt;

            // Call recursively
            rec_merge_multi_nodes(next_node, nw_node, table, nb_node);
        }
    }


    patricia::Patricia trie_merge(TrieNode* root, uint32_t& nb_node)
    {
        patricia::Patricia p = patricia::Patricia();
        rec_merge_multi_nodes(root, p.root, p.table, nb_node);
        return p;
    }


    void trie_insert(TrieNode *root, const std::string &word, uint32_t freq)
    {
        TrieNode *current = root;
        for (const char &ch : word)
        {
            std::string str = {ch};
            TrieNode *node = current->children[str];
            if (!node)
            {
                node = new TrieNode();
                current->children[str] = node;
            }
            current = node;
        }
        current->end_of_word = true;
        current->frequency = freq;
    }

    void trie_destroy(struct TrieNode *root)
    {
        for (const auto &i : root->children)
        {
            trie::trie_destroy(i.second);
        }
        delete (root);
    }

/* DEBUG */
    static void trie_print_dot_aux(const TrieNode *node, unsigned &nb)
    {
        unsigned i = nb;
        std::string color = node->end_of_word ? "cyan" : "white";
        std::string label = node->frequency ? std::to_string(node->frequency) : "";

        std::cout << "    " << nb << " ["
                  << " label=\"" << label << "\""
                  << " fillcolor=\"" << color << "\""
                  << " style=filled"
                  << " ]\n";
        for (const auto&[c, child] : node->children)
        {
            ++nb;
            std::string link_str { c };
            std::cout << "    " << i << " -> " << nb
                      << " [label  = \"" << link_str <<"\"]\n";
            trie_print_dot_aux(child, nb);
        }
    }

    void trie_print(const TrieNode *root)
    {
        std::cout << "digraph Trie {\n";
        std::cout << "    node [fontname=\"Arial\"];\n";

        if (!root)
            std::cout << "\n";
        else
        {
            unsigned i = 0;
            trie_print_dot_aux(root, i);
        }

        std::cout << "}\n";
    }
/* DEBUG END */
}