#pragma once


#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>




namespace sfml_utils {

inline void set_fill_color(sf::VertexArray& va, const sf::Color col = sf::Color::White) {
    for (size_t i = 0; i < va.getVertexCount(); ++i) {
        va[i].color = col;
    }
}
// camera transform
constexpr sf::Transform get_world_transform(const sf::Vector2f& focus_point, const sf::Vector2f& world_size, const float& zoom) {
    sf::Transform transform;
    transform.translate(world_size/2.f);
    transform.scale({zoom, zoom});
    // transform.translate(world_size * zoom);
    transform.translate(-focus_point);
    return transform;
}

// position trasform
// can be used to get mouse position from render to world
inline sf::Vector2f current_to_localpos(const sf::Vector2f& pos, const sf::Vector2f& current_size, const sf::Vector2f& focus_point, const float& zoom) {
    return get_world_transform(focus_point, current_size, zoom).getInverse().transformPoint(pos);
}

}; // namespace sfml_utils
