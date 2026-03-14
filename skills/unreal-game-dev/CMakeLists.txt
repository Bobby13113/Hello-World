# AI Overlords - Unreal Engine Game Project
# CMake configuration for Unreal Engine project

cmake_minimum_required(VERSION 3.16)

# Project configuration
project(AIOverlords VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Unreal Engine (supports UE 5.2 - 5.7)
find_path(UNREAL_ENGINE_ROOT
    NAMES Engine/Source/UnrealEngine.cpp
    PATHS
        "$ENV{PROGRAMFILES}/Epic Games/UE_5.7"
        "$ENV{PROGRAMFILES}/Epic Games/UE_5.6"
        "$ENV{PROGRAMFILES}/Epic Games/UE_5.5"
        "$ENV{PROGRAMFILES}/Epic Games/UE_5.4"
        "$ENV{PROGRAMFILES}/Epic Games/UE_5.3"
        "$ENV{PROGRAMFILES}/Epic Games/UE_5.2"
        "C:/Program Files/Epic Games/UE_5.7"
        "C:/Program Files/Epic Games/UE_5.6"
        "C:/Program Files/Epic Games/UE_5.5"
        "C:/Program Files/Epic Games/UE_5.4"
        "C:/Program Files/Epic Games/UE_5.3"
    PATH_SUFFIXES Engine/Source
)

if(NOT UNREAL_ENGINE_ROOT)
    message(FATAL_ERROR "Unreal Engine not found. Please install UE 5.2 or later.")
endif()

# Project directories
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_DIR "${PROJECT_ROOT}/Source")
set(PLUGIN_DIR "${PROJECT_ROOT}/Plugins")
set(CONFIG_DIR "${PROJECT_ROOT}/Config")
set(CONTENT_DIR "${PROJECT_ROOT}/Content")

# Create project directories
file(MAKE_DIRECTORY ${SOURCE_DIR})
file(MAKE_DIRECTORY ${CONFIG_DIR})
file(MAKE_DIRECTORY ${CONTENT_DIR})

# Game module
add_subdirectory(${SOURCE_DIR}/AIOverlords AIOverlords)

# Plugin support
if(EXISTS ${PLUGIN_DIR})
    add_subdirectory(${PLUGIN_DIR} ${PLUGIN_DIR})
endif()

# Install rules
install(DIRECTORY ${CONFIG_DIR} DESTINATION ${PROJECT_BINARY_DIR})
install(DIRECTORY ${CONTENT_DIR} DESTINATION ${PROJECT_BINARY_DIR})