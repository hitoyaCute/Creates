#include "EventProcessor.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <optional>


sf::Vector2i data::mousePos = {0,0};
char data::lastPressed = '_';
uint8_t data::t = 0;
uint8_t data::d = 0;

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
      };
      if (key->code == sf::Keyboard::Key::W) {
        data::t ++;
      } else if (key->code == sf::Keyboard::Key::S) {
        data::t --;
      };
      if (key->code == sf::Keyboard::Key::A) {
        data::d ++;
      } else if (key->code == sf::Keyboard::Key::D) {
        data::d --;
      }
    }

    if (const auto* mouse = event->getIf<sf::Event::MouseMoved>()) {
      data::mousePos = mouse->position;
    }
  }
}


