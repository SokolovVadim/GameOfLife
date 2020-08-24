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

    int* get_buf(Matrix & matrix, int line_num)
    {
        int dimx = matrix.get_dimx();
        auto line = new int[dimx];
        for(int i(0); i < dimx; ++i)
        {
            line[i] = matrix(uint32_t(line_num), i);
        }
    }

    void send_data(Matrix& matrix, int proc_num, int step)
    {
        if(step == 0) // initial state
        {
            // snd line in cicle

            for(int i(1); i < proc_num; ++i)
            {
                int tag(0), count(1);
                std::cout << "from root" << std::endl;
                int* buf = get_buf(matrix, i - 1);
                MPI_Send(&i, count, MPI_INT, i, tag, MPI_COMM_WORLD);
            }
        }
        else
        {

        }
    }

    void root_routine(Matrix& matrix, int proc_num)
    {
        int step(0);
        std::cout << "proc num = " << proc_num << std::endl;
        send_data(matrix, proc_num, step);
        step++;
        // render_graphics();
    }

    void client_routine(int proc_num)
    {
        std::cout << "I'm client" << std::endl;

        // recv data from root


            int buf(0), tag(0), count(1);
            MPI_Status status{};
            MPI_Recv(&buf, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
            std::cout << "buf: " << buf << std::endl;


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