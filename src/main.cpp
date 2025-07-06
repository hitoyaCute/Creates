#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CoordinateType.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <X11/X.h>
#include <chrono>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <ctime>
#include <string>
#include <unistd.h>

#include "UIProcessor/Events/EventProcessor.hpp"
#include "UIProcessor/ShapeDrawer/Shapes.hpp"

int main() {

  auto window = sf::RenderWindow(sf::VideoMode({1280,800}), "Creates", sf::Style::Resize, sf::State::Fullscreen);
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  sf::Color color{50u,50u,50u};
  
  sf::Font font;
  bool loaded = font.openFromFile(std::filesystem::path("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"));
  
  sf::Text y_{font};
  sf::Text x_{font};
  sf::Text text{font};

  uint32_t quality = 40*4;
  
  sf::VertexArray c{sf::PrimitiveType::TriangleFan, quality};

  const sf::Vector2<unsigned int> size = window.getSize();

  while (window.isOpen()) {
    
    window.clear(sf::Color {50u,50u,50u});
    processEvents(window);

        

    y_.setString(std::to_string(data::mousePos.y));
    y_.setPosition({size.y*0.1f,0});
    x_.setString(std::to_string(data::mousePos.x));
    x_.setPosition({size.y*0.1f,30.f});
    text.setString(data::lastPressed);
    text.setPosition({size.y*0.1f,60.f});

    
    generateRoundedRect(c, quality, (static_cast<sf::Vector2f>(data::mousePos) - sf::Vector2f{50.f,50.f}),
                        100.f, 100.f,
      15.f);
    
    window.draw(c);
    window.draw(y_);
    window.draw(x_);
    window.draw(text);

    window.display();
  }
}













