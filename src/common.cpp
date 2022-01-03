/***************************************************************
 * Name:      common.cpp
 * Purpose:   Class Implementation for general utilities
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include "common.h"
#include <iostream>
#include <sys/stat.h>
common::common()
{
    //ctor
}

common::~common()
{
    //dtor
}
int common::cuestamp_to_sectors(std::string stamp)
{
    std::stringstream test(stamp);
    std::string segment;
    int minutes , seconds, fields, count = 1;

    while(std::getline(test, segment, '_'))
    {
        if (count == 1)
            {minutes = stoi(segment); count++;}
        if (count == 2)
            {seconds = stoi(segment); count++;}
        if (count == 3)
            {fields  = stoi(segment); break;}

    }
    if (count != 3) {std::cerr <<"invalid cuestamp...\n"; return -1;}
    return ( fields + (seconds * 75) + (minutes * 60 * 75) );
}
int common::cuestamp_to_sectors (index_t INDEX)
{
    return ( INDEX.fields + (INDEX.secconds * 75) + (INDEX.minutes * 60 * 75) );
}
std::string common::sectors_to_cuestamp(int sectors)
{
    int minutes = (sectors / 4500);
    int fields = (sectors % 4500);
    int seconds = (fields / 75);
    fields = (sectors % 75);
    char buff[32];
    sprintf(buff,"%02d:%02d:%02d", minutes, seconds, fields);
    return std::string(buff);
}

size_t common::GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
