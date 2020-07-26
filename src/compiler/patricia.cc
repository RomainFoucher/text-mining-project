#include "patricia.hh"

#include <iostream>


namespace patricia
{
    std::string get_string_from_table(const std::string& table,
                                       uint64_t index, uint64_t len)
    {
        return table.substr(index, len);
    }

    void trie_node_delete(TrieNode *root)
    {
        for (const auto &i : root->children) {
            trie_node_delete(i.second.child);
        }
        delete (root);
    }


/* DEBUG */
    static void patricia_print_dot_aux(const TrieNode *node, const std::string& table,
            const std::string& cur_str, unsigned &nb)
    {
        unsigned i = nb;
        std::string color = node->end_of_word ? "cyan" : "white";
        std::cout << "    " << nb << " ["
                  << " label=\"" << cur_str << "\""
                  << " fillcolor=\"" << color << "\""
                  << " style=filled"
                  << " ]\n";
        for (const auto&[c, data] : node->children)
        {
            ++nb;
            std::string link_str { c };
            auto node_str = get_string_from_table(table, data.index, data.len);
            std::cout << "    " << i << " -> " << nb
                      << " [label  = \"" << link_str <<"\"]\n";
            patricia_print_dot_aux(data.child, table, node_str, nb);
        }
    }

    void patricia_print(const Patricia& patricia)
    {
        std::cout << "digraph Trie {\n";
        std::cout << "    node [fontname=\"Arial\"];\n";

        const TrieNode* root = patricia.root;
        if (!root)
            std::cout << "\n";
        else
        {
            unsigned i = 0;
            patricia_print_dot_aux(root, patricia.table, "", i);
        }

        std::cout << "}\n";
    }
    Patricia::Patricia()
    {
        root = new TrieNode();
    }
}
