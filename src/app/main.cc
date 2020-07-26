#include "patricia.hh"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 2) return 1;

    std::ofstream output_file(argv[1]);
    output_file << false;
    output_file.close();

    Patricia patricia = get_patricia_from_file(argv[1]);

    std::cout << patricia.root.end_of_word << std::endl;
    // input to json
    return 0;
}
