#pragma once


#include "patricia/patricia.hh"

namespace app
{
    /*!
     * Read from standard input lines with approx format.
     * Print on standard output json format of the query.
     *
     * @param patricia the patricia to search into
     */
    void read_inputs_to_json(const common::Patricia& patricia);
}