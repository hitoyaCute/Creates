#include <cmath>
#include <iostream>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/CoordinateType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "ui/shapes/Shapes.hpp"
#include "ui/events/EventProcessor.hpp"
#include "gate/Components.hpp"
#include "gate/Gates.hpp"

int main (int argc, char *argv[]) {
  bool* A = new bool {true};
  bool* B = new bool {true};
  bool* C = new bool {true};
  
  std::vector<bool*> nodes;
  
  nodes.resize(5);
  nodes[0] = A;
  nodes[1] = B; 
  nodes[2] = C;


  "name: adder-1b";
  std::vector<BasicGate> gates{};

  uint8_t t[5] = {3,3,// and
    7,7, // xor
    5}; // or
  std::cout << "num of items: " << std::size(gates) << std::endl;
  for (int i{0}; i < 5; i++) {
    gates.push_back(BasicGate{t[i]});

  }
  std::cout << "num of items: " << std::size(gates) << std::endl;
  // and0
  gates[0].connect(nodes[0], 2);
  gates[0].connect(nodes[1], 1);
  // and1
  gates[1].connect(nodes[2], 1);
  gates[1].connect(gates[2].getOutpNode(), 2);
  // xor0
  gates[2].connect(nodes[0], 2);
  gates[2].connect(nodes[1], 1);
  // xor1
  gates[3].connect(nodes[2], 2);
  gates[3].connect(gates[2].getOutpNode(), 1);
  // or
  gates[4].connect(gates[0].getOutpNode(), 2);
  gates[4].connect(gates[1].getOutpNode(), 1);
  // output
  nodes[3] = gates[3].getOutpNode();
  nodes[4] = gates[4].getOutpNode();

  // dummy circuit
  std::vector<Circuit> circuits{};
  Circuit adder{0,nodes,gates,circuits};

  std::vector<bool*> node = adder.getNode();
  

  std::cout << "circuit and nodes are initiated\n";
  
  adder.stepSize = 3;
  for (int a{0}; a <= 1; a++) {
    for (int b{0}; b <= 1; b++) {
      for (int c{0}; c <= 1; c++) {
        *A = a; *B = b; *C = c;
        adder.step();
        std::cout << "input: " << *A << " ," << *B << " ," << *C << "  output: " <<
        *node[3] << " ," << *node[4] << std::endl;
      }
    }
  }




  

  

  return 0;
}




int _main() {
  auto window = sf::RenderWindow(sf::VideoMode({1280,800}), "Creates", sf::Style::Resize, sf::State::Fullscreen);
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  sf::Color color{50u,50u,50u};
  
  sf::Font font;
  bool loaded = font.openFromFile(std::filesystem::path("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"));
  
  sf::Text y_{font};
  sf::Text x_{font};
  sf::Text text{font};

  uint32_t quality = 2*4;
  data::t = 2;
  data::d = 50;
  
  sf::VertexArray rc{sf::PrimitiveType::TriangleStrip, quality};

  const sf::Vector2<unsigned int> size = window.getSize();

  while (window.isOpen()) {
    window.clear(sf::Color {50u,50u,50u});
    processEvents(window);

    y_.setString(std::to_string(data::mousePos.y));
    y_.setPosition({size.y*0.1f,0});
    x_.setString(std::to_string(data::mousePos.x));
    x_.setPosition({size.y*0.1f,30.f});
    text.setString(data::lastPressed);
    text.setPosition({size.y*0.1f,60.f});
    
    sf::VertexArray c{sf::PrimitiveType::TriangleFan, data::t * 4u};
    generateRoundedRect(c, data::t * 4u, (static_cast<sf::Vector2f>(data::mousePos)) , // - sf::Vector2f{50.f,50.f}),
                        {500.f, 800.f},(static_cast<float>(data::d)/256.f)/2.f);
    // generateCircle(c, quality, (static_cast<sf::Vector2f>(data::mousePos)),
    //                200);
    
    window.draw(c);
    window.draw(y_);
    window.draw(x_);
    window.draw(text);
   

    window.display();
    
  }

  return 0;
}













