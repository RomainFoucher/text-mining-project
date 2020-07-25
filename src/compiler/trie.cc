#include "trie.hh"

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void insert(TrieNode *root, const std::string& word)
{
    TrieNode* current = root;
    for(const char& ch : word)
    {
        std::string str = {ch};
        TrieNode* node = current->children[str];
        if(!node)
        {
            node=new TrieNode();
            current->children[str] = node;
        }
        current=node;
    }
    current->end_of_word=true;
}

bool search(const TrieNode* root,const std::string& word)
{
    const TrieNode* current = root;
    for(const char& ch : word)
    {
        std::string str = {ch};
        auto node = current->children.at(str);
        if (!node)
            return false;
        current = node;
    }
    return current->end_of_word;
}

void destroy(struct TrieNode* root)
{
    for(const auto& i : root->children)
    {
        destroy(i.second);
    }
    delete(root);
}

/* DEBUG */

void bst_print_dot_aux(const TrieNode* node, std::string cur_str, unsigned& nb)
{
    unsigned i = nb;
    std::cout << "    " << nb << " [label = \"" << cur_str << "\"]\n";
    for (const auto& [c, child] : node->children)
    {
        ++nb;
        std::cout << "    " << i << " -> " << nb << "\n";
        bst_print_dot_aux(child, c, nb);
    }
}

void print_trie(const TrieNode *root) {
    std::cout << "digraph Trie {\n";
    std::cout << "    node [fontname=\"Arial\"];\n";

    if (!root)
        std::cout << "\n";
    else
    {
        unsigned i = 0;
        bst_print_dot_aux(root, "", i);
    }

    std::cout <<  "}\n";
}

/* DEBUG END */
