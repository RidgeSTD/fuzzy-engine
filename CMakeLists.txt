cmake_minimum_required (VERSION 3.0)

project (FuzzyE)

aux_source_directory(. DIR_SRCS)

# add dependency libraries
find_package(Eigen3)
include_directories("${EIGEN3_INCLUDE_DIR}")

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/core")
add_subdirectory(core)


add_executable(FuzzyE main.cc)
target_link_libraries(FuzzyE Core)
target_link_libraries(FuzzyE Eigen3::Eigen)