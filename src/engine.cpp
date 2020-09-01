//
// Created by vadim on 21.08.20.
//

#include <iostream>
#include "engine.hpp"
#include "matrix.hpp"
#include "mpi.h"


namespace Engine
{
    void render_graphics()
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Game of Life");
        sf::RectangleShape shape(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color::Magenta);

        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

    }

    void recv_up_to_date_data(Matrix & matrix)
    {
        int dimx = matrix.get_dimx();
        int proc_num = dimx + 1;
        auto line = new int[dimx];
        int tag(0), count(dimx);
        MPI_Status status{};
        for(int i(1); i < proc_num; ++i)
        {
            // receive line from proc i

            MPI_Recv(line, count, MPI_INT, i, tag, MPI_COMM_WORLD, &status);

            // write line to matrix

        }
    }

    int* get_buf(Matrix & matrix, int line_num)
    {
        int dimx = matrix.get_dimx();
        auto line = new int[dimx];
        for(int i(0); i < dimx; ++i)
        {
            line[i] = matrix(uint32_t(line_num), uint32_t(i));
        }
        return line;
    }

    void send_to_process(Matrix & matrix)
    {
        int dimx = matrix.get_dimx();
        int proc_num = dimx + 1;
        int count(dimx), tag(0);
        for(int i(1); i < proc_num; ++i)
        {
            if (i == 1) {
                // snd lines 0, 1, dimx - 1 to proc number 1
                int *buf = get_buf(matrix, i - 1);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
                buf = get_buf(matrix, i);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
                buf = get_buf(matrix, dimx - 1);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
            } else if (i == proc_num - 1) {
                // snd lines 0, dimx - 2, dimx - 1 to proc number proc_num - 1
                int *buf = get_buf(matrix, 0);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
                buf = get_buf(matrix, dimx - 2);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
                buf = get_buf(matrix, dimx - 1);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
            } else {
                // snd lines i - 2, i - 1, i to proc number i
                int *buf = get_buf(matrix, i - 2);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
                buf = get_buf(matrix, i - 1);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
                buf = get_buf(matrix, i);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
            }
        }
    }

    void send_to_neigbour(Matrix & matrix)
    {
        int dimx = matrix.get_dimx();
        int proc_num = dimx + 1;
        int count(dimx), tag(0);
        for(int i(0); i < dimx; ++i)
        {
            if(i == 0)
            {
                // snd to proc_num - 1, 1, 2
                int* buf = get_buf(matrix, i);
                MPI_Send(buf, count, MPI_INT, i + 1,        tag, MPI_COMM_WORLD);
                MPI_Send(buf, count, MPI_INT, i + 2,        tag, MPI_COMM_WORLD);
                MPI_Send(buf, count, MPI_INT, proc_num - 1, tag, MPI_COMM_WORLD);
            }
            else if(i == proc_num - 1)
            {
                // snd to 1, proc_num - 2, proc_num - 1
                int* buf = get_buf(matrix, i);
                MPI_Send(buf, count, MPI_INT, 1,            tag, MPI_COMM_WORLD);
                MPI_Send(buf, count, MPI_INT, proc_num - 2, tag, MPI_COMM_WORLD);
                MPI_Send(buf, count, MPI_INT, proc_num - 1, tag, MPI_COMM_WORLD);
            }
            else
            {
                // snd to i, i + 1, i + 2
                int* buf = get_buf(matrix, i);
                MPI_Send(buf, count, MPI_INT, i,     tag, MPI_COMM_WORLD);
                MPI_Send(buf, count, MPI_INT, i + 1, tag, MPI_COMM_WORLD);
                MPI_Send(buf, count, MPI_INT, i + 2, tag, MPI_COMM_WORLD);
            }
        }
    }

    void send_data(Matrix& matrix, int proc_num, int step)
    {
        if(step == 0) // initial state
        {
            // snd line in cycle

            for(int i(1); i < proc_num; ++i)
            {
                int tag(0), count(matrix.get_dimx());

                // send dimx

                MPI_Send(&count, 1, MPI_INT, i, tag, MPI_COMM_WORLD);

                // send line

                // std::cout << "from root" << std::endl;
                int* buf = get_buf(matrix, i - 1);
                MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
            }
        }
        else //
        {

        }
    }

    void root_routine(Matrix& matrix, int proc_num)
    {
        int step(0);
        // std::cout << "proc num = " << proc_num << std::endl;
        send_data(matrix, proc_num, step);
        step++;
        // render_graphics();
    }

    void recv_data(int proc_num)
    {

    }

    void client_routine(int proc_num)
    {
        // std::cout << "I'm client" << std::endl;

        // receive data from root


        int tag(0), count(0);
        MPI_Status status{};

        // receive dimx

        MPI_Recv(&count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        std::string msg = "count " + std::to_string(count) + "\n";
        // std::cout << msg;
        auto buf = new int[count];

        MPI_Recv(buf, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        // update

        // send data to neighbour


    }


    void init()
    {

    }

    void update()
    {

    }

    void draw()
    {

    }

    void snd_data()
    {

    }

    void recv_data()
    {

    }

};