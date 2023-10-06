cmake_minimum_required(VERSION 3.0)
project("B3Semi")              
add_executable(Program
	src/main.cpp
	src/myImage.hpp
	src/lib/fileio.cpp
	src/lib/color_convert.cpp
	src/lib/filtering.cpp
	src/lib/binarize.cpp
	src/lib/hls.cpp
	src/lib/edge.cpp
	src/lib/affine.cpp
	src/lib/hough.cpp
	src/lib/labeling.cpp
)