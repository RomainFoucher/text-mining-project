#pragma once


#include "patricia/patricia.hh"

#include <string>
#include <set>


namespace app
{
    /*!
     * A queried data.
     */
    struct json_data
    {
        std::string word;
        int8_t distance;
        int32_t frequency;
    };

    /*!
     * Functor used to compare two json_data.
     */
    struct custom_compare final
    {
        /*!
         * Compare two json_data.
         * Order: distance(minimum) > frequency(maximum) > lexicographic(minimum)
         *
         * @param left first json_data.
         * @param right second json_data.
         * @return if left is higher than right in priority.
         */
        bool operator()(const json_data& left, const json_data& right) const
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

    /*!
     * Print all json_data in json format.
     *
     * @param res the collection of json_data.
     */
    void print_json(const std::set<json_data, custom_compare>& res);

    /*!
     * Search in a patricia all words close by a distance to a given word.
     *
     * @param p the patricia to search into.
     * @param word to word to approximate.
     * @param distance maximum number of modifications (add, delete, replace and swap)
     * @return the collection of json_data.
     */
    std::set<json_data, custom_compare> search(const common::Patricia& p, const std::string& word, uint8_t distance);
}
