#include "search.hh"
#include "patricia/patricia.hh"

#include <vector>
#include <algorithm>
#include <iostream>


using namespace common;

namespace app
{

    static uint8_t* fill_row(uint8_t len, uint8_t* tab)
    {
        for (uint8_t i = 0; i < len + 1; i++)
        {
            tab[i] = i;
        }
        return tab;
    }

    uint8_t smallest(uint8_t x, uint8_t y, uint8_t z){
        return x < y ? (x < z ? x : z) : (y < z ? y : z);
    }


    static void
    recursive_search(const Patricia& p, const TrieNode* node, const std::string& prefix, char ch, char prev_ch,
                     const std::string& word, const uint8_t* prev_row, const uint8_t* pre_prev_row,
                     std::set<json_data, custom_compare>& results, uint8_t distance, uint8_t len, char* str)
    {
        // Init
        uint8_t columns = word.size() + 1;
        uint8_t current_row[256];
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
            current_row[col] = smallest(insert_val, delete_val, replace_val);

            // swap
            if (prev_ch != 0
                    && col - 1 > 0
                    && ch == word[col - 2]
                    && prev_ch == word[col - 1]
                    && word[col - 1] != ch)
            {
                current_row[col] = std::min<uint8_t>(current_row[col], pre_prev_row[col - 2] + 1);
            }
        }

        // Fill results
        uint8_t act_distance;
        if (end_of_word(node)
                && len == 1
                && (act_distance = current_row[word.size()]) <= distance)
        {
            json_data ret;
            ret.word = prefix;
            ret.frequency = node->frequency;
            ret.distance = act_distance;
            results.insert(ret);
        }

        // Call recursively
        if (*std::min_element(current_row, current_row + word.size() + 1) <= distance)
        {
            if (len > 1)
            {
                char new_ch = str[1];
                recursive_search(p, node, prefix + new_ch, new_ch, ch, word, current_row, prev_row, results,
                                 distance, len - 1, str + 1);
            }
            else
            {
                for (uint8_t i = 0; i < node->nb_children; i++)
                {
                    auto* dt = get_data_i(p, node->data_offset, i);
                    auto* chrs = get_chars(p, dt->chars_offset);
                    char new_ch = chrs[0];
                    const TrieNode* new_nd = get_child(p, dt->next_node_offset);
                    uint8_t new_len = dt->chars_size;
                    recursive_search(p, new_nd, prefix + new_ch, new_ch, ch, word, current_row, prev_row, results,
                            distance, new_len, chrs);

                }
            }
        }
    }


    std::set<json_data, custom_compare> search(const Patricia& p, const std::string& word, uint8_t distance)
    {
        std::set<json_data, custom_compare> results;

        uint8_t current_row[256];
        fill_row(word.size(), current_row);
        uint8_t prev_row[256];
        for (uint8_t i = 0; i < p.root.nb_children; i++)
        {
            auto* dt = get_data_i(p, p.root.data_offset, i);
            auto* chrs = get_chars(p, dt->chars_offset);
            const TrieNode* node = get_child(p, dt->next_node_offset);
            char ch = chrs[0];
            std::string prefix(1, ch);
            uint8_t new_len = dt->chars_size;
            recursive_search(p, node, prefix, ch, 0, word, current_row, prev_row, results, distance, new_len, chrs);
        }
        return results;
    }


    void print_json(const std::set<json_data, custom_compare>& res)
    {
        std::cout << "[";
        if (!res.empty())
        {
            auto it = res.begin();
            std::cout << "{";
            std::cout << R"("word":")" << (*it).word << "\",";
            std::cout << "\"freq\":" << (*it).frequency << ",";
            std::cout << "\"distance\":" << (int) (*it).distance << "";
            std::cout << "}";
            it++;
            for (; it != res.end(); ++it)
            {
                std::cout << ",{";
                std::cout << R"("word":")" << (*it).word << "\",";
                std::cout << "\"freq\":" << (*it).frequency << ",";
                std::cout << "\"distance\":" << (int) (*it).distance << "";
                std::cout << "}";

            }
        }
        std::cout << "]\n";
    }
}
