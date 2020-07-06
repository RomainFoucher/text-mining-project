#include "parser.hh"

struct TrieNode *get_trie_from_file(std::ifstream)
{
    auto root = new TrieNode;
    insert(root,"harshita");
    insert(root,"harsh");
    insert(root,"sharma");
    insert(root,"harry");
    destroy(root);

    return root;
}
