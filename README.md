# cpplattica

# Building the Code

## On NERSC

First make sure the CMake module is loaded:

```
> module load cmake
```

Next step is to build the code. We'll follow a CMake tree build:

```
> mkdir build
> cd build
```

Next step is configure the build in either __Debug__ mode or __Release__ mode.

```
> cmake -DCMAKE_BUILD_TYPE=Release ..
```

Once the build is configured, we may actually execute the build:

```
> make
```

# Running the Code

You will need to test on at most two nodes for this assignment. To allocate two interactive KNL nodes instead of just one (as we did in previous assignments), the syntax is simple:

```
build> salloc -N 2 -C cpu -q interactive -t 01:00:00
```

```
srun -N 2 --ntasks-per-node=1 ./mpi -n 10 -s 1
```

# squeue

To view current user jobs:

```
squeue -u $USER
```

To cancel a specific job:

```
scancel $JobID
```