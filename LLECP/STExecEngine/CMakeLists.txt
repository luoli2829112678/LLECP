file(GLOB_RECURSE CompilerCore_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CompilerCore/*.cpp")
file(GLOB_RECURSE FuncUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/FuncUint/*.cpp")
file(GLOB_RECURSE GrammarUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GrammarUint/*.cpp")
file(GLOB_RECURSE VariableUint_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/VariableUint/*.cpp")




add_library(STExecEngine SHARED
    STExecEngine.cpp
    ${CompilerCore_SOURCES}
    ${FuncUint_SOURCES}
    ${GrammarUint_SOURCES}
    ${VariableUint_SOURCES}
)

# 包含头文件目录（提供给主程序使用）
target_include_directories(STExecEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})