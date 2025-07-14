#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdint>

struct data {
  static sf::Vector2i mousePos;
  static uint8_t t;
  static uint8_t d;
  static char lastPressed;
};

void processEvents(sf::Window &window);


