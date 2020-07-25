#include "trie.hh"
#include "parser.hh"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 3) return 1;

    auto input_name = argv[1];
    std::ifstream input_file(input_name);
    if (not input_file.is_open()) {
        std::cerr << "Cannot open " << input_name;
        return 1;
    }

    auto trie = get_trie_from_file(input_file);
    input_file.close();
    // Do something with it?
    print_trie(trie);

    destroy(trie);

    auto output_name = argv[2];
    std::ofstream output_file(output_name);
    if (not output_file.is_open()) {
        std::cerr << "Cannot open " << output_name;
        return 1;
    }
    //write_trie(trie, output_file);
    output_file.close();
    return 0;
}