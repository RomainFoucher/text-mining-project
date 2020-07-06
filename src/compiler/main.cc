#include "trie.hh"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 3) return 1;

    std::ifstream input_file;
    input_file.open(argv[1]);
    //auto trie = get_trie_from_file(input_file);
    input_file.close();

    std::ofstream output_file;
    output_file.open(argv[2]);
    //auto trie = write_trie(output_file);
    output_file.close();
    return 0;
}