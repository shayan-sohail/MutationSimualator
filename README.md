# MutationSimulator

MutationSimulator is a C++ & CUDA C program that simulates the evolution of a population with an initial combination of genes. It starts with an initial population size and tries different variations from the initial population with some mutations until the desired gene is reached or the maximum iterations are reached.

## Installation

To use MutationSimulator, you need to have C++11 or above & CUDA Toolkit for CUDA implementation installed on your system. You can download the source code from the repository and compile it using a C++ compiler.

Alternatively, you can use CMake to build the project. Here are the steps to build the project with CMake:

1. Create a new directory and navigate into it:

   ```
   mkdir build && cd build
   ```

2. Run CMake with the path to the source code:

   ```
   cmake /path/to/MutationSimulator
   ```

3. Build the project:

   ```
   make
   ```

## Usage

To run MutationSimulator, navigate to the directory where the binary is located and run the following command:

    ./sim.exe
