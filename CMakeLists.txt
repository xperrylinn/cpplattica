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

add_executable(
    mpi 
    main.cpp
    constants.h
    helpers.h
    helpers.cpp
    phases_set.h 
    phases_set.cpp 
    lattice.h 
    lattice.cpp 
    square_grid_lattice_2d.h 
    square_grid_lattice_2d.cpp 
    structure_builder.h 
    structure_builder.cpp 
    simple_sqaure_2d_structure_builder.h  
    simple_sqaure_2d_structure_builder.cpp
    discrete_grid_setup.h
    discrete_grid_setup.cpp
    simulation.h
    simulation.cpp
    periodic_structure.h
    periodic_structure.cpp
    simulation_state.h
    simulation_state.cpp
    simulation_result.cpp
    simulation_result.h
    site.h
    site.cpp
    basic_controller.h
    basic_controller.cpp
    game_of_life_controller.h
    game_of_life_controller.cpp
    neighborhood_builder.h
    neighborhood_builder.cpp
    motif_neighborhood_builder.h
    motif_neighborhood_builder.cpp
    moore_neighborhood_builder.h
    moore_neighborhood_builder.cpp
    neighborhood.h
    neighborhood.cpp
    distance_map.h
    distance_map.cpp
    euclidean_distance_map.h
    euclidean_distance_map.cpp
    synchronous_runner.h
    synchronous_runner.cpp
    runner.h
    runner.cpp
)

target_link_libraries(mpi PRIVATE MPI::MPI_CXX ${ARMADILLO_LIBRARIES})

# Copy the job scripts
configure_file(job-mpi job-mpi COPYONLY)
