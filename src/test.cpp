#include <SFML/Graphics.hpp>
#include <iostream>
#include <mpi.h>

enum STATES
{
    ALIVE = 0,
    DEAD = 1
};

class Cell
{
    STATES status;
    // image, texture, sprite
};

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


int main(int argc, char* argv[])
{

    std::cout << "Hello!\n";

    int error = MPI_Init(&argc, &argv);
    if(error)
        std::cerr << "MPI_Init crashed!" << std::endl;

    int size(0), rank(0);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Game of Life");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
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

    MPI_Finalize();

    return 0;
}
