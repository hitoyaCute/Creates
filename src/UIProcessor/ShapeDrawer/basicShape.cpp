#include <cmath>
#include <cstdint>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "UIProcessor/ShapeDrawer/Shapes.hpp"



CircleGenerator::CircleGenerator(float radius_, uint32_t quality_) : 
  radius{radius_},
  quality{quality_},
  da{(2.0f * sf::priv::pi) / quality} {};

sf::Vector2f CircleGenerator::get_point(uint32_t i) {
  float angle = da * static_cast<float>(i);
  return {radius * sf::Vector2f{cosf(angle), sinf(angle)}};
}

// function that pupulate a predefined vertex array with rounded rectangle
// please!!! dont make the radius larger than {width, height}/2
void generateRoundedRect(sf::VertexArray& arr,
                         uint32_t quality,
                         sf::Vector2f position,
                         float height,
                         float width,
                         float radius,
                         sf::Color color) {
  CircleGenerator generator{radius, quality};
    
  const sf::Vector2f centers[4]{
    {width - radius, height - radius},
    {radius        , height - radius},
    {radius        , radius},
    {width - radius, radius}
  };


  for (uint32_t i{0}; i < quality; i++) {
    const auto point{
      [&]()-> const sf::Vector2f {
        const uint32_t corner_idx{i / (quality/4)};
        return centers[corner_idx] + generator.get_point(i);
    }()};

    arr[i].position = position + point;

    arr[i].color = color;
  }
}
// populate a vertex array with circle
void generateCircle(sf::VertexArray &arr,
                    uint32_t quality,
                    sf::Vector2f position,
                    float radius,
                    sf::Color color) {
  CircleGenerator generator{radius, quality};
  for (uint32_t i{0}; i < quality; i++) {
    arr[i].position = position + generator.get_point(i);

    arr[i].color = color;
  }
}

