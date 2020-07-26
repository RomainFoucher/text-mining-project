#pragma once


#include <string>
#include <set>
#include "patricia.hh"


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
        if (left.frequency > right.frequency)
            return true;
        return left.word < right.word;
    }
};




std::set<json_data, custom_compare> search(const Patricia& p, const std::string& word, int8_t distance);

