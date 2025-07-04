#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

struct data {
  static sf::Vector2i mousePos;
  static void start();
};

void processEvents(sf::Window& window);
