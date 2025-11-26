# 创建一个静态库（也可用 SHARED 变动态库）
file(GLOB_RECURSE FUNCUINT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/FuncUint/*.cpp")
add_library(RT_Script SHARED
    RT_Script.cpp
    ScriptVariable.cpp
    RT_ScriptActuator.cpp
    RT_ScriptInterpreter.cpp
    RT_ScriptCalculator.cpp
    RT_ScriptActuatorUint.cpp
    ScriptUint/ScriptUint_Token.cpp
    ScriptUint/ScriptUint_Cmd.cpp
    ScriptUint/ScriptUint_Line.cpp
    ScriptUint/ScriptUint_Buffer.cpp
    ${FUNCUINT_SOURCES}
)

# 包含头文件目录（提供给主程序使用）
target_include_directories(RT_Script PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
