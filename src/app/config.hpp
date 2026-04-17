#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

namespace conf {

static const char*        project_name  = "Creates";
static sf::Vector2u const window_size   = {1280,800};
static sf::Vector2f const window_size_f = {(sf::Vector2f)window_size};
static sf::Font     const font            {RES_DIR"/fonts/NerdFonts/HackNerdFont-Bold.ttf"};

}; // namespace conf


