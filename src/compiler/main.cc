#include "trie.hh"
#include "parser.hh"

int main(int argc, char* argv[])
{
    if (argc != 3) return 1;

    std::cerr << "Generate Trie :" << std::endl;

    trie::TrieNode* trie = get_trie_from_file(argv[1]);
    if (trie == nullptr) return 1;

    //trie::trie_print(trie);

    std::cerr << "Generate Patricia :" << std::endl;

    patricia::Patricia patricia_trie = trie::trie_merge(trie);
    trie::trie_destroy(trie);

    patricia::patricia_print(patricia_trie);
    std::cerr << "table: " << patricia_trie.table << std::endl;

    std::cerr << "Write Patricia :" << std::endl;

    patricia_write(patricia_trie, argv[2]);

    return 0;
}