target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DigitalOutputPin.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DigitalInputPin.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnalogOutputPin.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnaloginputPin.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnalogInputController.cpp)
