file(GLOB_RECURSE CompilerCore_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CompilerCore/*.cpp")
file(GLOB_RECURSE FunctionUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/FunctionUint/*.cpp")
file(GLOB_RECURSE VariableUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/VariableUint/*.cpp")
file(GLOB_RECURSE CodeComponent_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CodeComponent/*.cpp")



add_library(STExecEngine SHARED
    STExecEngine.cpp
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

# 包含头文件目录（提供给主程序使用）
target_include_directories(STExecEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})