#   Copyright 2017 Edoardo Pasca
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

cmake_minimum_required (VERSION 3.0)

project(RGL)
#https://stackoverflow.com/questions/13298504/using-cmake-with-setup-py

# The version number.
set (RGL_VERSION_MAJOR 1)
set (RGL_VERSION_MINOR 0)

set (CIL_VERSION_MAJOR 0)
set (CIL_VERSION_MINOR 10)
set (CIL_VERSION_PATCH 2)

# set (CIL_VERSION '${CIL_VERSION_MAJOR}.${CIL_VERSION_MINOR}.${CIL_VERSION_PATCH}' CACHE INTERNAL "Core Imaging Library version" FORCE)
# get CIL_VERSION from environment variable and set it in cmake
set (CIL_VERSION $ENV{CIL_VERSION} CACHE INTERNAL "Core Imaging Library version" FORCE)
message(STATUS "CIL_VERSION set to " ${CIL_VERSION})

# set the Python variables for the Conda environment
#include(${CMAKE_SOURCE_DIR}/CMake/FindAnacondaEnvironment.cmake)

option (BUILD_MATLAB_WRAPPER "Build Matlab Wrappers" OFF)
option (BUILD_PYTHON_WRAPPER "Build Python Wrappers" ON)
option (CONDA_BUILD "Conda Build" OFF)
option (BUILD_CUDA "Build the CUDA modules" ON)

set(MATLAB_DEST_DIR "" CACHE PATH "Directory of the Matlab wrappers")
if (MATLAB_DEST_DIR)
set(MATLAB_DEST "${MATLAB_DEST_DIR}")
else() 
set(MATLAB_DEST "${CMAKE_INSTALL_PREFIX}/matlab")
endif()
message(STATUS "Matlab wrappers will be installed in " ${MATLAB_DEST})

set(PYTHON_DEST_DIR "" CACHE PATH "Directory of the Matlab wrappers")
if (PYTHON_DEST_DIR)
 set(PYTHON_DEST "${PYTHON_DEST_DIR}")
else() 
 set(PYTHON_DEST "${CMAKE_INSTALL_PREFIX}/python")
endif()
message(STATUS "Python wrappers will be installed in " ${PYTHON_DEST})


add_subdirectory(Core)
add_subdirectory(Wrappers)
