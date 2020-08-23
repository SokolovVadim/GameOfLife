//
// Created by vadim on 22.08.20.
//

#include <iostream>
#include <random>
#include "matrix.hpp"

namespace Engine
{
    Matrix::Matrix(uint32_t dimx, uint32_t dimy):
        dimx_(dimx),
        dimy_(dimy)
    {
        inner_.resize(dimx_ * dimy);
    }

    int32_t& Matrix::operator()(uint32_t x, uint32_t y)
    {
        if((x >= dimx_) || (y >= dimy_))
        {
            std::__throw_out_of_range("Indices are out of bounds");
        }
        else
        {
            return inner_[dimx_ * y + x];
        }
    }

    void Matrix::print()
    {
        for(uint32_t i(0); i < dimx_; ++i)
        {
            for(uint32_t j(0); j < dimy_; ++j)
            {
                std::cout << this->operator()(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    void Matrix::init_state()
    {
        srand(unsigned(time(nullptr)));
        // Seed with a real random value, if available
        std::random_device r{};

        // Choose a random mean between 0 and 1
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, 1);

        // Fill in matrix

        for(uint32_t i(0); i < dimx_; ++i)
            for(uint32_t j(0); j < dimy_; ++j)
                this->operator()(i, j) = uniform_dist(e1);
    }
}
