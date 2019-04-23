target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/UART.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UARTConnection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UARTInterruptMasterConnection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UARTInterruptSlaveConnection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UARTDataSource.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UARTDataDestination.cpp)
