//
// Created by vadim on 21.08.20.
//

#ifndef GAMEOFLIFE_ENGINE_HPP
#define GAMEOFLIFE_ENGINE_HPP

#include <SFML/Graphics.hpp>

namespace Engine
{

    enum MAP
    {
        HEIGHT = 10,
        WIDTH  = 10
    };
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

    void root_routine();

};

#endif //GAMEOFLIFE_ENGINE_HPP
