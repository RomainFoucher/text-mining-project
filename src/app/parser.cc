#include <string>
#include <iostream>
#include <tuple>
#include <sstream>
#include "parser.hh"
#include "search.hh"


static void read_input_to_json(const Patricia& patricia, const std::string& word, uint8_t distance)
{
    print_json(search(patricia, word, distance));
}


// empty string = nothing
static std::tuple<uint8_t, std::string> parse_input_string(const std::string& str)
{
    std::string mode;
    std::string dist;
    std::string word;
    int d = 0;
    std::istringstream iss(str);

    iss >> mode;
    if (mode != "approx") return std::make_tuple(0, "");

    iss >> dist;
    try {
        d = std::stoi(dist);
        if (d < 0)
            d = 0;
    }
    catch (...) {
        return std::make_tuple(0, "");
    }

    iss >> word;
    return std::make_tuple(d, word);
}

void read_inputs_to_json(const Patricia& patricia)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        const auto& [distance, word] = parse_input_string(line);
        if (word.empty()) continue;

        read_input_to_json(patricia, word, distance);
    }
}