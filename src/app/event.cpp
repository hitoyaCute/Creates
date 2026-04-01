#include "app/event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"

using sf::Keyboard::Scan;

void process_event(sf::RenderWindow &win) {
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            win.close();
        } else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == Scan::Escape) {
                win.close();
            }
        }
    }
}
