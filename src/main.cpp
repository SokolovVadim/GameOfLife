#include <iostream>
#include <mpi.h>
#include "engine.hpp"
#include "matrix.hpp"

int main(int argc, char* argv[])
{

    std::cout << "Hello!\n";

    int error = MPI_Init(&argc, &argv);
    if(error)
        std::cerr << "MPI_Init crashed!" << std::endl;

    int proc_num(0), rank(0);

    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) // root
    {
        Engine::Matrix Matrix(uint32_t(proc_num - 1), uint32_t(proc_num - 1));
        Matrix.init_state();
        Matrix.print();

        Engine::root_routine(Matrix, proc_num);
    }
    else // client
    {
        Engine::client_routine(proc_num, rank);
    }

    MPI_Finalize();

    return 0;
}

void test_fill_matrix()
{
    int proc_num = 6;
    Engine::Matrix Matrix(uint32_t(proc_num - 1), uint32_t(proc_num - 1));
    Matrix.init_state();
    Matrix.print();
    auto line = new int[proc_num - 1];
    for(int i(0); i < proc_num - 1; ++i)
    {
        line[i] = i;
    }
    Matrix.fill_matrix(line, 1);
    Matrix.print();
}
