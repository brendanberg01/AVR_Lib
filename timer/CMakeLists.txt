target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Timer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TimerFastPWM.cpp)
