#include <vector>
#include <cstdint>
#include <unordered_map>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "app/globals.hpp"
#include "util/sfml_tools.hpp"
#include "ui/shapes/GlShapes.hpp"
#include "ui/shapes/basicShape.hpp"
#include "app/interface/scene/scene.hpp"
#include "app/interface/res_handler/Resource.hpp"

using namespace sf::Keyboard;
using namespace sf::Mouse;

constexpr sf::Color sim_background{75u,75u,75u};
// size of the gate
constexpr float gate_size = 10;

auto font = Resources.get_font("font_1",RES_DIR"fonts/NerdFonts/HackNerdFontMono-Regular.ttf");
sf::Shader rr_shader;

sf::Text y_{font};
sf::Text x_{font};

constexpr uint32_t quality = 8;
sf::VertexArray c{sf::PrimitiveType::TriangleFan, quality * 4};
sf::VertexArray top_shelf{sf::PrimitiveType::TriangleFan, 4};

// world size
sf::Vector2f size;
// the center of the view port
sf::Vector2f focus_point {0,0};

// info about interactions

// holds the position of the object to be moved, null if there's none
sf::Vector2f* is_dragging = 0;
// type of the thing currently holding
std::string type;

// is draggin
bool left_down;
sf::Vector2f dragg_offset;

// gate vector map
// the Gates contains vector of gate's name,position pair
std::unordered_map<std::string, std::vector<std::pair<std::string,sf::Vector2f>>> Gates;

// temporary buffer
// this holds the order of types
std::vector<std::string> buffer;

void process_in_topshelf_event(const sf::RenderWindow& window, const sf::Vector2f& mousePos) {
    
}

// process user interactions 
void process_in_sim_window_event(const sf::RenderWindow& window, const sf::Vector2f& mousePos, const float zoom_level) {
    auto local_pos = sfml_utils::current_to_localpos(mousePos, size, focus_point, zoom_level);
    // adding new element
    static bool a_down;
    // removing element
    static bool del_down;   

    if (isKeyPressed(Scancode::A)) {
        if (not a_down) {
            Gates["X"].emplace_back("meh",local_pos);
            a_down = 1;
        }
    } else {
        a_down = 0;
    }
    // move the element
    if (isButtonPressed(Button::Left)) {
        // check which gate is bellow the mouse
        for (auto& gate: Gates["X"]) {
            if (is_dragging != 0)
                break;
            if (!left_down and !is_dragging and sf::FloatRect{gate.second, {gate_size,gate_size}}.contains(local_pos)) {
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
    
    // delete an element
    if ((isKeyPressed(Scancode::Delete) or isKeyPressed(Scancode::X))) {
        auto& gates = Gates["X"];
        for (size_t i = 0; i < gates.size(); ++i) {
            if (!del_down and sf::FloatRect{gates[i].second, {gate_size,gate_size}}.contains(local_pos)) {
                auto it = gates.begin() + i;
                gates.erase(it);
                break;
            }
        }
        del_down = 1;
    } else {
        del_down = 0;
    }
}

void process_global_changes(sf::RenderWindow& window) {
    // move the view
    if (isKeyPressed(Scancode::Left))
        focus_point.x -= 1.5;
    if (isKeyPressed(Scancode::Right))
        focus_point.x += 1.5;
    if (isKeyPressed(Scancode::Up))
        focus_point.y -= 1.5;
    if (isKeyPressed(Scancode::Down))
        focus_point.y += 1.5;
}


// horizontall shelf that  you can move
void draw_shelf_items(sf::RenderWindow& window) {
    // bound of the shelf
    // pos x, y        size       x           , y
    // {10.f,10.f}, sf::Vector2f{size.x - 20.f,100.f}

    const auto shelf_size = sf::Vector2f{size.x - 40.f,80.f};
    const unsigned shelf_length = 2000;

    const sf::Vector2f element_size{80,80};
    const float eleme_rad = 20.f;
    // ammount of how much was the view is positined
    // 0 = maxed at the first
    // 255 = at end
    static uint8_t view_percent = 0;
    

    // load shader
    static sf::Shader item_rounded_rect_shader{};
    static bool shad_not_loaded = 1;
    if (shad_not_loaded) {
        if (item_rounded_rect_shader.loadFromFile(RES_DIR"/shader/shape_shader/shade_rounded_rect.frag",sf::Shader::Type::Fragment)) {
            shad_not_loaded = 0;
            item_rounded_rect_shader.setUniform("halfSize", sf::Glsl::Vec2{element_size * 0.5f});
            item_rounded_rect_shader.setUniform("radius", eleme_rad);
        } else {
            fprintf(stderr,"shader doesnt load\n");
            exit(-1);
        }
    }


    sf::RenderTexture shelf{(sf::Vector2u)shelf_size + sf::Vector2u{shelf_length,0}};
    sf::View view;
    shelf.clear(sf::Color{200,200,200});
    sf::VertexArray rect{sf::PrimitiveType::TriangleFan, 4};
    // setting view
    //                         offset    this should move the screen      
    const auto center = sf::Vector2f{shelf_length * (Glob::zoom_scalar / 255.f),0} + shelf_size * 0.5f;
    view.setCenter(center);
    view.setSize(shelf_size);
    shelf.setView(view);

    
    // modes
    // 1
    // rect[0] = {{0,0}              , sf::Color::White, {0,0}              };
    // rect[1] = {{0,element_size.y} , sf::Color::White, {0,element_size.y} };
    // rect[2] = {element_size       , sf::Color::White, element_size       };
    // rect[3] = {{element_size.x, 0}, sf::Color::White, {element_size.x, 0}};
    MEU::GLShapes::set_rect(rect, {}, element_size, sf::Color::White);
    shelf.draw(rect); //, sf::RenderStates(&item_rounded_rect_shader));
    // 2
    //                                   offset
    sf::Vector2f offset = {element_size.x + 10,0};
    // rect[0] = {sf::Vector2f{0,0}               + offset, sf::Color::Red, sf::Vector2f{0,0}              };
    // rect[1] = {sf::Vector2f{0,element_size.y}  + offset, sf::Color::Red, sf::Vector2f{0,element_size.y} };
    // rect[2] = {element_size                    + offset, sf::Color::Red, element_size                   };
    // rect[3] = {sf::Vector2f{element_size.x, 0} + offset, sf::Color::Red, sf::Vector2f{element_size.x, 0}};
    MEU::GLShapes::set_rect(rect, offset, element_size, sf::Color::Red);
    shelf.draw(rect); //, sf::RenderStates(&item_rounded_rect_shader));


    // drawing the shelf to the window
    shelf.display();
    // MEU::GLShapes::set_rect(rect, {20,20}, half_size * 2.f);
    //
    offset = {20,20};
    rect[0] = {{offset}                           , sf::Color::White, {}               };
    rect[1] = {{offset.x,shelf_size.y + offset.y} , sf::Color::White, {0,shelf_size.y} };
    rect[2] = {{shelf_size           + offset}    , sf::Color::White, {shelf_size}     };
    rect[3] = {{shelf_size.x + offset.x, offset.y}, sf::Color::White, {shelf_size.x, 0}};

    // rect[3].texCoords = {0,0};
    // rect[2].texCoords = {half_size.x * 2.f,0};
    // rect[1].texCoords = half_size * 2.f;
    // rect[0].texCoords = {0,half_size.y * 2.f};

    window.draw(rect, sf::RenderStates{&shelf.getTexture()});
}

void draw_main(sf::RenderWindow& window) {
    window.clear(sim_background);

    if (window.hasFocus()) process_global_changes(window);

    // process stuff
    const float zoom_level = 1.f + 3.5f * ((float)Glob::zoom_scalar / (float)UINT8_MAX);
    const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (top_shelf.getBounds().contains(mousePos) and window.hasFocus()) {
        process_in_topshelf_event(window, mousePos);
    } else if (window.hasFocus()) {
        process_in_sim_window_event(window, mousePos, zoom_level);
    }

    MEU::Shape::CreateCircle(c, quality * 4, 10.f, sf::Vector2f{mousePos}, sf::Color{255,255,0});

    y_.setString(std::to_string((int)mousePos.y));
    x_.setString(std::to_string((int)mousePos.x));

    // drawn at the back
    sf::RenderStates sim_render_state;
    sim_render_state.transform = sfml_utils::get_world_transform(focus_point, size, zoom_level);

    {
        auto gate_vertex = sf::VertexArray{sf::PrimitiveType::Triangles};
        for (const auto& gate: Gates["X"]) {
            const sf::Vector2f origin = gate.second;
            gate_vertex.append(sf::Vertex(origin, sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{0,gate_size}, sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{gate_size, gate_size}, sf::Color::White));

            gate_vertex.append(sf::Vertex(origin, sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{gate_size, gate_size}, sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{gate_size, 0}, sf::Color::White));
        }
        window.draw(gate_vertex, sim_render_state);
    }
    sf::RectangleShape d{{10,10}};
    window.draw(d, sim_render_state);

    d.setPosition(size-sf::Vector2f{10,10});
    window.draw(d, sim_render_state);

    window.draw(top_shelf, sf::RenderStates(&rr_shader));
    draw_shelf_items(window);
    window.draw(y_);
    window.draw(x_);
    // put at the front
    window.draw(c);
}

void load_main(sf::RenderWindow& window) {
    size = (sf::Vector2f)window.getSize();

    focus_point = size * 0.5f;

    y_.setPosition({1225.f,5.f});
    x_.setPosition({1225.f,35.f});
    

    // MEU::Shape::CreateRoundedRect(top_shelf,
    //                               quality*4,
    //                               20.f,
    //                               sf::Vector2f{size.x-20.f,100.f},
    //                               sf::Vector2f{10.f,10.f}, sf::Color{200,200,200});
    if (!rr_shader.loadFromFile(RES_DIR"/shader/shape_shader/shade_rounded_rect.frag",sf::Shader::Type::Fragment)) {
        printf("error\n");
        exit(-1);}
    constexpr float r = 25.f;
    rr_shader.setUniform("radius", r);
    rr_shader.setUniform("halfSize", sf::Glsl::Vec2{size.x - 20.f,100.f} * 0.5f);

    MEU::GLShapes::set_rect(top_shelf, {10.f,10.f}, sf::Vector2f{size.x - 20.f,100.f}, sf::Color{200,200,200});
 
    Gates["X"].emplace_back("meh", sf::Vector2f{100,100});
    Gates["X"].emplace_back("me2", sf::Vector2f{100,100 + gate_size});
    
}

