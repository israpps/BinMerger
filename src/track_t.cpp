/***************************************************************
 * Name:      track_t.cpp
 * Purpose:   Class Implementation for track_t and blocksize parser
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include "track_t.h"

size_t get_BlockSize(std::string TRACK_TIPE)
{
    if (
        (TRACK_TIPE == "AUDIO")      ||
        (TRACK_TIPE == "MODE1/2352") ||
        (TRACK_TIPE == "MODE2/2352") ||
        (TRACK_TIPE == "CDI/2352"))
        return 2352;

    if (TRACK_TIPE == "CDG") return 2448;

    if (TRACK_TIPE == "MODE1/2048") return 2048;

    if (
        (TRACK_TIPE == "MODE2/2336") ||
        (TRACK_TIPE == "CDI/2336"))
        return 2336;
    return 2352;
}

track_t::track_t(std::string Track_type, int Num):
    num(Num), globalBlocksize(get_BlockSize(Track_type))
{
}

track_t::~track_t()
{
    //dtor
}
