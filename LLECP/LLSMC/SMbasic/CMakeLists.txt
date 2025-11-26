
set(SM_HEADER_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/AxisConfig"
    "${CMAKE_CURRENT_SOURCE_DIR}/AxisControl"
    "${CMAKE_CURRENT_SOURCE_DIR}/AxisMovement"
    "${CMAKE_CURRENT_SOURCE_DIR}/AxisRead"
)

set(SM_PRECOMPILED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/SMbasic_stdafx.h")
file(WRITE ${SM_PRECOMPILED_HEADER} "#pragma once\n\n/* 该文件自动生成，不需要手动修改 */\n\n")
foreach(DIR ${SM_HEADER_DIRS})
    file(GLOB HEADERS "${DIR}/*.h")
    foreach(HEADER ${HEADERS})
        get_filename_component(HNAME ${HEADER} NAME)
        get_filename_component(HDIR ${DIR} NAME)
        file(APPEND ${SM_PRECOMPILED_HEADER} "#include \"${HDIR}/${HNAME}\"\n")
    endforeach()
    file(APPEND ${SM_PRECOMPILED_HEADER} "\n")
endforeach()



file(GLOB_RECURSE AXISCONTROL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/AxisControl/*.cpp")
file(GLOB_RECURSE AXISMOVEMENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/AxisMovement/*.cpp")
file(GLOB_RECURSE AXISREAD_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/AxisRead/*.cpp")
file(GLOB_RECURSE AXISCONFIG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/AxixConfig/*.cpp")

add_library(SMbasic SHARED
    SMbasic.cpp
    ${AXISCONTROL_SOURCES}
    ${AXISMOVEMENT_SOURCES}
    ${AXISREAD_SOURCES}
    ${AXISCONFIG_SOURCES}
)

target_include_directories(SMbasic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(SMbasic PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(SMbasic PUBLIC CIA402Axis)
