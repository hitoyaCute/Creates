#include "app/event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "app/globals.hpp"

using sf::Keyboard::Scan;

void process_event(sf::RenderWindow &win) {
    Glob::zoom_delta = 0;
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            win.close();
        } else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == Scan::Escape) {
                win.close();
            }
        } else if(const auto wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
            Glob::zoom_delta += wheel->delta;
        }
    }
}
