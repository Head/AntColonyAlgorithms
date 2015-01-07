cmake_minimum_required(VERSION 2.8.4)
project(AntColonyAlgorithms)

set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(antal antal.cpp)
add_executable(antalRank antalRank.cpp)
add_executable(antalElitist antalElitist.cpp)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})
add_executable(antalMPI antalMPI.cpp)
target_link_libraries(antalMPI ${MPI_LIBRARIES})
if(MPI_COMPILE_FLAGS)
  set_target_properties(antalMPI PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(antalMPI PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()