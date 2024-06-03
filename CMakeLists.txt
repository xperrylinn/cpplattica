cmake_minimum_required(VERSION 3.14)
project(cpplattica)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(MPI REQUIRED)

find_package(Armadillo REQUIRED)

# Include directories for Armadillo
include_directories(${ARMADILLO_INCLUDE_DIRS})

# We require the GNU compiler for this assignment.
if (NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(Prg-Clang "PrgEnv-cray")
    message(WARNING
            "Must use GNU Compiler for submission. Make sure you ran:\n"
            "module swap ${Prg-${CMAKE_C_COMPILER_ID}} PrgEnv-gnu")
endif ()

# Set the source directory
set(SRC_DIR src)

# List of source files
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/constants.h
    ${SRC_DIR}/helpers.h
    ${SRC_DIR}/helpers.cpp
    ${SRC_DIR}/phases_set.h 
    ${SRC_DIR}/phases_set.cpp 
    ${SRC_DIR}/lattice.h 
    ${SRC_DIR}/lattice.cpp 
    ${SRC_DIR}/square_grid_lattice_2d.h 
    ${SRC_DIR}/square_grid_lattice_2d.cpp 
    ${SRC_DIR}/structure_builder.h 
    ${SRC_DIR}/structure_builder.cpp 
    ${SRC_DIR}/simple_sqaure_2d_structure_builder.h  
    ${SRC_DIR}/simple_sqaure_2d_structure_builder.cpp
    ${SRC_DIR}/discrete_grid_setup.h
    ${SRC_DIR}/discrete_grid_setup.cpp
    ${SRC_DIR}/simulation.h
    ${SRC_DIR}/simulation.cpp
    ${SRC_DIR}/periodic_structure.h
    ${SRC_DIR}/periodic_structure.cpp
    ${SRC_DIR}/simulation_state.h
    ${SRC_DIR}/simulation_state.cpp
    ${SRC_DIR}/simulation_result.cpp
    ${SRC_DIR}/simulation_result.h
    ${SRC_DIR}/site.h
    ${SRC_DIR}/site.cpp
    ${SRC_DIR}/basic_controller.h
    ${SRC_DIR}/basic_controller.cpp
    ${SRC_DIR}/game_of_life_controller.h
    ${SRC_DIR}/game_of_life_controller.cpp
    ${SRC_DIR}/neighborhood_builder.h
    ${SRC_DIR}/neighborhood_builder.cpp
    ${SRC_DIR}/motif_neighborhood_builder.h
    ${SRC_DIR}/motif_neighborhood_builder.cpp
    ${SRC_DIR}/moore_neighborhood_builder.h
    ${SRC_DIR}/moore_neighborhood_builder.cpp
    ${SRC_DIR}/neighborhood.h
    ${SRC_DIR}/neighborhood.cpp
    ${SRC_DIR}/distance_map.h
    ${SRC_DIR}/distance_map.cpp
    ${SRC_DIR}/euclidean_distance_map.h
    ${SRC_DIR}/euclidean_distance_map.cpp
    ${SRC_DIR}/synchronous_runner.h
    ${SRC_DIR}/synchronous_runner.cpp
    ${SRC_DIR}/runner.h
    ${SRC_DIR}/runner.cpp
)

# Add the executable
add_executable(mpi ${SOURCES})

target_link_libraries(mpi PRIVATE MPI::MPI_CXX ${ARMADILLO_LIBRARIES})

# Copy the job scripts
# configure_file(job-mpi job-mpi COPYONLY)
