//
// Created by vadim on 22.08.20.
//

#include <iostream>
#include "matrix.hpp"

namespace Engine
{
    Matrix::Matrix(uint32_t dimx, uint32_t dimy):
        dimx_(dimx),
        dimy_(dimy)
    {
        inner_.resize(dimx_ * dimy);
    }

    int8_t& Matrix::operator()(uint32_t x, uint32_t y)
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
        for(int32_t i(0); i < dimx_; ++i)
        {
            for(int32_t j(0); j < dimy_; ++j)
            {
                std::cout << inner_[i * dimx_ + j] << " ";
            }
            std::cout << std::endl;
        }
    }
}
