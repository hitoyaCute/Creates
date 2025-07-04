#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <string>

#include "UIProcessor/Events/KeyEvents.hpp"
#include "UIProcessor/ShapeDrawer/Shapes.hpp"

int main() {
  
  data::mousePos = {0,0};

  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(30);
  window.clear();

  sf::Color color{50u,50u,50u};
  sf::Font font;
  bool loaded = font.openFromFile(std::filesystem::path("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"));
  
  sf::Text y_{font};
  sf::Text x_{font};

  while (window.isOpen()) {

    window.clear();
    processEvents(window);

    uint32_t quality = 40*4;
    sf::VertexArray circle{sf::PrimitiveType::TriangleFan, quality};
    sf::VertexArray c(sf::PrimitiveType::TriangleFan, quality/4);
    
    sf::Vector2u size = window.getSize();
    
    

    y_.setString(std::to_string(data::mousePos.y));
    y_.setPosition({size.y*0.1f,0});
    x_.setString(std::to_string(data::mousePos.x));
    x_.setPosition({size.y*0.1f,30.f});
    
    generateRoundedRect(circle, quality, {1.f,size.y*0.15f}, size.y*0.15f, size.x, ((size.x+size.y)/2.0f)*0.05f,
                        color);
    generateRoundedRect(c, quality, static_cast<sf::Vector2f>(data::mousePos),
                        size.y*0.01f, size.x*0.01f,
      ((size.x+size.y)/2.0f)*0.05f);

    window.draw(circle);
    window.draw(y_);
    window.draw(x_);
    window.draw(c);
    


    window.display();
  }
}










