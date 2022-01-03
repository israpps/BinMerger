/***************************************************************
 * Name:      structs.cpp
 * Purpose:   Struct Implementation for index_t and bin_t algong with some utilities
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include "common/structs.h"
#include <iostream>
index_t populate_index(std::string regex_match_)
{
    //std::cout <<"populate_index_t:"<<regex_match_<<"\n";
    std::string segment;
    index_t output;
    int count=1;
    output.number_as_string = regex_match_.substr(0, regex_match_.find_first_of(' '));
    output.number = std::stoi(output.number_as_string);
    std::stringstream test(regex_match_.substr(regex_match_.find_first_of(' ')+1) );
    while(std::getline(test, segment, ':'))
    {
        //std::cout << count<<" segment "<<segment<<"\n";
        if (count == 1)
            {output.minutes  = stoi(segment);}
        if (count == 2)
            {output.secconds = stoi(segment);}
        if (count == 3)
            {output.fields  = stoi(segment); break;}
         count++;
    }
    output.file_offset =  output.fields + (output.secconds * 75) + (output.minutes * 60 * 75) ;
    //std::cout<<" "<< output.minutes<<"-"<< output.secconds <<"-"<< output.fields<<"@"<<output.file_offset<<"|\n";
    return output;
}
