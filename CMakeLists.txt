cmake_minimum_required(VERSION 2.8.4)
project(AntColonyAlgorithms)

set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

add_executable(antal antal.cpp common.cpp)
add_executable(antalRank antalRank.cpp)
add_executable(antalElitist antalElitist.cpp)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(antalShared antalShared.cpp common.cpp)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})
add_executable(antalMPI antalMPI.cpp common.cpp)
target_link_libraries(antalMPI ${MPI_LIBRARIES})
if(MPI_COMPILE_FLAGS)
  set_target_properties(antalMPI PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(antalMPI PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()