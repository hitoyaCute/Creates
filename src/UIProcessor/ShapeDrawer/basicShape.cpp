#include <cmath>
#include <cstdint>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "Shapes.hpp"



CircleGenerator::CircleGenerator(float radius_, uint32_t quality_) : 
  radius{radius_},
  quality{quality_},
  da{(2.0f * sf::priv::pi) / quality} {};

sf::Vector2f CircleGenerator::get_point(uint32_t i, float theta) {
  float angle = da * static_cast<float>(i);
  return {radius * sf::Vector2f{cosf(angle+theta), sinf(angle+theta)}};
}

// function that pupulate a predefined vertex array with rounded rectangle
void generateRoundedRect(sf::VertexArray& arr, sf::Vector2f position, float height, float width, uint32_t quality, float theta, float radius, sf::Color color) {
  CircleGenerator generator{radius, quality * 4};
    
  const sf::Vector2f centers[4]{
    {width - radius, height - radius},
    {radius        , height - radius},
    {radius        , radius},
    {width - radius, radius}
  };


  for (uint32_t i{0}; i < (quality * 4); i++) {
    const sf::Vector2f point{
      [&]()-> const sf::Vector2f {
      const uint32_t corner_idx{i / quality*4};
      return centers[corner_idx] + generator.get_point(i - corner_idx, theta);
    }()};
    arr[i/4].position = position + point;

    arr[i/4].color = color;
  }
}
// populate a vertex array with circle
void generateCircle(sf::VertexArray &arr, sf::Vector2f position, float radius, uint32_t quality, float theta, sf::Color color) {
  CircleGenerator generator{radius, quality};
  for (uint32_t i{0}; i < quality; i++) {
    arr[i].position = position + generator.get_point(i, theta);

    arr[i].color = color;
  }
}

