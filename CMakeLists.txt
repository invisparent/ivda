cmake_minimum_required(VERSION 4.0)

project(ivda C)

set(CMAKE_C_STANDARD 11)

if (NOT IVS_ROOT)
    message(FATAL_ERROR "Variable IVS_ROOT is not set. Please specify it using -DIVS_ROOT=path_to_libivs")
endif ()

set(IVDA_INCLUDE_LOCAL ./include)

add_subdirectory(${IVS_ROOT} ./ivs)

add_library(ivda STATIC)

file(GLOB_RECURSE IVDA_SRCS ./src/*.c)
target_sources(ivda PRIVATE ${IVDA_SRCS})
target_include_directories(ivda PRIVATE ${IVDA_INCLUDE_LOCAL})
target_link_libraries(ivda PRIVATE ivs)
target_include_directories(ivda PRIVATE ${IVS_ROOT}/include)
target_compile_definitions(ivda PRIVATE $<$<CONFIG:Release,MinSizeRel>:IVS_NDEBUG>)
