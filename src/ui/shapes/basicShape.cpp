#include <SFML/Graphics/PrimitiveType.hpp>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <stdexcept>
#include "Shapes.hpp"



CircleGenerator::CircleGenerator(float radius_, uint32_t quality_) : 
  radius{radius_},
  quality{quality_},
  da{(2.0f * 3.1415927f) / quality_} {};

const sf::Vector2f CircleGenerator::get_point(uint32_t i) {
  float angle = da * static_cast<float>(i);
  return {radius * sf::Vector2f{cosf(angle), sinf(angle)}};
}


RoundedRectGenerator::RoundedRectGenerator(sf::Vector2f size_, float arc_, uint32_t quality_):
  quality{quality_ - 2u},
  da{(2.f * sf::priv::pi) / quality_},
  radius{((size_.x + size_.y) / 2) * arc_},
  size{size_},
  generator{radius, quality_},
  centers{
    {size.x - radius, size.y - radius},
    {radius         , size.y - radius},
    {radius         , radius},
    {size.x - radius, size.y - radius}
  }{};

const sf::Vector2f RoundedRectGenerator::get_point(uint32_t i) {
  const uint32_t corner_idx(i / (quality/4));
  return centers[corner_idx] + generator.get_point((float)i);
}


void _generateRoundedRect(sf::VertexArray &arr, uint32_t quality, sf::Vector2f position, sf::Vector2f size, float arcRatio ,sf::Color) {
  if (quality % 4 != 0) {
    throw std::runtime_error("rounded rectangle has to have quality divisible by 4 to have each size equal ammount of vertex(or vertecies)");
  }

  RoundedRectGenerator(size, arcRatio, quality);
}

// function that pupulate a predefined vertex array with rounded rectangle
// please!!! dont make the radius larger than {width, height}/2
void generateRoundedRect(sf::VertexArray& arr,
                         uint32_t quality,
                         sf::Vector2f position,
                         sf::Vector2f size,
                         float arcRatio,
                         sf::Color color) {
  if (quality % 4 != 0) {
    throw std::runtime_error("rounded rectangle has to have quality divisible by 4 to have each size equal ammount of vertex(or vertecies)");
  }
  const float radius{((size.x + size.y) / 2.f) * arcRatio};
  CircleGenerator generator = CircleGenerator {radius, quality -4};

  const sf::Vector2f centers[4] {
    {size.x - radius, size.y - radius},
    {radius         , size.y - radius},
    {radius         , radius},
    {size.x - radius, radius}
  };


  for (uint32_t i{0}; i < quality; i++) {
    const auto point{
      [&]()-> const sf::Vector2f {
        const uint32_t corner_idx{i / (quality/4)};
        return centers[corner_idx] + generator.get_point(i - corner_idx);
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

void generateRoundedBorder(sf::VertexArray &arr,
                            uint32_t quality,
                            sf::Vector2f position,
                            sf::Vector2f size,
                            float range,
                            float arch,
                            sf::Color color) {
  if ((quality & 8) != 0){
    throw std::runtime_error("rounded rectangle border has to have quality divisible by 8");
  };
  sf::VertexArray inner{sf::PrimitiveType::Points, quality/2u};
  sf::VertexArray outer{sf::PrimitiveType::Points, quality/2u};

  generateRoundedRect(inner, quality/2u, position, size, arch);
  generateRoundedRect(outer, quality/2u, (position - sf::Vector2f{range,range}), (size + sf::Vector2f{range*2.f,range*2.f}), arch);
  vzip(inner, outer, arr, quality);
}

void vzip(sf::VertexArray &first, sf::VertexArray &second, sf::VertexArray &output, uint32_t outpSize) {
  for (uint32_t i{0}; i < outpSize; i++) {
    uint32_t ith{(i/2)};
    if ((i & 1) == 0) {
      output[i] = first[ith];
    } else {
      output[i] = second[ith];
    }
  }
}





