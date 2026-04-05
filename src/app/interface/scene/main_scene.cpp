#include <vector>
#include <cstdint>
#include <unordered_map>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "app/globals.hpp"
#include "util/sfml_tools.hpp"
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

// info about interactions

// holds the position of the object to be moved, null if there's none
sf::Vector2f* is_dragging = 0;
std::string type;
bool left_down;
sf::Vector2f dragg_offset;


// gate vector map
// the Gates contains vector of gate's name,position pair
std::unordered_map<std::string, std::vector<std::pair<std::string,sf::Vector2f>>> Gates;

// temporary buffer
// this holds the order of types
std::vector<std::string> buffer;

void draw_main(sf::RenderWindow& window) {
    window.clear(sf::Color {75u,75u,75u});

    const float zoom_level = 1 + ((float)Glob::zoom_scalar / (float)UINT8_MAX);
    const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    auto local_pos = sfml_utils::current_to_localpos(mousePos, size, focus_point, zoom_level);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        // check which gate is bellow the mouse
        for (auto& gate: Gates["X"]) {
            if (is_dragging != 0)
                break;
            if (!left_down and !is_dragging and sf::FloatRect{gate.second, {50,50}}.contains(local_pos)) {
                is_dragging = &gate.second;
                dragg_offset = gate.second - local_pos;
                break;
            }
        }

        if (is_dragging != nullptr)
            *is_dragging = local_pos + dragg_offset;
        left_down = 1;
    } else {
        is_dragging = 0;
        left_down = 0;
    }
    // move the view
    using namespace sf::Keyboard;

    if (isKeyPressed(Scancode::Left))
        focus_point.x -= 1.5;
    if (isKeyPressed(Scancode::Right))
        focus_point.x += 1.5;
    if (isKeyPressed(Scancode::Up))
        focus_point.y -= 1.5;
    if (isKeyPressed(Scancode::Down))
        focus_point.y += 1.5;

    MEU::Shape::CreateCircle(c, quality * 4, 10.f, sf::Vector2f{mousePos}, sf::Color{255,255,0});
    y_.setString(std::to_string((int)mousePos.y));
    x_.setString(std::to_string((int)mousePos.x));

    // drawn at the back
    sf::RenderStates sim_render_state;
    sim_render_state.transform = sfml_utils::get_world_transform(focus_point, size, zoom_level);

    for (const auto& gate: Gates["X"]) {
        auto d = sf::RectangleShape{{50,50}};
        d.setPosition(gate.second);
        window.draw(d, sim_render_state);
    }

    sf::RectangleShape d{{10,10}};
    window.draw(d, sim_render_state);

    d.setPosition(size-sf::Vector2f{10,10});
    window.draw(d, sim_render_state);

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

    Gates["X"].emplace_back("meh", sf::Vector2f{100,100});
    Gates["X"].emplace_back("me2", sf::Vector2f{100,150});
}

