/***************************************************************
 * Name:      track_t.h
 * Purpose:   Class definition for track_t and blocksize parser
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef TRACK_T_H
#define TRACK_T_H
//#include "common.h"
#include <string>
#include <vector>
class track_t
{
    public:
        track_t(std::string Track_type, int Num);

        virtual ~track_t();

    protected:

    private:
        int num;
        std::vector<int> indexes;
        size_t file_offset;
        size_t sectors;
        size_t globalBlocksize;
};

#endif // TRACK_T_H
