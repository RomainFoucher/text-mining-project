#include <iostream>
#include "patricia.hh"
#include "search.hh"

int main(int argc, char* argv[])
{
    if (argc != 2) return 1;

    Patricia patricia = get_patricia_from_file(argv[1]);
    patricia_print(patricia);

    auto res = search(patricia, "n936", 4);
    print_json(res);
    //std::cout << "test" << std::endl;
    // input to json
    return 0;
}
