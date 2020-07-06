#include "trie.hh"

int main(void)
{
    TrieNode *root=new TrieNode();
    insert(root,"harshita");
    insert(root,"harsh");
    insert(root,"sharma");
    insert(root,"harry");
    destroy(root);
    return 0;
}