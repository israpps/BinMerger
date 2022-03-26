/***************************************************************
 * Name:      main.cpp
 * Purpose:   Program behaviour implementation
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include <iostream>
#include <string.h>
#include "BinMerger.h"
using namespace std;
#include "version.h"
int main(int argc, char** argv)
{
    std::string ARGV0 = argv[0];
    std::cout <<"\tBinMerger "<<AutoVersion::FULLVERSION_STRING<<"\n"<<
                "\tCoded By Matias Israelson (El_isra)  [www.github.com/israpps]\n";
    if (argc < 2) {std::cerr << "not enough argumments\nUsage:\n\t"<<ARGV0.substr(ARGV0.find_last_of('\\')+1)<<" [CUE Location] [New Filename (without extension)]\n";return -1;}
    BinMerger A;
    std::vector<bin_t> B = A.parse_cue(std::string(argv[1]));
    A.generate_merged_cue(B,std::string(argv[2]));
    A.fuse_bins(B, (argc < 3) ? std::string(argv[2]) : std::string(argv[1]"_merge"));
    return 0;
}
