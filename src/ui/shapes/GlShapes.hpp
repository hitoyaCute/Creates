#pragma once
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <filesystem>
using std::filesystem::path;


// autor's developer initials
namespace MEU {
namespace GLShapes {
    
    inline void set_rect(sf::VertexArray& va, const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& col = sf::Color::White) {
        const sf::Vector2f half = size * 0.5f;
        const sf::Vector2f center = pos + half;

        va[0] = {center + sf::Vector2f{-half.x, -half.y}, col, {-half.x, -half.y}};
        va[1] = {center + sf::Vector2f{ half.x, -half.y}, col, { half.x, -half.y}};
        va[2] = {center + sf::Vector2f{ half.x,  half.y}, col, { half.x,  half.y}};
        va[3] = {center + sf::Vector2f{-half.x,  half.y}, col, {-half.x,  half.y}};
    }
    inline void draw_rounded_rect(sf::RenderTarget& target, const sf::Vector2f& pos, const sf::Vector2f& size, const float radius, const sf::Color& col = sf::Color::White) {
        static sf::Shader shad{};
        static sf::RenderStates states{};
        static sf::VertexArray va{sf::PrimitiveType::TriangleFan, 4};
        static bool loaded = false;

        if (!loaded) {
            if (!shad.loadFromFile(RES_DIR"/shader/shape_shader/shade_rounded_rect.frag", sf::Shader::Type::Fragment)) {
                printf("Failed to load rounded rect shader\n");
                return;
            }
            states = sf::RenderStates{&shad};
            loaded = true;
        }

        shad.setUniform("radius", radius);
        shad.setUniform("halfSize", sf::Glsl::Vec2{size * 0.5f});

        set_rect(va, pos, size, col);
        target.draw(va, states);
    }

}; // namespace GLShapes
}; // namespace MEU


