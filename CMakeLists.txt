cmake_minimum_required (VERSION 2.8)

project (FuzzyE)

aux_source_directory(. DIR_SRCS)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/assets")
add_subdirectory(assets)

add_executable(FuzzyE main.cc)
target_link_libraries(FuzzyE Core)