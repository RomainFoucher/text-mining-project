#include "trie.hh"
#include "parser.hh"


using namespace compiler;

int main(int argc, char* argv[])
{
    if (argc != 3) return 1;

    std::cerr << "Generate Trie :" << std::endl;
    trie::TrieNode* trie = get_trie_from_file(argv[1]);
    if (trie == nullptr) return 1;
    //trie::trie_print(trie); // DEBUG

    std::cerr << "Generate Patricia :" << std::endl;
    uint32_t nb_node = 0;
    patricia::Patricia patricia_trie = trie::trie_merge(trie, nb_node);
    trie::trie_destroy(trie);

    //patricia::patricia_print(patricia_trie); // DEBUG
    //std::cerr << "table: " << patricia_trie.table << std::endl; // DEBUG

    std::cerr << "Write Patricia :" << std::endl;
    patricia_write(argv[2], patricia_trie, nb_node);

    return 0;
}