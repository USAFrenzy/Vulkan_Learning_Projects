cmake_minimum_required(VERSION 3.20)

# Include Directories for projects to be aware of #
include_directories(vendor/Vulkan/include)
include_directories(src)

################################################
# This Section Is For Linking To GLFW Later On #
################################################
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)     # Change Option To Build The Docs
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)    # Change Option To Build The Tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Change Option To Build The Examples
add_subdirectory(vendor/GLFW)

# cmakeSettings is the root folder for where other .cmake files will live

include(cmakeSettings/PreventInSrcBuilds.cmake) 
    assureoutofsourcebuilds()

#######################################
# Meta Data such as name and revision #
#######################################
include(cmakeSettings/MetaData.cmake)      
    project(${META_PROJECT_NAME} LANGUAGES CXX)

###################################################################################
#                        Project Options                                          #
###################################################################################
option(ENABLE_TESTING       "Enable Test Builds"                             OFF)

##############################
# Include For Testing Option #
##############################
include(CTest)


######################################################
#          Use solution folders feature              #
######################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#################################################################
#                 Setting Output Directories                    #
#################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

###################################################################
#                  Write The Version File Out                     #
###################################################################
file(WRITE "${PROJECT_BINARY_DIR}/VERSION" "${META_NAME_VERSION}")

##################################
#   Global configuration types   #
##################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

####################################
# If Tests Are Enabled, Build Them #
####################################
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(Tests)
endif()

###################################
# The Different Projects To Build #
###################################
add_subdirectory(src)

set_property(
   DIRECTORY
   PROPERTY
   VS_STARTUP_PROJECT
   Base_Project
)