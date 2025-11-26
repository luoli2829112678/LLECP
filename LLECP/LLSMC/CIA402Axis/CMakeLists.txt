# hrsmc/CIA402Axis/CMakeLists.txt
add_library(CIA402Axis SHARED
    CIA402Axis.cpp
    CIA402AxisPDO.cpp
    CIA402AxisConfig.cpp
    CIA402AxisGeneral.cpp
)

target_include_directories(CIA402Axis PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(CIA402Axis PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)



# ===== 在配置阶段生成 CIA402Axis/AxisFriendList.h（写入源码目录） =====
set(FRIEND_SCAN_DIR "${CMAKE_CURRENT_LIST_DIR}/../SMbasic")
file(GLOB_RECURSE FRIEND_HEADERS CONFIGURE_DEPENDS
    "${FRIEND_SCAN_DIR}/*.h"
    "${FRIEND_SCAN_DIR}/*.hpp"
)

set(GENERATED_FRIEND_FILE "${CMAKE_CURRENT_LIST_DIR}/AxisFriendList.h")
set(FRIEND_NAMESPACE "")  
# 读取头文件并用正则抓取 class 名称
set(_classes)
foreach(_h IN LISTS FRIEND_HEADERS)
    if(EXISTS "${_h}")
        file(READ "${_h}" _content)
        # 只匹配：class Name { / class Name : ... / class Name final ...
        string(REGEX MATCHALL
            "class[ \t\r\n]+([A-Za-z_][A-Za-z0-9_]*)[ \t\r\n]*(\\{|:|final|$)"
            _matches "${_content}")
        foreach(_m IN LISTS _matches)
            string(REGEX REPLACE
                "class[ \t\r\n]+([A-Za-z_][A-Za-z0-9_]*).*" "\\1"
                _cname "${_m}")
            list(APPEND _classes "${_cname}")
        endforeach()
    endif()
endforeach()

list(REMOVE_DUPLICATES _classes)
list(SORT _classes)

set(_out "/* 该文件自动生成，不需要手动修改 */\n")
set(_out "${_out}#ifndef FRIENDLIST_H\n#define FRIENDLIST_H\n\n")
set(_out "${_out}#define FRIEND_CLASSES \\\n")
foreach(_c IN LISTS _classes)
    set(_out "${_out}    friend class ${FRIEND_NAMESPACE}${_c}; \\\n")
endforeach()
set(_out "${_out}\n#endif /* FRIENDLIST_H */\n")

set(_need_write TRUE)
if(EXISTS "${GENERATED_FRIEND_FILE}")
    file(READ "${GENERATED_FRIEND_FILE}" _old)
    if(_old STREQUAL _out)
        set(_need_write FALSE)
    endif()
endif()

if(_need_write)
    file(WRITE "${GENERATED_FRIEND_FILE}" "${_out}")
    message(STATUS "[CIA402Axis] Wrote ${GENERATED_FRIEND_FILE} with ${_classes}")
else()
    message(STATUS "[CIA402Axis] ${GENERATED_FRIEND_FILE} up-to-date")
endif()

include_directories(BEFORE "${CMAKE_CURRENT_LIST_DIR}")
