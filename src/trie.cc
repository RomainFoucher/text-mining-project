#include "trie.hh"

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void insert(TrieNode *root, const std::string& word)
{
    TrieNode *current = root;
    for(const char& i : word)
    {
        char ch=i;
        TrieNode *node=current->children[ch];
        if(!node)
        {
            node=new TrieNode();
            current->children[i]=node;
        }
        current=node;
        current->prefixes++;
    }
    current->endofword=true;
}

bool search(const TrieNode* root,const std::string& word)
{
    const TrieNode* current = root;
    for(const char& ch : word)
    {
        auto node = current->children.at(ch);
        if (!node)
            return false;
        current = node;
    }
    return current->endofword;
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

void bst_print_dot_aux(const TrieNode* node, char cur_char, unsigned& nb)
{
    unsigned i = nb;
    std::cout << "    " << nb << " [label = \"" << cur_char << "\"]\n";
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
        bst_print_dot_aux(root, ' ', i);
    }

    std::cout <<  "}\n";
}

/* DEBUG END */
