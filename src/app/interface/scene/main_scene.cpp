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

#include "Interpolated/Interpolated.hpp"
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
// Gates["Gate_type"][gate_index] = {game_name, sf::Vector2f{gate_pos_topleft}}
std::unordered_map<std::string, std::vector<std::pair<std::string,sf::Vector2f>>> Gates;

// temporary buffer
// this holds the order of types
std::vector<std::string> buffer;

// top shelf elements
const unsigned shelf_length = 2000;
sf::Vector2f top_shelf_size;
struct Shelf_element{
    // this could tell if its being hovered
    Interpolation::Actuator<int8_t> size = {0, 20, 0.8f, 0.5f, Interpolation::Easing::easeOutElastic};
    uint8_t brightness = 255;

    std::string name = "Elem";
    sf::Vector2f pos = {};

    Shelf_element() = default;
    Shelf_element(std::string n = "Elem", sf::Vector2f p = {}): name{n}, pos{p}{}
};
std::vector<Shelf_element>  shelf_elements;

void process_in_topshelf_event(const sf::RenderWindow& window, const sf::Vector2f mousePos, int* mouse_process_owner, uint8_t* scroll_percent) {
    int& mouse_owner = *mouse_process_owner;
    auto local_pos = mousePos + sf::Vector2f{shelf_length * (*scroll_percent / 255.f) - 20,-20};
    // check if mouse is not on bound of top shelf and top shelf doesnt own, or when window doesnt have focus
    // set hover effect
    for (Shelf_element& elem: shelf_elements) {
        if (sf::FloatRect{elem.pos, {80,80}}.contains(local_pos)) {
            if (elem.size.value == elem.size.value.start) elem.size.setForward();
        } else 
            if (elem.size.value == elem.size.value.end) elem.size.setBackward();
    }

    /*********************************************************************************************/
    if ((!top_shelf.getBounds().contains(mousePos) and mouse_owner != 523) or !window.hasFocus())
        return;

    int zoom_percent_temp = *scroll_percent - Glob::zoom_delta * 2.f;

    if (zoom_percent_temp <= 0)
        *scroll_percent = 0;
    else if (zoom_percent_temp >= 255)
        *scroll_percent = 255;
    else
        *scroll_percent = zoom_percent_temp;

    /***************************************************************************/
    bool event_activated= 0;
    static Shelf_element* selected = 0;

    if (isButtonPressed(Button::Left)) {
        // check which gate is bellow the mouse
        for (auto& elem: shelf_elements) {
            if (selected)
                break;
            if (!left_down and !selected and sf::FloatRect{elem.pos, {80,80}}.contains(local_pos)) {
                selected = &elem;
                selected->brightness = 170;
                break;
            }
        }

        left_down = 1;
        event_activated = 1;
    } else {
        if (selected) selected->brightness = 255;
        selected = 0;
        left_down = 0;
    }

    // set or release ownership
    if (event_activated)
        mouse_owner = 523;
    else
        mouse_owner = 0;
}

// process user interactions
void process_in_sim_window_event(const sf::RenderWindow& window, const sf::Vector2f mousePos, const float zoom_level, int* mouse_process_owner, uint8_t* zoom_percent) {
    auto local_pos = sfml_utils::current_to_viewportpos(mousePos, size, focus_point, zoom_level);
    // adding new element
    static bool a_down;
    // removing element
    static bool del_down;
    int& mouse_owner = *mouse_process_owner;

    if (top_shelf.getBounds().contains(mousePos) and mouse_owner != 1984) return;
    int zoom_percent_temp = 3 * Glob::zoom_delta + *zoom_percent;
    if (zoom_percent_temp <= 0)
        *zoom_percent = 0;
    else if (zoom_percent_temp >= 255)
        *zoom_percent = 255;
    else
        *zoom_percent = zoom_percent_temp;

    bool event_activated = 0;
    if (isKeyPressed(Scancode::A)) {
        if (not a_down) {
            Gates["X"].emplace_back("meh",local_pos);
            a_down = 1;
        }
        event_activated = 1;
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
        event_activated = 1;
    } else {
        is_dragging = 0;
        left_down = 0;
    }
    
    // delete an element
    if (isKeyPressed(Scancode::Delete) or isKeyPressed(Scancode::X)) {
        auto& gates = Gates["X"];
        for (size_t i = 0; i < gates.size(); ++i) {
            if (!del_down and sf::FloatRect{gates[i].second, {gate_size,gate_size}}.contains(local_pos)) {
                auto it = gates.begin() + i;
                gates.erase(it);
                break;
            }
        }
        del_down = 1;
        event_activated = 1;
    } else {
        del_down = 0;
    }
    
    // take ownership or release when needed
    if (event_activated)
        mouse_owner = 1984;
    else
        mouse_owner = 0;
}

void process_global_changes(const sf::RenderWindow& window) {
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
void draw_shelf_items(sf::RenderWindow& window, int* mouse_process_owner, const sf::Vector2f mousePos) {
    // bound of the shelf
    // pos x, y        size       x           , y
    // {10.f,10.f}, sf::Vector2f{size.x - 20.f,100.f}

    const sf::Vector2f element_size{80,80};
    const float eleme_rad = 20.f;
    // ammount of how much was the view is positined
    // 0 = maxed at the first
    // 255 = at end
    static uint8_t view_percent = 0;

    /************************ loading shader **********************/
    static sf::Shader item_rounded_rect_shader{};
    static bool shad_not_loaded = 1;
    if (shad_not_loaded) {
        if (item_rounded_rect_shader.loadFromFile(RES_DIR"/shader/shape_shader/shade_rounded_rect.frag",sf::Shader::Type::Fragment)) {
            shad_not_loaded = 0;
        } else {
            fprintf(stderr,"shader doesnt load\n");
            exit(-1);
        }
    }
    /************************ loading shader **********************/

    // process event
    process_in_topshelf_event(window, mousePos, mouse_process_owner, &view_percent);
    sf::Vector2f shelf_size = top_shelf_size - sf::Vector2f{5,5};
    sf::RenderTexture shelf{(sf::Vector2u)shelf_size + sf::Vector2u{shelf_length,0}};
    shelf.clear(sf::Color{255,255,255,0});
    
    /*********************** drawing elements *********************/
    static sf::Font text_font{RES_DIR"/fonts/NerdFonts/HackNerdFontMono-Regular.ttf"};
    sf::Text text{text_font};
    text.setFillColor(sf::Color::Black);

    sf::VertexArray rect{sf::PrimitiveType::TriangleFan, 4};
    // TODO:
    // need to make this load specific texture on each
    for (const auto& elem: shelf_elements) {
        item_rounded_rect_shader.setUniform("halfSize", sf::Glsl::Vec2{(element_size * (1.f + elem.size / 255.f)) * 0.5f});
        item_rounded_rect_shader.setUniform("radius", eleme_rad);
        const uint8_t col = elem.brightness;
        MEU::GLShapes::set_rect(rect,
                elem.pos + element_size * 0.5f - element_size * 0.5f * (1.f + elem.size / 255.f),
                element_size * (1.f + elem.size / 255.f),
                sf::Color{col, col, col});
        shelf.draw(rect, sf::RenderStates(&item_rounded_rect_shader));

        text.setString(elem.name);
        text.setPosition(element_size * 0.5f - text.getLocalBounds().size * 0.5f + elem.pos);
        shelf.draw(text);
    }
    /*********************** drawing elements *********************/

    /******************* drawing shelf to window ******************/
    const auto texture_offset = sf::Vector2f{shelf_length * (view_percent / 255.f),0};
    const sf::Vector2f offset = {15,15};
    rect[0] = {{offset}                           , sf::Color::White, {texture_offset}                                   };
    rect[1] = {{offset.x, shelf_size.y + offset.y}, sf::Color::White, {texture_offset.x, shelf_size.y + texture_offset.y}};
    rect[2] = {{shelf_size + offset}              , sf::Color::White, {shelf_size + texture_offset}                      };
    rect[3] = {{shelf_size.x + offset.x, offset.y}, sf::Color::White, {shelf_size.x + texture_offset.x, texture_offset.y}};

    shelf.display();
    window.draw(rect, sf::RenderStates{&shelf.getTexture()});
    /******************* drawing shelf to window ******************/
}

void draw_main(sf::RenderWindow& window) {
    window.clear(sim_background);

    if (window.hasFocus()) process_global_changes(window);

    // process stuff
    static uint8_t zoom_percent = 0;
    const float zoom_level = 1.f + 3.5f * ((float)zoom_percent / (float)UINT8_MAX);
    const auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // a event processor can own this to make sure only that process could work
    static int mouse_process_owner = 0;

    if (window.hasFocus())
        process_in_sim_window_event(window, mousePos, zoom_level, &mouse_process_owner, &zoom_percent);

    MEU::Shape::CreateCircle(c, quality * 4, 10.f, sf::Vector2f{mousePos}, sf::Color{255,255,0});

    y_.setString(std::to_string((int)mousePos.y));
    x_.setString(std::to_string((int)mousePos.x));

    // drawn at the back
    sf::RenderStates sim_render_state;
    sim_render_state.transform = sfml_utils::get_world_transform(focus_point, size, zoom_level);

    {
        auto gate_vertex = sf::VertexArray{sf::PrimitiveType::Triangles};
        gate_vertex.resize(50);
        // TODO:
        // add ways to make this load specific texture for
        // each gate and each circuit type
        for (const auto& gate: Gates["X"]) {
            const sf::Vector2f origin = gate.second;
            gate_vertex.append(sf::Vertex(origin                                     , sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{0,gate_size}         , sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{gate_size, gate_size}, sf::Color::White));

            gate_vertex.append(sf::Vertex(origin                                     , sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{gate_size, gate_size}, sf::Color::White));
            gate_vertex.append(sf::Vertex(origin + sf::Vector2f{gate_size, 0}        , sf::Color::White));
        }
        window.draw(gate_vertex, sim_render_state);
        gate_vertex.clear();
    }
    sf::RectangleShape d{{10,10}};
    window.draw(d, sim_render_state);

    d.setPosition(size-sf::Vector2f{10,10});
    window.draw(d, sim_render_state);

    window.draw(top_shelf, sf::RenderStates(&rr_shader));
    draw_shelf_items(window, &mouse_process_owner, mousePos);
    window.draw(y_);
    window.draw(x_);
    // put at the front
    window.draw(c);
}

void load_main(sf::RenderWindow& window) {
    size = (sf::Vector2f)window.getSize();

    focus_point = size * 0.5f;

    y_.setPosition({1225.f - 30,5.f});
    x_.setPosition({1225.f - 30,35.f});
    
    if (!rr_shader.loadFromFile(RES_DIR"/shader/shape_shader/shade_rounded_rect.frag",sf::Shader::Type::Fragment)) {
        printf("error\n");
        exit(-1);}

    constexpr float r = 25.f;
    top_shelf_size = sf::Vector2f{size.x - 20.f,100.f};
    rr_shader.setUniform("halfSize", sf::Glsl::Vec2{top_shelf_size} * 0.5f);
    rr_shader.setUniform("radius", r);

    MEU::GLShapes::set_rect(top_shelf, {10.f,10.f}, top_shelf_size, sf::Color{200,200,200});
 
    Gates["X"].emplace_back("meh", sf::Vector2f{100,100});
    Gates["X"].emplace_back("me2", sf::Vector2f{100,100 + gate_size});

    shelf_elements.emplace_back("1", sf::Vector2f{5,5});
    shelf_elements.emplace_back("2", sf::Vector2f{90,5});
}

