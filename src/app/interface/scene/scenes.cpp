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


// where the texture will be laid
sf::VertexArray sim_window{sf::PrimitiveType::Triangles, 6};
// super big texture
sf::RenderTexture sim_window_render;

sf::Vector2f size;

inline void draw_intro(sf::RenderWindow& win) {
}

inline void draw_main(sf::RenderWindow& window) {
    window.clear(sf::Color {75u,75u,75u});
    sim_window_render.clear(sf::Color{255,255,255,0});

    const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    MEU::Shape::CreateCircle(c, quality * 4, 10.f, sf::Vector2f{mousePos}, sf::Color{255,255,0});
    y_.setString(std::to_string((int)mousePos.y));
    x_.setString(std::to_string((int)mousePos.x));

    sf::CircleShape a{50};
    a.setFillColor(sf::Color::Blue);
    a.setPosition(mousePos);

    /// zoom

    sf::View sim_window_view{};
    sim_window_view.setSize(size);
    sim_window_view.zoom(((float)Glob::zoom_scalar) / 255.f);

    sim_window_render.setView(sim_window_view);

    sim_window_render.draw(a);
    sim_window_render.display();

    sf::RenderStates sim_render_state;
    sim_render_state.texture = &sim_window_render.getTexture();
    // drawn at the back
    window.draw(sim_window, sim_render_state);

    window.draw(top_shelf);
    window.draw(y_);
    window.draw(x_);
    // put at the front
    window.draw(c);
}


void load_scene(sf::RenderWindow& window, int scene) {
    size = (sf::Vector2f)window.getSize();
    sim_window_render = {(sf::Vector2u)size};
    y_.setPosition({25.f,5.f});
    x_.setPosition({25.f,35.f});

    MEU::Shape::CreateRoundedRect(top_shelf,
                                  quality*4,
                                  20.f,
                                  sf::Vector2f{size.x-20.f,100.f},
                                  sf::Vector2f{10.f,10.f}, sf::Color{200,200,200});

    const auto win_size = (sf::Vector2f)window.getSize();
    // sim_window_view.setCenter(win_size/2.f);
    sf::Texture text = sim_window_render.getTexture();

    
    auto temp = (sf::Vector2f)text.getSize();
    
    sim_window[0].texCoords = {0,0};
    sim_window[0].position = {0,0};
    sim_window[1].texCoords = {temp.x, 0};
    sim_window[1].position = {win_size.x, 0};
    sim_window[2].texCoords = temp;
    sim_window[2].position = win_size;

    sim_window[3].texCoords = {0,0};
    sim_window[3].position = {0,0};
    sim_window[4].texCoords = {0, temp.y};
    sim_window[4].position = {0, win_size.y};
    sim_window[5].texCoords = temp;
    sim_window[5].position = win_size;

    
    sfml_utils::set_fill_color(sim_window);
}


void display_scene(sf::RenderWindow &window, int scene) {
    if (scene == 0) {
        draw_intro(window);
    } else if(scene == 1) {
        draw_main(window);
    }
}
