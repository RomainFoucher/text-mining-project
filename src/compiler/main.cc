#include "trie.hh"
#include "parser.hh"

int main(int argc, char* argv[])
{
    if (argc != 3) return 1;

    trie::TrieNode* trie = get_trie_from_file(argv[1]);
    if (trie == nullptr) return 1;
    // Do something with it?
    //trie::trie_print(trie);
    //trie_merge(root)
    patricia::Patricia patricia_trie = trie::trie_merge(trie);
    trie::trie_destroy(trie);

    patricia::patricia_print(patricia_trie);

    patricia_write(patricia_trie, argv[2]);

    return 0;
}