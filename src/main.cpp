#include <iostream>
#include <mpi.h>
#include "engine.hpp"

int main(int argc, char* argv[])
{

    std::cout << "Hello!\n";

    int error = MPI_Init(&argc, &argv);
    if(error)
        std::cerr << "MPI_Init crashed!" << std::endl;

    int size(0), rank(0);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) // root
    {
        Engine::root_routine();
    }
    else
    {

    }

    MPI_Finalize();

    return 0;
}
