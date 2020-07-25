#include "patricia.hh"


namespace patricia
{
    void trie_node_delete(TrieNode *root)
    {
        for (const auto &i : root->children) {
            trie_node_delete(i.second.child);
        }
        delete (root);
    }
}
