#include <mpi.h>
#include <vector>
#include <iostream>

// Dimensions of the overall grid
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;

// Number of iterations
const int ITERATIONS = 100;

// Function to get the state of a cell (e.g., a simple example for Conway's Game of Life)
int get_next_state(int current_state, int neighbor_count) {
    // Implement CA rules here (this is just an example)
    if (current_state == 1) {
        if (neighbor_count < 2 || neighbor_count > 3) {
            return 0; // Die
        }
        return 1; // Stay alive
    } else {
        if (neighbor_count == 3) {
            return 1; // Become alive
        }
        return 0; // Stay dead
    }
}

// Function to count live neighbors (example for Conway's Game of Life)
int count_live_neighbors(const std::vector<std::vector<int>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if (grid[x + i][y + j] == 1) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Create a 2D Cartesian communicator
    int dims[2] = {0, 0};
    MPI_Dims_create(size, 2, dims);

    int periods[2] = {0, 0}; // No wrap-around neighbors
    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &cart_comm);

    int coords[2];
    MPI_Cart_coords(cart_comm, rank, 2, coords);

    int left, right, up, down;
    MPI_Cart_shift(cart_comm, 0, 1, &left, &right);
    MPI_Cart_shift(cart_comm, 1, 1, &up, &down);

    // Determine the local grid size
    int local_width = GRID_WIDTH / dims[0];
    int local_height = GRID_HEIGHT / dims[1];

    // Allocate local grid with ghost cells
    std::vector<std::vector<int>> local_grid(local_height + 2, std::vector<int>(local_width + 2, 0));
    std::vector<std::vector<int>> next_grid(local_height + 2, std::vector<int>(local_width + 2, 0));

    // Initialize the local grid
    // Note: Replace with your own initialization logic
    for (int i = 1; i <= local_height; ++i) {
        for (int j = 1; j <= local_width; ++j) {
            local_grid[i][j] = (coords[0] + coords[1] + i + j) % 2;
        }
    }

    // Buffers for communication
    std::vector<int> send_left(local_height), send_right(local_height), send_up(local_width), send_down(local_width);
    std::vector<int> recv_left(local_height), recv_right(local_height), recv_up(local_width), recv_down(local_width);

    for (int iter = 0; iter < ITERATIONS; ++iter) {
        // Prepare data for communication
        for (int i = 1; i <= local_height; ++i) {
            send_left[i - 1] = local_grid[i][1];
            send_right[i - 1] = local_grid[i][local_width];
        }
        for (int j = 1; j <= local_width; ++j) {
            send_up[j - 1] = local_grid[1][j];
            send_down[j - 1] = local_grid[local_height][j];
        }

        // Exchange boundaries with neighbors
        MPI_Request requests[8];
        MPI_Isend(send_left.data(), local_height, MPI_INT, left, 0, cart_comm, &requests[0]);
        MPI_Irecv(recv_right.data(), local_height, MPI_INT, right, 0, cart_comm, &requests[1]);
        MPI_Isend(send_right.data(), local_height, MPI_INT, right, 1, cart_comm, &requests[2]);
        MPI_Irecv(recv_left.data(), local_height, MPI_INT, left, 1, cart_comm, &requests[3]);
        MPI_Isend(send_up.data(), local_width, MPI_INT, up, 2, cart_comm, &requests[4]);
        MPI_Irecv(recv_down.data(), local_width, MPI_INT, down, 2, cart_comm, &requests[5]);
        MPI_Isend(send_down.data(), local_width, MPI_INT, down, 3, cart_comm, &requests[6]);
        MPI_Irecv(recv_up.data(), local_width, MPI_INT, up, 3, cart_comm, &requests[7]);

        MPI_Waitall(8, requests, MPI_STATUSES_IGNORE);

        // Update ghost cells with received data
        for (int i = 1; i <= local_height; ++i) {
            local_grid[i][0] = recv_left[i - 1];
            local_grid[i][local_width + 1] = recv_right[i - 1];
        }
        for (int j = 1; j <= local_width; ++j) {
            local_grid[0][j] = recv_up[j - 1];
            local_grid[local_height + 1][j] = recv_down[j - 1];
        }

        // Update local grid
        for (int i = 1; i <= local_height; ++i) {
            for (int j = 1; j <= local_width; ++j) {
                int live_neighbors = count_live_neighbors(local_grid, i, j);
                next_grid[i][j] = get_next_state(local_grid[i][j], live_neighbors);
            }
        }

        // Swap grids
        local_grid.swap(next_grid);
    }

    MPI_Finalize();
    return 0;
}
