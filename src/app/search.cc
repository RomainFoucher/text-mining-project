#include "search.hh"
#include "patricia.hh"

#include <vector>


std::vector<int8_t > make_row(int8_t len)
{
    auto vec = std::vector<int8_t >();
    for (int8_t i = 0; i < len + 1; i++)
    {
        vec.emplace_back(i);
    }
    return vec;
}


std::set<json_data, custom_compare> search(const Patricia& p, const std::string& word, int8_t distance)
{
    std::set<json_data, custom_compare> results;

    auto current_row = make_row(word.size());

    for (int8_t i = 0; i < p.root.nb_children; i++)

    return results;
}

