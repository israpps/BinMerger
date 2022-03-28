/***************************************************************
 * Name:      BinMerger.h
 * Purpose:   Class definition for program core
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#ifndef BINMERGER_H
#define BINMERGER_H
#include <regex>
#include <string>
#include "common.h"
#include "common/structs.h"
#include <vector>

size_t get_BlockSize(std::string TRACK_TIPE);
class BinMerger : common
{
public:
    BinMerger();
    virtual ~BinMerger();
    std::vector<bin_t> parse_cue(std::string CUEPATH);
    int fuse_bins(std::vector<bin_t>vec, std::string outpath);
    std::string generate_merged_cue(std::vector<bin_t> vec, std::string merged_bin_filename);
protected:

private:
    const std::regex TRACK_REGEX = std::regex("[0-9]+ [a-bA-b0-9\\/]+");
    //const std::regex TRACK_REGEX = std::regex("[0-9]+");
    const std::regex INDEX_REGEX = std::regex("[0-9]+ [0-9][0-9]\\:[0-9][0-9]\\:[0-9][0-9]");
    //const std::regex FILE_REGEX  = std::regex("FILE \"?(.*?)\"? BINARY");
    size_t globalBlocksize;


    enum ITERATE_STATE {_O = 0,FOUND_FILE, FOUND_TRACK, FOUND_INDEX};
};

#endif // BINMERGER_H
