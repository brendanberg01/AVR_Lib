cmake_minimum_required(VERSION 3.12)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if (NOT HAS_PARENT)
    project(AVR_Lib)
    add_library(AVR_Lib "")

    if(APPLE)
        include_directories(/usr/local/CrossPack-AVR/include)
    elseif(WIN32)
        include_directories(C://AVR/avr/include)
    else()
        message(WARNING "AVR include directories not set for current operating system")
    endif()
endif()

add_subdirectory(util)
add_subdirectory(io)
add_subdirectory(usart)
add_subdirectory(timer)
add_subdirectory(interrupt)
