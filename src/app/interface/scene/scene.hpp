#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


void draw_main(sf::RenderWindow& window);
// load add data about that scene
void load_main(sf::RenderWindow& window);


void draw_intro(sf::RenderWindow& window);



inline void display_scene(sf::RenderWindow &window, int scene = 1) {
    draw_main(window);
    if (scene == 0) {
        draw_intro(window);
    }
}


