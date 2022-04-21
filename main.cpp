/***************************************************************
 * Name:      main.cpp
 * Purpose:   Program behaviour implementation
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   MIT License
 **************************************************************/

#include <iostream>
#include <string.h>

#include "BinMerger.h"
#include "version.h"

using namespace std;

int main(int argc, char** argv)
{
    std::string ARGV0 = argv[0];
    std::cout <<"\tBinMerger "<<AutoVersion::FULLVERSION_STRING<<"\n"<<
              "\tCoded By Matias Israelson (El_isra)  [www.github.com/israpps]\n";
    if (argc < 3)
    {
        std::cerr << "not enough argumments\nUsage:\n\t"<<ARGV0.substr(ARGV0.find_last_of('\\')+1)<<" [CUE Location] [New Filename (without extension)]\n";
        return -1;
    }
    BinMerger A;
    std::vector<bin_t> B = A.parse_cue(std::string(argv[1]));
    if (B.size() == 0 )
    {
        std::cerr << "Collected data from BIN was incorrect or incomplete...\naborting file merging...\n";
        return -1;
    }
    A.generate_merged_cue(B,std::string(argv[2]));
    A.fuse_bins(B,std::string(argv[2]));
    return 0;
}
