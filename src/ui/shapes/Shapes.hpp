#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>


/* object that generate a point with angle theta
 * plus i't from the 0 with derivetive of da*/
struct CircleGenerator{
  // derivetive of angle
  const float da;
  const uint32_t quality;
  const float radius = 0.f;
  CircleGenerator(float radius_, uint32_t quality_);
  // return i't point with option to rotate using theta
  const sf::Vector2f get_point(uint32_t i);
};

struct RoundedRectGenerator {
  const float da;
  const uint32_t quality;
  const sf::Vector2f size;
  const float radius = 0.f;
  const sf::Vector2f centers[4];
  CircleGenerator generator;
  RoundedRectGenerator(sf::Vector2f size_, float arc_, uint32_t quality_);
  const sf::Vector2f get_point(uint32_t i);

};




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


// this will make the VertexArray x2 on its current size
// where arch 
void generateRoundedBorder(sf::VertexArray &arr,
                            uint32_t quality,
                            sf::Vector2f position,
                            sf::Vector2f size,
                            float range = 1.f,
                            float arc = 0.1f,
                            sf::Color = sf::Color{255u,255u,255u});

// populate a vertex array with points of a rounded rectangle
// params:
//    arr: VertexArray - the array that will be populated
//    quality: unsigned int - number of vertecies on the array
//    position: Vector2f - the position on where the shape will be drawn
//    size: Vector2f - size
//    arcRatio: float - the arc's ratio to the rectangle's size
//    color: Color - color of the shape
void generateRoundedRect(sf::VertexArray& arr,
                         uint32_t quality,
                         sf::Vector2f position,
                         sf::Vector2f size,
                         float arcRatio,
                         sf::Color color = sf::Color{122u,122u,122u});

void vzip(sf::VertexArray &first, sf::VertexArray &second, sf::VertexArray &output, uint32_t outpSize);
