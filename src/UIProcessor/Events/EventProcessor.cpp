#include "UIProcessor/Events/EventProcessor.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <optional>


sf::Vector2i data::mousePos = {0,0};
char data::lastPressed = '_';

void processEvents(sf::Window &window) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape) {
        window.close();
      } else {
        data::lastPressed = (char)key->code;
        std::cout << (char)key->code << std::endl;
      }
    }

    if (const auto* mouse = event->getIf<sf::Event                ::MouseMoved>()) {
      data::mousePos = mouse->position;
    }
  }
}


