/***************************************************************
 * Name:      structs.h
 * Purpose:   Struct Declaration for index_t and bin_t algong with some utilities
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <sstream>
#include <string>
#include <vector>

#include "track_t.h"

struct index_t
{
    int number;
    std::string number_as_string;
    int minutes;
    int secconds;
    int fields;
    size_t file_offset;
};

struct bin_t
{
    std::string path;
    std::vector <index_t> index;
    std::string track;
    size_t size;
};
index_t populate_index(std::string regex_match_);

#endif // STRUCTS_H_INCLUDED
