cmake_minimum_required(VERSION 2.8.12)

PROJECT(Eye_Glasses_Not_Eye_Glasses)

find_package( OpenCV REQUIRED )

# ###  Windows users uncomment the 6 lines below  ###

find_package( dlib REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ${dlib_INCLUDE_DIRS})
file(GLOB Eye_Glasses_Not_Eye_Glasses
    "*.h"
    "*.cpp"
)

add_executable( Eye_Glasses_Not_Eye_Glasses ${Eye_Glasses_Not_Eye_Glasses} )
target_link_libraries( Eye_Glasses_Not_Eye_Glasses ${OpenCV_LIBS} ${dlib_LIBS} )
