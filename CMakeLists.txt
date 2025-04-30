cmake_minimum_required(VERSION 3.28)

# -----------------------------------------------------------------------------
# Include Macros

include(cmake/cfg.cmake)
include(cmake/add.cmake)
include(cmake/opt.cmake)

# -----------------------------------------------------------------------------
# Initialize Project

project(hook)

# -----------------------------------------------------------------------------
# Redirect Output Files

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "" FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ----------------------------------------------------------------------------
# Main Platform Checks

if(WIN32)
	include(cmake/platform_win32.cmake)
endif()

if(UNIX AND NOT APPLE)
	include(cmake/platform_linux.cmake)
endif()

include(CMakeDependentOption)

# -----------------------------------------------------------------------------
# Extra Compile Flags

# Select C++17 as the standard for C++ projects.
set(CMAKE_CXX_STANDARD 17)
# If C++17 is not available, downgrading to an earlier standard is NOT OK.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Do not enable compiler specific language extensions.
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------------------------------------------------
# Architecture

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    add_definitions(-D_AMD64_)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|i386")
    add_definitions(-D_X86_)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    add_definitions(-D_ARM64_)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    add_definitions(-D_ARM_)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "ia64")
    add_definitions(-D_IA64_)
endif()

# -----------------------------------------------------------------------------
# Organization

if(WIN32 OR XCODE)
	option(IDE_GROUP_SOURCES_IN_FOLDERS "Organize the source files in filters matching the source folders." ON)
	mark_as_advanced(IDE_GROUP_SOURCES_IN_FOLDERS)

	option(IDE_GROUP_PROJECTS_IN_FOLDERS "Organize the projects according to source folder structure." ON)
	mark_as_advanced(IDE_GROUP_PROJECTS_IN_FOLDERS)

	if(IDE_GROUP_PROJECTS_IN_FOLDERS)
		set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	endif()
endif()

# -----------------------------------------------------------------------------
# Enable Tests

enable_testing()

# -----------------------------------------------------------------------------
# Detect Endianess

detect_endianess()

# -----------------------------------------------------------------------------
# Add Sub-Directories

add_subdirectory(extern)
add_subdirectory(intern)
add_subdirectory(source)
add_subdirectory(target)
