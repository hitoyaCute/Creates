#include <cmath>
#include <SFML/Graphics/Drawable.hpp>
#include "basicShape.hpp"

namespace MEU {
namespace Shape {

CircleGenerator::CircleGenerator(const uint32_t quality_, const float radius_):
    da{(2.0f * sf::priv::pi) / quality_},
    radius{radius_}{};

constexpr sf::Vector2f CircleGenerator::get_point(const uint32_t i) const {
    const float angle = da * static_cast<float>(i);
    return {radius * sf::Vector2f{cosf(angle), sinf(angle)}};
}

RoundedRectGenerator::RoundedRectGenerator(const sf::Vector2f& size_, const float radius_, const uint32_t quality_):
    da{(2.0f * sf::priv::pi) / (quality_-4)},
    radius{radius_},
    quality{quality_},
    size{size_},
    centers{
        {size_.x - radius_, size_.y - radius_},
        {radius_          , size_.y - radius_},
        {radius_          , radius_},
        {size_.x - radius_, radius_}
    }{}

constexpr sf::Vector2f RoundedRectGenerator::get_point(const uint32_t i) const {
    const uint32_t idx{i / (quality / 4)};
    const float angle = da * (float)(i-idx);

    return centers[idx] + (radius * sf::Vector2f{cosf(angle), sinf(angle)});
}

///// functions

void CreateCircle(sf::VertexArray& arr,
                  const uint32_t quality,
                  const float radius,
                  const sf::Vector2f& pos,
                  const sf::Color& color) {
    CircleGenerator generator{quality, radius};
    for (uint32_t i{0}; i < quality; i++) {
        arr[i].position = pos + generator.get_point(i);
        arr[i].color = color;
    }
}

void CreateRoundedRect(sf::VertexArray& arr,
                       const uint32_t quality,
                       const float radius,
                       const sf::Vector2f& size,
                       const sf::Vector2f& pos,
                       const sf::Color& color) {
    RoundedRectGenerator generator{size, radius, quality};
    for (uint32_t i{0}; i < quality; i++) {
        arr[i].position = pos + generator.get_point(i);
        arr[i].color = color;
    }
}
void CreateRoundedRectBorder(sf::VertexArray& arr,
                             const uint32_t quality,
                             const float radius,
                             const float thickness,
                             const sf::Vector2f& size,
                             const sf::Vector2f& pos,
                             const sf::Color& color_inner,
                             const sf::Color& color_outer){
    RoundedRectGenerator inner{size, radius, quality/2 - 1};
    RoundedRectGenerator outer{size + 2.f * sf::Vector2f{thickness, thickness}, radius+(thickness/2), quality/2 - 1};
    

    for (uint32_t i{0}; i < quality/2 - 1; i++) {
        arr[i*2].position = pos + inner.get_point(i);
        arr[i*2].color = color_inner;
        arr[i*2+1].position = pos + outer.get_point(i) - sf::Vector2f{thickness, thickness};
        arr[i*2+1].color = color_outer;
    }

    arr[quality-2].position = arr[0].position;
    arr[quality-2].color = arr[0].color;
    arr[quality-1].position = arr[1].position;
    arr[quality-1].color = arr[1].color;
}

}; // namespace Shape
}; // namespace Calc

