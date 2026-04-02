#pragma once


#include <SFML/Graphics/VertexArray.hpp>




namespace sfml_utils {


inline void set_fill_color(sf::VertexArray& va, const sf::Color col = sf::Color::White) {
    for (size_t i = 0; i < va.getVertexCount(); ++i) {
        va[i].color = col;
    }
}


}; // namespace sfml_utils
