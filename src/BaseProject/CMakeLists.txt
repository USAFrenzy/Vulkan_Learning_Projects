set(PROJECT_NAME Base_Project)

message(CHECK_START "Building The Initial Base Project")

set(HEADER_FILES
"Base/base.h"
"Window/window.h"
)

set(IMPLEMENTATION_FILES
"main.cpp"
"Base/base.cpp"
"Window/window.cpp"
)

source_group("BaseProject\\Header Files" FILES ${HEADER_FILES})
source_group("BaseProject\\Source Files" FILES ${IMPLEMENTATION_FILES})

set(ALL_FILES
${HEADER_FILES}
${IMPLEMENTATION_FILES}
)


add_executable(${PROJECT_NAME} ${ALL_FILES})
target_include_directories(${PROJECT_NAME} 
PUBLIC
${Vulkan_INCLUDE_DIRS}
${GLFW_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/src/BaseProject
)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)


##################################################
#     Target name For Configuration Builds       #
##################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG        "BaseProject_Debug"
    TARGET_NAME_RELEASE      "BaseProject_Release"
)
####################################################
#             Compile definitions                  #
####################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "UNICODE;"
    "_UNICODE"
)

#####################################################
#             Compile and link options              #
#####################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Distribution>:
            /Oi;
            /GF;
            /Gy
        >
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >
        /permissive-;
        /std:c++17;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Distribution>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /SUBSYSTEM:CONSOLE
    )
endif()


message(CHECK_PASS "Base Project Finished")