#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>
#include <vector>


/* object that generate a point with angle theta
 * plus i't from the 0 with derivetive of da*/
struct CircleGenerator{
  const uint32_t quality;
  const float radius = 0;
  // derivetive of angle
  const float da;
  CircleGenerator(float radius_, uint32_t quality_);
  // return i't point with option to rotate using theta
  sf::Vector2f get_point(uint32_t i);
};
/* generateRoundedRect - Pupulate a pree alocated vertex array with points ressembles a rounded rectangle
 * arguments:
 *    arr: VertexArray - arrat that holds the points
 *    quality: uint32_t - unsigned 32 bit int that holds the size of the VertexArray and tells the quality of the rounded rectangle
 *    position: Vector2f - vector that hols 2 floats which is the top-left position of the rounded rectangle relative to the window*/
void generateRoundedRect(sf::VertexArray& arr,
                         uint32_t quality,
                         sf::Vector2f position,
                         float height,
                         float width,
                         float radius = 0.0,
                         sf::Color color = sf::Color::Red);
/* generateCircle - Pupulate a pree alocated vertex array with points ressembles a circle
 * arguments:
 *    arr: VertexArray - array that holds the points
 *    quality: uint32_t - unsigned 32 bit int that holds the size of the VertexArray and tells the quality of the circle
 *    position: Vector2f - vector that holds 2 float which is the position of the circle relative to the window
 *    radius: float - distance from the origin/position
 *    theta: float = 0.0 - agnel offset
 *    color: Color = White - color will be drawn to the circle*/
void generateCircle(sf::VertexArray& arr,
                    uint32_t quality,
                    sf::Vector2f position,
                    float radius,
                    sf::Color color = sf::Color::White);

sf::VertexArray* zip(std::vector<sf::VertexArray&>& args);







