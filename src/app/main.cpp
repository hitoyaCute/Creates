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



using namespace Creates;



int main (int argc, char *argv[]) {
  bool* A = new bool {true};
  bool* B = new bool {true};
  bool* C = new bool {true};
  
  std::vector<bool*> nodes;
  
  nodes.resize(5);
  nodes[0] = A;
  nodes[1] = B; 
  nodes[2] = C;


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



int __main(){
  
  /////// buidling half adder
  Creates::Circuits::Generator halfADD{"name:half-adder;"};
  // set a nodes 3 for input and 2 for output
  halfADD.setNodes(4); // input are 0,1 sum is 2 and cary is 3

  // add and(3)
  halfADD.add(3);
  halfADD.add(3);
  // add xor(4)
  halfADD.add(7);
  halfADD.add(7);
  // add or(2)
  halfADD.add(5);

  // connectGate - connect a gate to a node
  // param:
  // int first - index of the gate
  // int firstNode - index of what node on that gate
  // int second - index of the gate/circuit/node
  // int secondNode - index of the node on that gate/circuit, if node it will do nothing
  // char secondType = 'g' - g means gate on second and c for circuit and i for input
  // connect the input0 to and gate to the 0th node of the gate
  halfADD.connectGate(0, 0, 0, 0, 'i');
  // connect the input1 to and gate to its 1th node
  halfADD.connectGate(0, 1, 1, 0, 'i');
  // connect the input0 to xor gate to its 0th node
  halfADD.connectGate(2, 0, 0, 0, 'i');
  // connect the input1 to xor gate to its 
  halfADD.connectGate(2, 1, 1, 0, 'i');

  // connect a node to a object same as connectGate
  // connect node(3) aka output(1) to and gate's node(2) aka output
  halfADD.connectNode(3, 0, 2, 'g');
  // connect node(2) aka output(0) to xor gate's node(2) aka output
  halfADD.connectNode(2, 1, 2, 'g');
  int type = halfADD.save();

  ////// build a full adder using 2 half adder
  Creates::Circuits::Generator Adder{"name:adder-1b;"};

  // create 2 half adder
  Adder.addCircuit(type);
  Adder.addCircuit(type);
  Adder.add(5); // or gate
  
  // same for connectGate but first 2 parameters is a circuit
  // connect first circuit's node(2) aka output(0) to second circuit's node(0) aka input(0)
  Adder.connectCircuit(0, 2, 1, 0, 'c');
  // connect first circuit's node(3) aka output(1) to or gate's node(0) aka input(0)
  Adder.connectCircuit(0, 3, 0, 0, 'g');
  // connect second circuit's node(3) aka output(1) to or gate's node(1) aka input(1)
  Adder.connectCircuit(1, 3, 0, 1, 'g');
  // connect the node(0) aka input(0) to circuit(0)'s node(0) aka input(0)
  Adder.connectNode(0, 0, 0, 'c');
  // connect the node(1) aka input(1) to circuit(0)'s node(1) aka input(1)
  Adder.connectNode(1, 0, 1, 'c');
  // connect the node(2) aka input(2) to circuit(1)'s node(1) aka input(1)
  Adder.connectNode(2, 1, 1, 'c');
  // connect the node(3) aka output(0) sum to circuit(1)'s node(2) aka output(0)
  Adder.connectNode(3, 1, 2, 'c');
  // connect the 



  


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













