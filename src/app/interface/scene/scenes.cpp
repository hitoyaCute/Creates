#include "app/globals.hpp"
#include "app/interface/res_handler/Resource.hpp"
#include "app/interface/scene/scene.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>


#include "ui/shapes/GlShapes.hpp"
#include "ui/shapes/basicShape.hpp"
#include "util/sfml_tools.hpp"

auto font = Resources.get_font("font_1",RES_DIR"fonts/NerdFonts/HackNerdFontMono-Regular.ttf");

sf::Text y_{font};
sf::Text x_{font};

const uint32_t quality = 8;
sf::VertexArray c{sf::PrimitiveType::TriangleFan, quality * 4};
sf::VertexArray top_shelf{sf::PrimitiveType::TriangleFan, quality*4};

sf::Vector2f size;

void draw_intro(sf::RenderWindow& win) {
}

void draw_main(sf::RenderWindow& window) {
    window.clear(sf::Color {75u,75u,75u});

    const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    MEU::Shape::CreateCircle(c, quality * 4, 10.f, sf::Vector2f{mousePos}, sf::Color{255,255,0});
    y_.setString(std::to_string((int)mousePos.y));
    x_.setString(std::to_string((int)mousePos.x));

    sf::CircleShape a{50};
    a.setFillColor(sf::Color::Blue);
    a.setPosition(mousePos);


    sf::RenderStates sim_render_state;
    sf::Transform t{};
    t.scale({(float)Glob::zoom_scalar/255.f, (float)Glob::zoom_scalar/255.f});
    sim_render_state.transform = t;
    // drawn at the back
    window.draw(a, sim_render_state);

    window.draw(top_shelf);
    window.draw(y_);
    window.draw(x_);
    // put at the front
    window.draw(c);
}


void load_scene(sf::RenderWindow& window, int scene) {
    size = (sf::Vector2f)window.getSize();
    y_.setPosition({25.f,5.f});
    x_.setPosition({25.f,35.f});

    MEU::Shape::CreateRoundedRect(top_shelf,
                                  quality*4,
                                  20.f,
                                  sf::Vector2f{size.x-20.f,100.f},
                                  sf::Vector2f{10.f,10.f}, sf::Color{200,200,200});
}


void display_scene(sf::RenderWindow &window, int scene) {
    if (scene == 0) {
        draw_intro(window);
    } else if(scene == 1) {
        draw_main(window);
    }
}
