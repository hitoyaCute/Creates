#include <cmath>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/CoordinateType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "app/event.hpp"
#include "app/interface/scene/scene.hpp"
#include "ui/shapes/basicShape.hpp"


int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1280,800}), "Creates", sf::Style::Resize, sf::State::Fullscreen);
    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true);
    
    load_scene(window, 1);

    while (window.isOpen()) {
        process_event(window);
        // display main
        display_scene(window, 1);

        window.display();
    }
    return 0;
}

