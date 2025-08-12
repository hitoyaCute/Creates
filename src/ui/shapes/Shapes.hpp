#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>



namespace Creates {

struct CircleGenerator{
  const float da; // the delta a 
  const float radius;
  
  CircleGenerator(uint32_t quality_, float radius_);

  // finction that returns the i'th point of the circle
  const sf::Vector2f get_point(uint32_t i);
};

struct RoundedRectGenerator {
  const float da;
  const float radius;
  const uint32_t quality;
  const sf::Vector2f size;
  const sf::Vector2f centers[4];

  RoundedRectGenerator(sf::Vector2f size_,
                       float radius_,
                       uint32_t quality_);

  // method that returns the ith point of the rounded rectangle
  sf::Vector2f get_point(uint32_t i);
};

struct RoundedRectBorderGenerator {

};

// populate a VertexArray with points of a circle
// args:
// \ \ VertexArray arr: the array will be populated
// \ \ uint32_t quality: the ammount of vertex
// \ \ float radius: the radius of the circle
// \ \ Vector2f pos: position of the origin on where to draw the shape
// \ \ Color color: what color to give the circle
void CreateCircle(sf::VertexArray arr,
                 uint32_t quality,
                 float radius,
                 sf::Vector2f pos,
                 sf::Color color = sf::Color{50,50,50});
// populate a VertexArray with points of a rounded rectangle
// args:
// \ \ VertexArray arr: the array will be populated
// \ \ uint32_t quality: the ammount of vertex
// \ \ float radius: the corner radius
// \ \ Vector2f size: the size of the whole rectangle+radius
// \ \ Vector2f pos: position of the origin on where to draw the shape
// \ \ Color color: what color to give the rounded rect
void CreateRoundedRect(sf::VertexArray arr,
                       uint32_t quality,
                       float radius,
                       sf::Vector2f size,
                       sf::Vector2f pos,
                       sf::Color color = sf::Color{50,50,50});
// populate a VertexArray with points of a rounded rectangle with border
// args:
// \ \ VertexArray arr: the array will be populated
// \ \ uint32_t quality: the ammount of vertex
// \ \ float corner_radius: the corner radius
// \ \ float border_range: the distance of where the outer rect will sit
// \ \ Vector2f size: the size of the whole rectangle+radius
// \ \ Vector2f pos: position of the origin on where to draw the shape
// \ \ Color color: what color to give the rounded rect
void CreateRoundedRectBorder(sf::VertexArray arr,
                             uint32_t quality,
                             float corner_radius,
                             float border_range,
                             sf::Vector2f size,
                             sf::Vector2f pos,
                             sf::Color color = sf::Color{50,50,50});


}; // Creates



