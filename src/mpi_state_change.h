#ifndef MPI_STATE_CHANGE_TYPE_H
#define MPI_STATE_CHANGE_TYPE_H

#include <sstream>
#include <mpi.h>


struct mpi_state_change {
    int src_rank;
    int site_id;
    int new_state;

    std::string to_json() const {
        std::ostringstream oss;
        oss << "{"
            << "\"src_rank\":" << src_rank << ","
            << "\"site_id\":" << site_id << ","
            << "\"new_state\":" << new_state
            << "}";
        return oss.str();
    }
};

inline MPI_Datatype create_mpi_state_change_type() {
    MPI_Datatype mpi_state_change_type;

    int blockLengths[3] = {1, 1, 1};

    MPI_Aint offsets[3];
    offsets[0] = offsetof(mpi_state_change, src_rank);
    offsets[1] = offsetof(mpi_state_change, site_id);
    offsets[2] = offsetof(mpi_state_change, new_state);

    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT};

    MPI_Type_create_struct(3, blockLengths, offsets, types, &mpi_state_change_type);
    MPI_Type_commit(&mpi_state_change_type);

    return mpi_state_change_type;
}

#endif // MPI_STATE_CHANGE_TYPE_H
