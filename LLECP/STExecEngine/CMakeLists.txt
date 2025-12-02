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

# 包含头文件目录（提供给主程序使用）
target_include_directories(STExecEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})