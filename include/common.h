/***************************************************************
 * Name:      common.h
 * Purpose:   Class definition for general utilities
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   MIT License
 **************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <sstream>
#include "common/structs.h"

class common
{
public:
    common();
    virtual ~common();
    std::string sectors_to_cuestamp (int sectors);
    int cuestamp_to_sectors (std::string stamp);
    size_t GetFileSize(std::string filename);
    int cuestamp_to_sectors (index_t INDEX);

protected:

private:
};

#endif // COMMON_H
