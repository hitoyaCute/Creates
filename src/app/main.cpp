#include <cmath>
#include <iostream>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <SFML/Graphics.hpp>
// #include <SFML/System/Err.hpp>
// #include <SFML/System/Time.hpp>
// #include <SFML/System/Sleep.hpp>
// #include <SFML/Graphics/Text.hpp>
// #include <SFML/Graphics/Font.hpp>
// #include <SFML/Graphics/Color.hpp>
// #include <SFML/Graphics/Shape.hpp>
// #include <SFML/System/Vector2.hpp>
// #include <SFML/Window/VideoMode.hpp>
// #include <SFML/Window/WindowEnums.hpp>
// #include <SFML/Graphics/VertexArray.hpp>
// #include <SFML/Graphics/PrimitiveType.hpp>
// #include <SFML/Graphics/CoordinateType.hpp>
// #include <SFML/Graphics/RectangleShape.hpp>

// #include "ui/shapes/Shapes.hpp"
// #include "ui/events/EventProcessor.hpp"
#include "gate/Components.hpp"
#include "gate/Gates.hpp"

int main (int argc, char *argv[]) {
  bool* A = new bool {true};
  bool* B = new bool {true};
  bool* C = new bool {true};

  BasicGate and0{3};
  BasicGate and1{3};
  BasicGate xor0{7};
  BasicGate xor1{7};
  BasicGate or0{5};
  
  xor0.connect(A, 1);
  xor0.connect(B, 2);

  and0.connect(B, 2);
  and0.connect(A, 1);

  and1.connect(xor0.getOutpNode(), 1);
  // and1.connect(C, 2);
  
  or0.connect(and0.getOutpNode(), 2);
  or0.connect(and1.getOutpNode(), 1);

  xor1.connect(xor0.getOutpNode(), 1);
  xor1.connect(C, 2);

  for (int  i{0}; i < 3; i++) {
    
  or0.process();
  xor1.process();
  and0.process();
  xor0.process();
  and1.process();
    std::cout << "input: " << *A << " ," << *B << " ," << *C << "  output: " <<
      *xor1.getOutpNode() << " ," << *or0.getOutpNode() << std::endl;
    // std::cout << "   and0: " << *and0.getOutpNode() << " and1: " << *and1.getOutpNode() <<
    // " xor1: " << *xor0.getOutpNode() << " or0: " << *or0.getOutpNode() << " xor1: " << *xor1.getOutpNode() << std::endl;
  }
  
  // int id = Circuits::createCircuit("adder_1b");
  // Circuits::types[id];
  
  
  

  return 0;
}




// int _main() {
//   auto window = sf::RenderWindow(sf::VideoMode({1280,800}), "Creates", sf::Style::Resize, sf::State::Fullscreen);
//   window.setFramerateLimit(60);
//   window.setVerticalSyncEnabled(true);

//   sf::Color color{50u,50u,50u};
//   
//   sf::Font font;
//   bool loaded = font.openFromFile(std::filesystem::path("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"));
//   
//   sf::Text y_{font};
//   sf::Text x_{font};
//   sf::Text text{font};

//   uint32_t quality = 2*4;
//   data::t = 2;
//   data::d = 50;
//   
//   sf::VertexArray rc{sf::PrimitiveType::TriangleStrip, quality};

//   const sf::Vector2<unsigned int> size = window.getSize();

//   while (window.isOpen()) {
//     window.clear(sf::Color {50u,50u,50u});
//     processEvents(window);

//     y_.setString(std::to_string(data::mousePos.y));
//     y_.setPosition({size.y*0.1f,0});
//     x_.setString(std::to_string(data::mousePos.x));
//     x_.setPosition({size.y*0.1f,30.f});
//     text.setString(data::lastPressed);
//     text.setPosition({size.y*0.1f,60.f});
//     
//     sf::VertexArray c{sf::PrimitiveType::TriangleFan, data::t * 4u};
//     generateRoundedRect(c, data::t * 4u, (static_cast<sf::Vector2f>(data::mousePos)) , // - sf::Vector2f{50.f,50.f}),
//                         {500.f, 800.f},(static_cast<float>(data::d)/256.f)/2.f);
//     // generateCircle(c, quality, (static_cast<sf::Vector2f>(data::mousePos)),
//     //                200);
//     
//     window.draw(c);
//     window.draw(y_);
//     window.draw(x_);
//     window.draw(text);
//    

//     window.display();
//     
//   }
// }













