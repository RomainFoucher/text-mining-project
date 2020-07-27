#pragma once


#include "patricia.hh"

#include <string>
#include <set>


struct json_data
{
    std::string word;
    int8_t distance;
    int32_t frequency;
};


struct custom_compare final
{
    bool operator() (const json_data& left, const json_data& right) const
    {
        if (left.distance < right.distance)
            return true;
        else if (left.distance > right.distance)
            return false;
        else
        {
            if (left.frequency > right.frequency)
                return true;
            else if (left.frequency < right.frequency)
                return false;
            else
                return left.word < right.word;
        }

    }
};



void print_json(const std::set<json_data, custom_compare>& res);
std::set<json_data, custom_compare> search(const Patricia& p, const std::string& word, uint8_t distance);

