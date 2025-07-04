#include "KeyEvents.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>


void processEvents(sf::Window &window) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape) {
        window.close();
      }
    }

    if (const auto* mouse = event->getIf<sf::Event                ::MouseMoved>()) {
      data::mousePos = mouse->position;
    }
  }
}


