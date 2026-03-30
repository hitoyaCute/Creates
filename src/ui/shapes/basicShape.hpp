#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace Calc {
namespace Shape {

struct CircleGenerator {
    const float da; // the delta a 
    const float radius;
    
    CircleGenerator(const uint32_t quality_, const float radius_);

    // finction that returns the i'th point of the circle
    constexpr sf::Vector2f get_point(const uint32_t i) const;
};

struct RoundedRectGenerator {
    const float da; // 
    const float radius;
    const uint32_t quality;
    const sf::Vector2f size;
    const sf::Vector2f centers[4];

    RoundedRectGenerator(const sf::Vector2f& size_,
                         const float radius_,
                         const uint32_t quality_);

    // method that returns the ith point of the rounded rectangle
    constexpr sf::Vector2f get_point(const uint32_t i) const;

};

// populate a VertexArray with points of a circle
// args:
// \ \ VertexArray arr: the array will be populated
// \ \ uint32_t quality: the ammount of vertex
// \ \ float radius: the radius of the circle
// \ \ Vector2f pos: position of the origin on where to draw the shape
// \ \ Color color: what color to give the circle
void CreateCircle(sf::VertexArray& arr,
                 const uint32_t quality,
                 const float radius,
                 const sf::Vector2f& pos,
                 const sf::Color& color = sf::Color{50,50,50});
// populate a VertexArray with points of a rounded rectangle
// args:
// \ \ VertexArray arr: the array will be populated
// \ \ uint32_t quality: the ammount of vertex
// \ \ float radius: the corner radius
// \ \ Vector2f size: the size of the whole rectangle+radius
// \ \ Vector2f pos: position of the origin on where to draw the shape
// \ \ Color color: what color to give the rounded rect
void CreateRoundedRect(sf::VertexArray& arr,
                       const uint32_t quality,
                       const float radius,
                       const sf::Vector2f& size,
                       const sf::Vector2f& pos,
                       const sf::Color& color = sf::Color{255,255,255});
// populate a VertexArray with points of a rounded rectangle with border
// args:
// \ \ VertexArray arr: the array will be populated
// \ \ uint32_t quality: the ammount of vertex
// \ \ float corner_radius: the corner radius
// \ \ float border_range: the distance of where the outer rect will sit
// \ \ Vector2f size: the size of the whole rectangle+radius
// \ \ Vector2f pos: position of the origin on where to draw the shape
// \ \ Color color: what color to give the rounded rect
void CreateRoundedRectBorder(sf::VertexArray& arr,
                             const uint32_t quality,
                             const float radius,
                             const float thickness,
                             const sf::Vector2f& size,
                             const sf::Vector2f& pos,
                             const sf::Color& color_inner = sf::Color{50,50,50},
                             const sf::Color& color_outer = sf::Color{});
}; // namespace Shapes
}; // napespace Calc
