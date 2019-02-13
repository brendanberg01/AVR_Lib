cmake_minimum_required(VERSION 3.12)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if (NOT HAS_PARENT)
    project(AVR_Lib)
    add_library(AVR_Lib "")
endif()

add_subdirectory(io)
