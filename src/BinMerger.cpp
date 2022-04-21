/***************************************************************
 * Name:      BinMerger.cpp
 * Purpose:   Class implementation for program core
 * Author:    El_isra (israelson-matias@hotmail.com)
 * Created:   2022-01-03
 * Copyright: El_isra (https://www.github.com/israpps)
 * License:   MIT License
 **************************************************************/
#include "BinMerger.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "common/structs.h"

BinMerger::BinMerger()
{}

BinMerger::~BinMerger()
{}

std::vector<bin_t> BinMerger::parse_cue(std::string CUEPATH)
{
    int track_count = 0, index_count = 0, file_count = 0;
    std::cout << "Parsing cue file...\n";
    bool first_iteration = true;
    common Common;
    std::string line, binpath,
        ROOT = CUEPATH.substr(0,CUEPATH.find_last_of('\\')+1);
    std::ifstream CUE(CUEPATH);
    std::smatch match;
    size_t first_quote_of_FILE = std::string::npos;
    int last_state = 0, linecount = 0;
    std::vector<bin_t> BINS;
    if (!CUE.is_open())
    {
        std::cerr << "ERROR: Can't open original cue file for processing...\nprovided file path was: \""<<CUEPATH<<"\"\n";
        return BINS;
    }
    bin_t tmpbin;
    while (std::getline(CUE, line))
    {
        linecount++;
        //std::cout<<"|"<<line<<"|\n";
        if (line.find("FILE") != std::string::npos)
        {
            if (last_state == FOUND_TRACK)
            {
                std::cerr << "ERROR: expected track index on line ["<<linecount<<"], instead, FILE entry was found\n";
                goto ERR;
            }
            if (last_state == FOUND_INDEX)
            {
                BINS.push_back(tmpbin);
                tmpbin.index.clear();
                first_iteration = false;
            }
            last_state = FOUND_FILE;
            first_quote_of_FILE = line.find_first_of('\"');
            binpath = line.substr(first_quote_of_FILE +1, line.find_first_of('\"', first_quote_of_FILE + 1) - (first_quote_of_FILE+1));
            tmpbin.path = binpath;
            tmpbin.size = Common.GetFileSize(ROOT+binpath);
            if (tmpbin.size < 1)
            {
                std::cerr << "ERROR: bin file asociated to FILE entry on line ["<<linecount<<"] can't be stated to obtain file data\n";
                goto ERR;
            }
            file_count++;
        }
        if (line.find("TRACK") != std::string::npos)
        {
            last_state = FOUND_TRACK;
            if (std::regex_search(line, match, TRACK_REGEX))
            {
                tmpbin.track = match[0];
                if(first_iteration)
                {
                    globalBlocksize = get_BlockSize(tmpbin.track.substr(tmpbin.track.find_first_of(' ')+1 ) );
                }
            }
            else
            {
                std::cerr << "ERROR: can't find TRACK data on line ["<<linecount<<"]\n";
                goto ERR;
            }
        track_count++;
        }
        if (std::regex_search(line, match, INDEX_REGEX))
        {
            if ((last_state == FOUND_INDEX) || (last_state == FOUND_TRACK))
            {
                std::string tmpmatch = match[0];
                last_state = FOUND_INDEX;
                tmpbin.index.push_back(populate_index(match[0]));
            }
            else
            {
                std::cerr <<"ERROR: Found INDEX entry on line ["<<linecount<<"], previously expected another INDEX or TRACK entry\n";
                goto ERR;
            }
            index_count++;
        }
    }
    if (file_count < 2) {std::cerr<<"ERROR: less than two bin files on CUE...\nAborting process...\n"; goto ERR;}
    BINS.push_back(tmpbin);
    tmpbin.index.clear();
    std::cout << "[Cue Parser]: parsing finished. found ["<<file_count <<"] bin files, ["<<track_count<< "] Tracks and ["<< index_count <<"] Indexes. Global Block Size: ["<<globalBlocksize<<"]\n";
    return BINS;
ERR:
    BINS.clear();
    return BINS;
}

std::string BinMerger::generate_merged_cue(std::vector<bin_t> vec, std::string merged_bin_filename)
{
    common Common;
    std::string new_cue;
    new_cue = "FILE \"" + merged_bin_filename + ".bin\" BINARY\n";
    size_t sector_pos = 0;
    for (size_t x = 0; x < vec.size(); x++)
    {
        bin_t tmpbin = vec[x];
        new_cue += "  TRACK " + vec[x].track + "\n";
        for (size_t z = 0; z < vec[x].index.size(); z++)
        {
            //std::cout <<"INDEX["<<z<<"] - offset["<<vec[x].index[z].file_offset<<"]\n";
            new_cue += "    INDEX " + vec[x].index[z].number_as_string + " " + Common.sectors_to_cuestamp(sector_pos + vec[x].index[z].file_offset) + "\n";
        }
        sector_pos =(sector_pos + (vec[x].size / globalBlocksize));
    }
    std::ofstream OUTCUE;
    OUTCUE.open(merged_bin_filename+".cue");
    OUTCUE << new_cue;
    OUTCUE.close();
    return new_cue;
}

int BinMerger::fuse_bins(std::vector<bin_t>vec, std::string outpath)
{
    std::ofstream OUTFILE ;
    size_t DD = 0,QQ = 0, vecsize = vec.size();
    OUTFILE.open(outpath+".bin",std::ofstream::binary);
    for (size_t x = 0; x < vecsize; x++)
    {
        QQ += vec[x].size;
    }
    std::cout <<QQ <<" -> Merged bin size\n";
    for (size_t x = 0; x < vecsize; x++)
    {
        std::ifstream fin(vec[x].path, std::ifstream::binary);
        if (!fin.is_open())
        {
            std::cerr <<"\nERROR: Can't open bin number "<< x <<"\npath: \""<<vec[x].path<<"\"\naborting file creation...\n";
        }
        std::vector<char> buffer (1024*1024,0); //reads only the first 1024 bytes
        while(!fin.eof())
        {
            fin.read(buffer.data(), buffer.size());
            std::streamsize s=fin.gcount();
            OUTFILE.write(buffer.data(),s);
            DD += s;
            std::cout << DD <<" bytes written, bin ("<<((x+1)*100/vecsize)<<"%)\r";
        }
        //COLOR_INT(07);
        fin.close();
    }
    OUTFILE.close();
    std::cout << std::endl;
    return 0;
}
