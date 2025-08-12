#include <cmath>
#include <cstdint>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Shapes.hpp"

namespace Creates {

///// generators

CircleGenerator::CircleGenerator(uint32_t quality_, float radius_):
  radius{radius_},
  da{(2.0f * sf::priv::pi) / quality_}{};

const sf::Vector2f CircleGenerator::get_point(uint32_t i) {
  const float angle = da * static_cast<float>(i);
  return {radius * sf::Vector2f{cosf(angle), sinf(angle)}};
}

RoundedRectGenerator::RoundedRectGenerator(sf::Vector2f size_, float radius_, uint32_t quality_):
  size{size_},
  radius{radius_},
  quality{quality_},
  da{(2.0f * sf::priv::pi) / (quality_-4)},
  centers{
    {size_.x - radius_, size_.y - radius_},
    {radius_          , size_.y - radius_},
    {radius_          , radius_},
    {size_.x - radius_, radius_}
  }{}

sf::Vector2f RoundedRectGenerator::get_point(uint32_t i) {
  const uint32_t idx{i / ((quality-4) / 4)};
  const float angle = da * (float)(i-idx);
  return centers[idx] + (radius * sf::Vector2f{cosf(angle), sinf(angle)});
}

///// functions


void CreateCircle(sf::VertexArray arr,
                  uint32_t quality,
                  float radius,
                  sf::Vector2f pos,
                  sf::Color color) {
  CircleGenerator generator{quality, radius};
  for (uint32_t i{0}; i < quality; i++) {
    arr[i].position = pos + generator.get_point(i);
/*     std::cout << "y: " << arr[i].position.y << " x: " << arr[i].position.x << std::endl; */
    arr[i].color = color;
  }
}

void CreateRoundedRect(sf::VertexArray arr,
                       uint32_t quality,
                       float radius,
                       sf::Vector2f size,
                       sf::Vector2f pos,
                       sf::Color color) {
  RoundedRectGenerator generator{size, radius, quality};
  for (uint32_t i{0}; i < quality; i++) {
    arr[i].position = pos + generator.get_point(i);
    arr[i].color = color;
  }
}


}; // Creates






