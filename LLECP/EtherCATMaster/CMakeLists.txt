include_directories(/opt/etherlab/include)
add_subdirectory(SOEM)
link_directories(/opt/etherlab/lib)
# 创建一个静态库（也可用 SHARED 变动态库）
add_library(EtherCATMaster SHARED
    EtherCATMaster.cpp
    sdo_operation.cpp
    slave/SlaveBase.cpp
    slave/NETX_50_RE_ECS.cpp
    slave/EL1088.cpp
    slave/EL2088.cpp
)

# 包含头文件目录（提供给主程序使用）
target_include_directories(EtherCATMaster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(EtherCATMaster PRIVATE soem CIA402Axis)