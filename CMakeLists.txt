if(WIN32)
    cmake_minimum_required(VERSION 3.4)
else()
    cmake_minimum_required(VERSION 3.0)
endif()

project(SuperimposeMesh
        LANGUAGES CXX
        VERSION 0.9.4.0)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(WIN32)
    add_definitions(-D_USE_MATH_DEFINES)
    if(MSVC)
        set(CMAKE_DEBUG_POSTFIX "d")
        set(CMAKE_CXX_FLAGS "/MP /EHsc")
        set(CMAKE_C_FLAGS "/MP /EHsc")
    endif()
endif()

### Options
# Is macOS?
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-D GLFW_MAC)
endif()

# Shared/Dynamic or Static library?
option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# Build test related commands?
option(BUILD_TESTING "Create tests using CMake" OFF)
if(BUILD_TESTING)
    enable_testing()
endif()

# Support RPATH?
option(ENABLE_RPATH "Enable RPATH for this library" ON)
mark_as_advanced(ENABLE_RPATH)
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}"
                          DEPENDS ENABLE_RPATH
                          USE_LINK_PATH)

# Default Build type to Release
if(NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
    endif()
endif()

### Compile- and install-related commands
add_subdirectory(src)

# Install the files necessary to call find_package(LibTemplateCMake) in CMake projects
include(InstallBasicPackageFiles)
install_basic_package_files(${PROJECT_NAME}
                            VERSION ${${PROJECT_NAME}_VERSION}
                            COMPATIBILITY ExactVersion
                            TARGETS_PROPERTY ${PROJECT_NAME}_TARGETS
                            NO_SET_AND_CHECK_MACRO
                            VARS_PREFIX ${PROJECT_NAME}
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO
                            DEPENDENCIES assimp "glew CONFIG" glfw3 OpenCV)

# Add the uninstall target
include(AddUninstallTarget)

# Add integration tests (unit tests for each library should be in each sublibrary directory)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
