#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

struct data {
  static sf::Vector2i mousePos;
  static char lastPressed;
};

void processEvents(sf::Window &window);


