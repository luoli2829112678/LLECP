set(CMAKE_CXX_STANDARD 17)
set(GRAMMAR_FILE   ${CMAKE_SOURCE_DIR}/STExecEngine/CompilerCore/ANTLR/STGrammar.g4)
set(GENERATED_DIR  ${CMAKE_SOURCE_DIR}/STExecEngine/CompilerCore/ANTLR/generated)

file(MAKE_DIRECTORY ${GENERATED_DIR})

execute_process(
    COMMAND antlr4
            -Dlanguage=Cpp
            -visitor
            -o ${GENERATED_DIR}
            ${GRAMMAR_FILE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/STExecEngine/CompilerCore/ANTLR
    RESULT_VARIABLE ANTLR_RESULT
    OUTPUT_VARIABLE ANTLR_OUT
    ERROR_VARIABLE  ANTLR_ERR
)

message(STATUS "ANTLR4 result = ${ANTLR_RESULT}")
message(STATUS "ANTLR4 stdout = ${ANTLR_OUT}")
message(STATUS "ANTLR4 stderr = ${ANTLR_ERR}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE CompilerCore_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CompilerCore/*.cpp")
file(GLOB_RECURSE FunctionUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/FunctionUint/*.cpp")
file(GLOB_RECURSE VariableUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/VariableUint/*.cpp")
file(GLOB_RECURSE CodeComponent_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CodeComponent/*.cpp")
file(GLOB_RECURSE ANTLR_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CompilerCore/ANTLR/generated/*.cpp")

add_library(STExecEngine SHARED
    STExecEngine.cpp
    ${ANTLR_SOURCES}
    ${CompilerCore_SOURCES}
    ${FunctionUint_SOURCES}
    ${VariableUint_SOURCES}
    ${CodeComponent_SOURCES}
)


file(GLOB FUNCTION_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctionUint/Function_*.h"
)
set(FUNCTION_INCLUDE_CONTENT "#pragma once\n\n")
set(FUNCTION_h1 "#include \"FunctionInfo.h\"\n\n")
set(FUNCTION_h2 "//#################该文件自动生成################\n\n")
foreach(h ${FUNCTION_HEADERS})
    # h 是完整路径，取文件名
    get_filename_component(hname "${h}" NAME)
    string(APPEND FUNCTION_INCLUDE_CONTENT "#include \"${hname}\"\n")
endforeach()

file(WRITE
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctionUint/FunctionInclude.h"
    "${FUNCTION_INCLUDE_CONTENT}"
    "${FUNCTION_h1}"
    "${FUNCTION_h2}"
)
target_include_directories(STExecEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/FunctionUint
    ${CMAKE_CURRENT_BINARY_DIR}          # 这里也要加
)

target_include_directories(STExecEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}                             # STExecEngine 自己的头
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionUint
        ${CMAKE_CURRENT_SOURCE_DIR}/CompilerCore/ANTLR/generated
        ${CMAKE_CURRENT_SOURCE_DIR}/CompilerCore/ANTLR/include/antlr4-runtime
)

target_link_libraries(STExecEngine
    antlr4-runtime
    Threads::Threads
)