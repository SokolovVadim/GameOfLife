//
// Created by vadim on 22.08.20.
//

#ifndef GAMEOFLIFE_MATRIX_HPP
#define GAMEOFLIFE_MATRIX_HPP

#include "engine.hpp"

namespace Engine
{
    class Matrix
    {
    public:
        Matrix(uint32_t dimx, uint32_t dimy);
        int32_t& operator()(uint32_t x, uint32_t y);
        void print();
        void init_state();
        uint32_t get_dimx() const;
    private:
        std::vector<int32_t> inner_;
        uint32_t dimx_, dimy_;
    };
}

#endif //GAMEOFLIFE_MATRIX_HPP
