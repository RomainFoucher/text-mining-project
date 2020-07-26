#include "patricia.hh"

#include <fstream>
#include <iostream>


using namespace std;

void trie_node_clean(TrieNode root)
{
    for (size_t i = 0; i < root.nb_children; ++i)
        trie_node_clean(root.children[i].child);
    delete[] root.children;
}

static void store_node(std::ifstream& input, TrieNode* root)
{
    input >> root->end_of_word;
    input >> root->nb_children;
    root->children = new struct Data[root->nb_children];

    for (size_t i = 0; i < root->nb_children; ++i)
    {
        Data* data = &root->children[i];
        input >> data->next_char;
        input >> data->index;
        input >> data->len;
        store_node(input, &data->child);
    }
}


Patricia get_patricia_from_file(char* input_name)
{
    Patricia patricia;

    std::ifstream input_file(input_name);
    if (not input_file.is_open())
        std::cerr << "Cannot open " << input_name;
    else
    {
        store_node(input_file, &patricia.root);
        // TODO
        // get table
        input_file.close();
    }
    return patricia;
}