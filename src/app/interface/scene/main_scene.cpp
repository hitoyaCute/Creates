#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdint>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>


#include "app/globals.hpp"
// #include "util/sfml_tools.hpp"
// #include "ui/shapes/GlShapes.hpp"
#include "ui/shapes/basicShape.hpp"
#include "app/interface/scene/scene.hpp"
#include "app/interface/res_handler/Resource.hpp"

auto font = Resources.get_font("font_1",RES_DIR"fonts/NerdFonts/HackNerdFontMono-Regular.ttf");

sf::Text y_{font};
sf::Text x_{font};

constexpr uint32_t quality = 8;
sf::VertexArray c{sf::PrimitiveType::TriangleFan, quality * 4};
sf::VertexArray top_shelf{sf::PrimitiveType::TriangleFan, quality*4};

// world size
sf::Vector2f size;
// the center of the view port
sf::Vector2f focus_point {0,0};

// camera transform
constexpr sf::Transform get_world_transform(const sf::Vector2f& focus_point, const sf::Vector2f& world_size, const float& zoom) {
    sf::Transform transform;
    transform.translate(world_size/2.f);
    transform.scale({zoom, zoom});
    // transform.translate(world_size * zoom);
    transform.translate(-focus_point);
    return transform;
}

// position trasform
// can be used to get mouse position from render to world
inline sf::Vector2f current_to_localpos(const sf::Vector2f& pos, const sf::Vector2f& current_size, const sf::Vector2f& focus_point, const float& zoom) {
    return get_world_transform(focus_point, current_size, zoom).getInverse().transformPoint(pos);
}

void draw_main(sf::RenderWindow& window) {
    window.clear(sf::Color {75u,75u,75u});

    const float zoom_level = ((float)Glob::zoom_scalar / (float)UINT8_MAX);
    const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    MEU::Shape::CreateCircle(c, quality * 4, 10.f, sf::Vector2f{mousePos}, sf::Color{255,255,0});
    y_.setString(std::to_string((int)mousePos.y));
    x_.setString(std::to_string((int)mousePos.x));

    sf::CircleShape a{50};
    a.setFillColor(sf::Color::Blue);
    a.setOrigin(a.getGlobalBounds().getCenter());
    a.setPosition(current_to_localpos(mousePos, size, focus_point, zoom_level));

    sf::RectangleShape d{{10,10}};

    // drawn at the back
    sf::RenderStates sim_render_state;
    sim_render_state.transform = get_world_transform(focus_point, size, zoom_level);
    window.draw(d, sim_render_state);

    d.setPosition(size-sf::Vector2f{10,10});
    window.draw(d, sim_render_state);
    window.draw(a, sim_render_state);

    window.draw(top_shelf);
    window.draw(y_);
    window.draw(x_);
    // put at the front
    window.draw(c);
}

void load_main(sf::RenderWindow& window) {
    size = (sf::Vector2f)window.getSize();

    focus_point = size * 0.5f;

    y_.setPosition({25.f,5.f});
    x_.setPosition({25.f,35.f});

    MEU::Shape::CreateRoundedRect(top_shelf,
                                  quality*4,
                                  20.f,
                                  sf::Vector2f{size.x-20.f,100.f},
                                  sf::Vector2f{10.f,10.f}, sf::Color{200,200,200});  
}
