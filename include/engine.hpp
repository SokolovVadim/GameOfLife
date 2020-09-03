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
        HEIGHT = 512,
        WIDTH  = 512
    };
    enum STATES
    {
        DEAD = 0,
        ALIVE = 1
    };

    class Cell
    {
        STATES status;
        // image, texture, sprite
    };

    class Matrix;

    void root_routine(Matrix& matrix, int proc_num);
    void client_routine(int proc_num);

};

#endif //GAMEOFLIFE_ENGINE_HPP
