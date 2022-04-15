# Setup cmake
cmake_minimum_required( VERSION 3.5 )
project( Bot )
set( CMAKE_CONFIGURATION_TYPES "Release;Dev;Debug" )
if( UNIX )
  set( CMAKE_POSITION_INDEPENDENT_CODE ON )
endif()
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

# Setup compiler options
if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
  # Harcoded setup for clang + ldd
  add_compile_options( -std=c++17 -lm -lpthread -ldl -lcrypt -Wall -Wextra -Wconversion -Wshadow-all -Wno-shadow-field-in-constructor -Wno-format-security -Wno-unused-command-line-argument -m64 -mavx2 -mfma -march=native )
  set( LINKER_FLAGS "-fuse-ld=lld" )
  set( COMPILER_OPTIMIZATION_FLAGS "-Ofast")
  set( COMPILER_NO_OPTIMIZATION_FLAGS "-O0")
  set( COMPILER_DEBUG_INFO "-fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -ggdb3 -D_GLIBCXX_ASSERTIONS=1" )
elseif( MSVC )
  add_compile_options( /std:c++17 /sdl /Wall /nologo /wd4514 /wd5045 /wd4820 /wd4626 /wd5027 /wd4623 /wd4625 /wd4710 /wd4711 /Zi)
  set( COMPILER_NO_OPTIMIZATION_FLAGS "/Od /wd4710")
  set( COMPILER_DEBUG_INFO "/Z7 /Zi")
  set( LINKER_FLAGS "/DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF")
else()
  # Setup for you own compiler + linker here
  message( WARNING "Not using Clang or MSVC: make sure to add a configuration for your ${CMAKE_CXX_COMPILER_ID} compiler")
endif()

set( CMAKE_CXX_FLAGS_RELEASE "${COMPILER_OPTIMIZATION_FLAGS}" )
set( CMAKE_CXX_FLAGS_DEV     "${COMPILER_OPTIMIZATION_FLAGS} ${COMPILER_DEBUG_INFO}" )
set( CMAKE_CXX_FLAGS_DEBUG   "${COMPILER_NO_OPTIMIZATION_FLAGS} ${COMPILER_DEBUG_INFO}" )

set( CMAKE_SHARED_LINKER_FLAGS_RELEASE "${LINKER_FLAGS}" CACHE STRING "" FORCE )
set( CMAKE_SHARED_LINKER_FLAGS_DEV     "${LINKER_FLAGS}" CACHE STRING "" FORCE )
set( CMAKE_SHARED_LINKER_FLAGS_DEBUG   "${LINKER_FLAGS}" CACHE STRING "" FORCE )

set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${LINKER_FLAGS}" CACHE STRING "" FORCE )
set( CMAKE_EXE_LINKER_FLAGS_DEV     "${LINKER_FLAGS}" CACHE STRING "" FORCE )
set( CMAKE_EXE_LINKER_FLAGS_DEBUG   "${LINKER_FLAGS}" CACHE STRING "" FORCE )

mark_as_advanced( 
  CMAKE_CXX_FLAGS_RELEASE CMAKE_SHARED_LINKER_FLAGS_RELEASE CMAKE_EXE_LINKER_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_DEV     CMAKE_SHARED_LINKER_FLAGS_DEV     CMAKE_EXE_LINKER_FLAGS_DEV
  CMAKE_CXX_FLAGS_DEBUG   CMAKE_SHARED_LINKER_FLAGS_DEBUG   CMAKE_EXE_LINKER_FLAGS_DEBUG )

# Setup targets
add_executable( bot "src/bot.cpp")
add_custom_command( TARGET bot POST_BUILD
  COMMAND "python" "${PROJECT_ROOT}/merge_source_files.py" "${PROJECT_ROOT}/src/bot.cpp" "${INCLUDE_DIR}" "${PROJECT_ROOT}/package/bot.cpp"
  COMMENT "assembling CodinGame source"
)

add_executable( unit_tests "tests/unit_tests.cpp")
