cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(LLECP CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /usr/bin/LLETC)  # 可执行文件（.out / 无扩展名）
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /usr/bin/LLETC)  # 动态库（.so）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY /usr/bin/LLETC)  # 静态库（.a）
set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/etherlab/include)
link_directories(/opt/etherlab/lib)

add_subdirectory(EtherCATMaster)
add_subdirectory(RT_Script)
add_subdirectory(STExecEngine)
add_subdirectory(LLSMC)
add_subdirectory(TestExamples)
add_executable(LLECP main.cpp)
target_link_libraries(LLECP PUBLIC 
    RT_Script 
    STExecEngine
    CIA402Axis
    motion_algorithm
    soem
    SMbasic
    pthread 
    SoftMotion
    EtherCATMaster
)


target_include_directories(LLECP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CIA402Axis
    ${CMAKE_CURRENT_SOURCE_DIR}/SMbasic
    ${CMAKE_CURRENT_SOURCE_DIR}/SoftMotion
    ${CMAKE_CURRENT_SOURCE_DIR}/STExecEngine
)
