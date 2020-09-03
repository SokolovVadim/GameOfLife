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
        void init_map(sf::Texture& texture);
        void draw(sf::RenderWindow& window);
        uint32_t get_dimx() const;
        uint32_t get_dimy() const;;
        void fill_matrix(int* line, uint32_t line_num);
        void set_position();
    private:
        std::vector<int32_t> inner_;
        std::vector<sf::Sprite> map_;
        uint32_t dimx_, dimy_;
    };
}

#endif //GAMEOFLIFE_MATRIX_HPP
