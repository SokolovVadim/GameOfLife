#include <SFML/Graphics.hpp>
#include "engine.hpp"

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


int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Game of Life");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::cout << "Hello!\n";

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

    return 0;
}
