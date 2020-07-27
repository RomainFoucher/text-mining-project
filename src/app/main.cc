#include "patricia.hh"
#include "parser.hh"

int main(int argc, char* argv[])
{
    if (argc != 2) return 1;

    Patricia patricia = get_patricia_from_file(argv[1]);
    // patricia_print(patricia); // DEBUG
    read_inputs_to_json(patricia);
    return 0;
}
