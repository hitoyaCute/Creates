#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

int main() {
  sf::PrimitiveType fan = sf::PrimitiveType::TriangleFan;
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(144);
  
  while (window.isOpen()) {
  
    while (const std::optional event = window.pollEvent()) {
      
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    window.display();
  }
}
