#include <cmath>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
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
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/CoordinateType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// #include "/ui/shapes/GlShapes.hpp"
#include "SFML/Window/Mouse.hpp"
#include "app/event.hpp"
#include "ui/shapes/basicShape.hpp"

// int __main(){
//   
//   /////// buidling half adder
//   Creates::Circuits::Generator halfADD{"name:half-adder;"};
//   // set a nodes 3 for input and 2 for output
//   halfADD.setNodes(4); // input are 0,1 sum is 2 and cary is 3

//   // add and(3)
//   halfADD.add(3);
//   halfADD.add(3);
//   // add xor(4)
//   halfADD.add(7);
//   halfADD.add(7);
//   // add or(2)
//   halfADD.add(5);

//   // connectGate - connect a gate to a node
//   // param:
//   // int first - index of the gate
//   // int firstNode - index of what node on that gate
//   // int second - index of the gate/circuit/node
//   // int secondNode - index of the node on that gate/circuit, if node it will do nothing
//   // char secondType = 'g' - g means gate on second and c for circuit and i for input
//   // connect the input0 to and gate to the 0th node of the gate
//   halfADD.connectGate(0, 0, 0, 0, 'i');
//   // connect the input1 to and gate to its 1th node
//   halfADD.connectGate(0, 1, 1, 0, 'i');
//   // connect the input0 to xor gate to its 0th node
//   halfADD.connectGate(2, 0, 0, 0, 'i');
//   // connect the input1 to xor gate to its 
//   halfADD.connectGate(2, 1, 1, 0, 'i');

//   // connect a node to a object same as connectGate
//   // connect node(3) aka output(1) to and gate's node(2) aka output
//   halfADD.connectNode(3, 0, 2, 'g');
//   // connect node(2) aka output(0) to xor gate's node(2) aka output
//   halfADD.connectNode(2, 1, 2, 'g');
//   int type = halfADD.save();

//   ////// build a full adder using 2 half adder
//   Creates::Circuits::Generator Adder{"name:adder-1b;"};

//   // create 2 half adder
//   Adder.addCircuit(type);
//   Adder.addCircuit(type);
//   Adder.add(5); // or gate
//   
//   // same for connectGate but first 2 parameters is a circuit
//   // connect first circuit's node(2) aka output(0) to second circuit's node(0) aka input(0)
//   Adder.connectCircuit(0, 2, 1, 0, 'c');
//   // connect first circuit's node(3) aka output(1) to or gate's node(0) aka input(0)
//   Adder.connectCircuit(0, 3, 0, 0, 'g');
//   // connect second circuit's node(3) aka output(1) to or gate's node(1) aka input(1)
//   Adder.connectCircuit(1, 3, 0, 1, 'g');
//   // connect the node(0) aka input(0) to circuit(0)'s node(0) aka input(0)
//   Adder.connectNode(0, 0, 0, 'c');
//   // connect the node(1) aka input(1) to circuit(0)'s node(1) aka input(1)
//   Adder.connectNode(1, 0, 1, 'c');
//   // connect the node(2) aka input(2) to circuit(1)'s node(1) aka input(1)
//   Adder.connectNode(2, 1, 1, 'c');
//   // connect the node(3) aka output(0) sum to circuit(1)'s node(2) aka output(0)
//   Adder.connectNode(3, 1, 2, 'c');
//   // connect the 



//   


//   return 0;
// }


void print_vertex_array(sf::VertexArray& arr) {
  std::cout << "[";
  uint32_t size = arr.getVertexCount();
  for (uint32_t i{0}; i < size; i++) {
    std::cout << "[" <<arr[i].position.y << ", " << arr[i].position.x << "], ";
  }
}


int main_() {
  auto window = sf::RenderWindow(sf::VideoMode({1280,800}), "Creates", sf::Style::Resize, sf::State::Fullscreen);
  window.setFramerateLimit(60);
  // window.setVerticalSyncEnabled(true);

  sf::Color color{50u,50u,50u};

  sf::Font font;
  bool loaded = font.openFromFile(RES_DIR"fonts/NerdFonts/HackNerdFontMono-Regular.ttf");

  sf::Text y_{font};
  sf::Text x_{font};

  uint32_t quality = 8;

  sf::VertexArray rcb{sf::PrimitiveType::TriangleStrip, quality*4*2+2};
  sf::VertexArray rc{sf::PrimitiveType::TriangleFan, quality*4};
  sf::VertexArray c{sf::PrimitiveType::TriangleFan, quality * 4};

  const sf::Vector2<unsigned int> size = window.getSize();


  // testing and structuring the UI
  sf::VertexArray top_shelf{sf::PrimitiveType::TriangleFan, quality*4};
  sf::VertexArray sim_window{sf::PrimitiveType::TriangleFan, quality*4};
  sf::VertexArray sim_window_border{sf::PrimitiveType::TriangleStrip, quality*4*2+2};
  // sim_window.setPosition(sf::Vector2f{10.f,110.f});
  // sim_window.setSize(sf::Vector2f{size.x - 20.f, size.y - 110.f - 10.f});
  
  while (window.isOpen()) {
    const auto mousePos = sf::Mouse::getPosition(window);
    window.clear(sf::Color {75u,75u,75u});
    process_event(window);

    y_.setString(std::to_string(mousePos.y));
    y_.setPosition({25.f,5.f});
    x_.setString(std::to_string(mousePos.x));
    x_.setPosition({25.f,35.f});

    MEU::Shape::CreateCircle(c, quality * 4, 10.f, static_cast<sf::Vector2f>(mousePos), sf::Color{255,255,0});
    MEU::Shape::CreateRoundedRect(top_shelf,
                               quality*4,
                               20.f,
                               sf::Vector2f{size.x-20.f,100.f},
                               sf::Vector2f{10.f,10.f}, sf::Color{200,200,200});
    MEU::Shape::CreateRoundedRect(sim_window, quality*4, 20.f, sf::Vector2f{size.x - 20.f, size.y - 120.f - 10.f}, sf::Vector2f{10.f,120.f}, sf::Color{50,50,50});
    MEU::Shape::CreateRoundedRectBorder(sim_window_border, quality*4*2+2, 20.f, 20.f, sf::Vector2f{size.x - 20.f, size.y - 120.f - 10.f}, sf::Vector2f{10.f,120.f}, sf::Color{50,50,50}, sf::Color{75,75,75,0});

    window.draw(sim_window_border);
    window.draw(sim_window);
    window.draw(top_shelf);
    window.draw(c);
    window.draw(y_);
    window.draw(x_);

    window.display();
  }
  return 0;
}

