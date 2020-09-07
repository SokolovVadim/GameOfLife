//
// Created by vadim on 21.08.20.
//

#include <iostream>
#include "engine.hpp"
#include "matrix.hpp"
#include "mpi.h"


namespace Engine {
    // void draw(sf::RenderWindow &window, sf::Sprite &sprite, Matrix &matrix);

    void render_graphics(Matrix& matrix)
    {
        sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");
        sf::Texture texture{};
        if (!texture.loadFromFile("image.png"))
        {
            std::cerr << "error! Texture loading failed\n";
        }
        matrix.init_map(texture);
        matrix.set_position();

        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            matrix.draw(window);
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

    /*void send_to_neigbour(Matrix & matrix)
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
    }*/

    void send_data(Matrix& matrix, int proc_num, int step)
    {
        if(step == 0) // initial state
        {
            // snd line in cycle
            int tag(0), count(matrix.get_dimx());

            for(int i(1); i < proc_num; ++i)
            {

                // send dimx

                MPI_Send(&count, 1, MPI_INT, i, tag, MPI_COMM_WORLD);

                // send line

                // std::cout << "from root" << std::endl;
                // int* buf = get_buf(matrix, i - 1);
                // MPI_Send(buf, count, MPI_INT, i, tag, MPI_COMM_WORLD);
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
        send_to_process(matrix);
        step++;
        recv_up_to_date_data(matrix);
        render_graphics(matrix);
    }

    void test_recv_data(int count, int rank, int* buf0, int* buf1, int* buf2)
    {
        std::string msg = "---------------------------------\n";
        msg += "rank = " + std::to_string(rank) + "\n";

        for(int i(0); i < count; ++i)
        {
            msg += std::to_string(buf0[i]);
        }
        msg += '\n';
        for(int i(0); i < count; ++i)
        {
            msg += std::to_string(buf1[i]);
        }
        msg += '\n';
        for(int i(0); i < count; ++i)
        {
            msg += std::to_string(buf2[i]);
        }
        msg += '\n';
        std::cout << msg;
    }

    int recv_data(int proc_num, int rank)
    {
        int tag(0), count(0);
        MPI_Status status{};

        // receive dimx

        MPI_Recv(&count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        // std::string msg = "count " + std::to_string(count) + "\n";
        // std::cout << msg;
        auto buf0 = new int[count];
        auto buf1 = new int[count];
        auto buf2 = new int[count];

        MPI_Recv(buf0, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(buf1, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(buf2, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        test_recv_data(count, rank, buf0, buf1, buf2);
        return count;
    }

    void update()
    {

    }

    void send_up_to_date_data(int* line, int count)
    {
        // send line from client to root
        int tag(0);
        MPI_Send(line, count, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    void client_routine(int proc_num, int rank)
    {
        // std::cout << "I'm client" << std::endl;

        // receive data from root
        int count = recv_data(proc_num, rank);

        // update line
        update();

        // send line to root to be printed
        int* line{};
        send_up_to_date_data(line, count);
    }


    void init()
    {

    }

    void snd_data()
    {

    }

    void recv_data()
    {

    }

};