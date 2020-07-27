#include "search.hh"
#include "patricia.hh"

#include <vector>
#include <algorithm>
#include <iostream>


std::vector<uint8_t > make_row(uint8_t len)
{
    auto vec = std::vector<uint8_t >();
    for (uint8_t i = 0; i < len + 1; i++)
    {
        vec.emplace_back(i);
    }
    return vec;
}


void recursive_search(const Patricia& p, const TrieNode& node, const std::string prefix, char ch, char prev_ch, const std::string& word,
        const std::vector<uint8_t >& prev_row, const std::vector<uint8_t>& pre_prev_row,
        std::set<json_data, custom_compare>& results, uint8_t distance, uint8_t len, char* str)
{
    //std::cout << prefix << std::endl;
    // Init
    uint8_t columns = word.size() + 1;
    auto current_row = std::vector<uint8_t>(word.size() + 1, 0);
    current_row[0] = prev_row[0] + 1;

    // Fill current_row
    for (uint8_t col = 1; col < columns; col++)
    {
        uint8_t insert_val = prev_row[col] + 1;
        uint8_t delete_val = current_row[col - 1] + 1;
        uint8_t replace_val;
        if (word[col - 1] != ch)
            replace_val = prev_row[col - 1] + 1;
        else
            replace_val = prev_row[col - 1];
        current_row[col] = std::min({insert_val, delete_val, replace_val});

        // swap
        if (prev_ch != 0 && col - 1 > 0 && ch == word[col - 2] && prev_ch == word[col - 1] && word[col - 1] != ch)
        {
            current_row[col] = std::min<uint8_t>(current_row[col], pre_prev_row[col - 2] + 1);
        }
    }

    // Fill results
    uint8_t act_distance;
    if (node.end_of_word && (act_distance = current_row[current_row.size() - 1]) <= distance)
    {
        json_data ret;
        ret.word = prefix;
        ret.frequency = node.frequency;
        ret.distance = act_distance;
        results.insert(ret);
    }

    // Call recursively
    if (*std::min_element(current_row.begin(), current_row.end()) <= distance)
    {
        if (len != 0)
        {
            char new_ch = str[0];
            recursive_search(p, node, prefix + new_ch, new_ch, ch, word, current_row, prev_row, results,
                             distance, len - 1,
                             str + 1);
        }
        else
        {
            for (uint8_t i = 0; i < node.nb_children; i++)
            {

                char new_ch = node.children[i].next_char;
                const TrieNode &new_nd = node.children[i].child;
                uint8_t new_len = node.children[i].len;
                if (new_len == 0)
                {
                    recursive_search(p, new_nd, prefix + new_ch, new_ch, ch, word, current_row, prev_row, results,
                            distance, 0,
                            nullptr);
                }
                else
                {
                    char *new_str = get_chars_from_table(p, node.children[i].index);
                    recursive_search(p, new_nd, prefix + new_ch, new_ch, ch, word, current_row, prev_row, results,
                            distance, new_len, new_str);
                }
            }
        }
    }
}


std::set<json_data, custom_compare> search(const Patricia& p, const std::string& word, uint8_t distance)
{
    std::set<json_data, custom_compare> results;
    auto current_row = make_row(word.size());
    auto prev_row = std::vector<uint8_t>();
    for (uint8_t i = 0; i < p.root.nb_children; i++)
    {
        char ch = p.root.children[i].next_char;
        const TrieNode& node = p.root.children[i].child;
        std::string prefix(1, ch);
        uint8_t new_len = p.root.children[i].len;
        //std::cout << p.root.children[i].next_char << std::endl;
        //std::cout << (int)new_len << std::endl;
        if (new_len == 0)
        {
            recursive_search(p, node, prefix, ch, 0, word, current_row, prev_row, results, distance, 0, nullptr);
        }
        else
        {
            char* new_str = get_chars_from_table(p, p.root.children[i].index);
            recursive_search(p, node, prefix, ch, 0, word, current_row, prev_row, results, distance, new_len, new_str);
        }
        //std::cout << "end rec" << std::endl;
    }
    return results;
}


void print_json(const std::set<json_data, custom_compare>& res)
{
    std::cout << "[";
    auto it = res.begin();
    std::cout << "{";
    std::cout << "\"word\":\"" << (*it).word << "\",";
    std::cout << "\"freq\":\"" << (int)(*it).distance << "\",";
    std::cout << "\"distance\":\"" << (*it).frequency << "\"";
    std::cout << "}";
    it++;
    for (; it != res.end(); ++it)
    {
        std::cout << ",{";
        std::cout << "\"word\":\"" << (*it).word << "\",";
        std::cout << "\"freq\":\"" << (int)(*it).distance << "\",";
        std::cout << "\"distance\":\"" << (*it).frequency << "\"";
        std::cout << "}";

    }
    std::cout << "]";
}
