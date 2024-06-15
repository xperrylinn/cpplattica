#ifndef MPI_STATE_CHANGE_TYPE_H
#define MPI_STATE_CHANGE_TYPE_H

#include <mpi.h>

struct mpi_state_change {
    int site_id;
    int new_state;
};

inline MPI_Datatype create_mpi_state_change_type() {
    MPI_Datatype mpiStateChangeType;

    int blockLengths[2] = {1, 1}; // Each member is a single element

    MPI_Aint offsets[2];
    offsets[0] = offsetof(mpi_state_change, site_id);
    offsets[1] = offsetof(mpi_state_change, new_state);

    MPI_Datatype types[2] = {MPI_INT, MPI_INT};

    MPI_Type_create_struct(2, blockLengths, offsets, types, &mpiStateChangeType);
    MPI_Type_commit(&mpiStateChangeType);

    return mpiStateChangeType;
}

#endif // MPI_STATE_CHANGE_TYPE_H
