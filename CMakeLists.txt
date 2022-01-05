cmake_minimum_required(VERSION 3.10)

# set the project name
project(BinMerger)

# add the executable
include_directories(include)
add_executable(BinMerger main.cpp
                         PKG-000.rc
						 src/structs.cpp
						 src/common.cpp
						 src/track_t.cpp
						 src/BinMerger.cpp
                         )
