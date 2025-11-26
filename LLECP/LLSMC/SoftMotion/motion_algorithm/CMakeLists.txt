add_library(motion_algorithm SHARED
    motion_planning/motion_planning.cpp
)

target_include_directories(motion_algorithm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(motion_algorithm PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
