#include "app/event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "app/globals.hpp"

using sf::Keyboard::Scan;

void process_event(sf::RenderWindow &win) {
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            win.close();
        } else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == Scan::Escape) {
                win.close();
            }
        } else if(const auto wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
            float temp = wheel->delta * 2;
            printf("%f\n", ((float)Glob::zoom_scalar) / 255.f);
            if (temp+(float)Glob::zoom_scalar > 255) {
                Glob::zoom_scalar = -1;
            } else if (temp+(float)Glob::zoom_scalar <= 0) {
                Glob::zoom_scalar = 0;
            } else {
                Glob::zoom_scalar = temp+(float)Glob::zoom_scalar;
            }
        }
    }
}
