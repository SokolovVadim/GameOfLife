//
// Created by vadim on 21.08.20.
//

#include "engine.hpp"



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
    void root_routine()
    {
        render_graphics();

        

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