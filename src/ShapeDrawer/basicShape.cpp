#include <cmath>
#include <cstdint>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "Shapes.hpp"


CircleGenerator::CircleGenerator(float radius_, uint32_t quality_) {
  radius = radius_;
  quality = quality_;
  float da = 2.0 * sf::priv::pi / static_cast<float>(quality);
  
}

sf::Vector2f CircleGenerator::get_point(uint32_t i, float theta) {
  float angle = da * static_cast<float>(i);
  return {radius * sf::Vector2f{cosf(angle+theta), sinf(angle+theta)}};
}

void generateRoundedRect(sf::VertexArray& arr, sf::Vector2f position, float height, float width, uint32_t quality, float theta, float range, sf::Color color) {
  CircleGenerator generator{range, quality};
  height -= range;
  width -= range;


  
}

void generateCircle(sf::VertexArray &arr, sf::Vector2f position, float radius, uint32_t quality, float theta, sf::Color color) {
  CircleGenerator generator{radius, quality};
  for (uint32_t i = 1; i < quality; i++) {
    arr[i].position = position + generator.get_point(i, theta);

    arr[i].color = color;
  }
}

