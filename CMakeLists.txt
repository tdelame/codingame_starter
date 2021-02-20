# Setup cmake
cmake_minimum_required( VERSION 3.5 )
project( Bot )
set( CMAKE_CONFIGURATION_TYPES "Release;Dev;Debug" )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None, Release, Dev and Debug" FORCE )
endif()

# Setup directories
set( PROJECT_ROOT "${CMAKE_SOURCE_DIR}" )
if( NOT DEFINED REPOSITORY_ROOT )
  if( DEFINED ENV{REPOSITORY_ROOT} )
    set( REPOSITORY_ROOT $ENV{REPOSITORY_ROOT} )
  else()
    set( REPOSITORY_ROOT "${PROJECT_ROOT}/../" )
  endif()
endif()
if( NOT DEFINED INCLUDE_DIR )
  if( DEFINED ENV{INCLUDE_DIR} )
    set( INCLUDE_DIR $ENV{INCLUDE_DIR} )
  else()
    set( INCLUDE_DIR "${REPOSITORY_ROOT}/tools/include" )
  endif()
endif()
if( NOT DEFINED LIB_DIR )
  if( DEFINED ENV{LIB_DIR} )
    set( LIB_DIR $ENV{LIB_DIR} )
  else()
    set( LIB_DIR "${REPOSITORY_ROOT}/tools/lib" )
  endif()
endif()
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_ROOT}/lib" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT}/lib" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT}/bin" )

include_directories( "${INCLUDE_DIR}" "${PROJECT_ROOT}/src" "${PROJECT_ROOT}/tests" )
link_directories( "${LIB_DIR}" )
file( MAKE_DIRECTORY "${PROJECT_ROOT}/package" )

# Setup compiler options (harcoded for clang + lld)
add_compile_options( -std=c++17 -Wall -Wextra -Wconversion -Wshadow-all -Wno-shadow-field-in-constructor -Wno-format-security )
set( LINKER_SELECTION "-fuse-ld=lld" )
set( COMPILER_DEBUG_INFO "-fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -ggdb3 -D_GLIBCXX_ASSERTIONS=1" )

set( CMAKE_CXX_FLAGS_RELEASE "-O3" )
set( CMAKE_CXX_FLAGS_DEV     "-O3 ${COMPILER_DEBUG_INFO}" )
set( CMAKE_CXX_FLAGS_DEBUG   "-O0 ${COMPILER_DEBUG_INFO}" )

set( CMAKE_SHARED_LINKER_FLAGS_RELEASE "${LINKER_SELECTION}" CACHE STRING "" FORCE )
set( CMAKE_SHARED_LINKER_FLAGS_DEV     "${LINKER_SELECTION}" CACHE STRING "" FORCE )
set( CMAKE_SHARED_LINKER_FLAGS_DEBUG   "${LINKER_SELECTION}" CACHE STRING "" FORCE )

set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${LINKER_SELECTION}" CACHE STRING "" FORCE )
set( CMAKE_EXE_LINKER_FLAGS_DEV     "${LINKER_SELECTION}" CACHE STRING "" FORCE )
set( CMAKE_EXE_LINKER_FLAGS_DEBUG   "${LINKER_SELECTION}" CACHE STRING "" FORCE )

mark_as_advanced( 
  CMAKE_CXX_FLAGS_RELEASE CMAKE_SHARED_LINKER_FLAGS_RELEASE CMAKE_EXE_LINKER_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_DEV     CMAKE_SHARED_LINKER_FLAGS_DEV     CMAKE_EXE_LINKER_FLAGS_DEV
  CMAKE_CXX_FLAGS_DEBUG   CMAKE_SHARED_LINKER_FLAGS_DEBUG   CMAKE_EXE_LINKER_FLAGS_DEBUG )

# Setup targets
add_executable( bot "src/bot.cpp")
add_custom_command( TARGET bot POST_BUILD
  COMMAND "${PROJECT_ROOT}/merge_source_files" "${PROJECT_ROOT}/src/bot.cpp" "${INCLUDE_DIR}" "${PROJECT_ROOT}/package/bot.cpp"
  COMMENT "assembling CodinGame source"
)

add_executable( unit_tests "tests/unit_tests.cpp")

# The VSCode extension will add targets below to compile previous bot versions
