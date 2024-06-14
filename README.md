# cpplattica


# Building the Code

## Locally on MacOS

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

### Debugging with LLDB

Configure the build in debug mode:

```
> cmake -DCMAKE_BUILD_TYPE=Debug ..
```

Once the build is configured, we may actually execute the build:

```
> make
```

Activate lldb with executable file:

```
> lldb ./mpi
```

#### General debugging commands

Set a breakpoint in a specific file:

```
> breakpoint set --file /Users/xavi/Documents/grad_school/CS267/final_project/cpplattica/main.cpp --line 39
```

Online resource, [LLBDB Quick Reference](https://www.cs.williams.edu/~morgan/cs136-f15/lldb.html)

## On NERSC

First make sure the CMake module is loaded:

```
> module load cmake
```

If the armadillo dependency is not installed download the tar from the [website](https://arma.sourceforge.net/download.html) and untar. 
Change directory the resulting library. Follow the cmake installation instructions in the README. Make sure the library is in the include path. For example,

```
> export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/global/homes/x/xlinn/armadillo-12.8.4
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

### Running the Code

You will need to test on at most two nodes for this assignment. To allocate two interactive KNL nodes instead of just one (as we did in previous assignments), the syntax is simple:

```
build> salloc -N 2 -C cpu -q interactive -t 01:00:00
```

```
srun -N 2 --ntasks-per-node=1 ./mpi
```

### Viewing current jobs on NERSC

To view current user jobs:

```
squeue -u $USER
```

To cancel a specific job:

```
scancel $JobID
```

### Debugging with GDB

Set breakpoint on a specific file and line:

```
break /global/homes/x/xlinn/cpplattica/src/synchronous_runner.cpp:37
```

Print variables:


```
```