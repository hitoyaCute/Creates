#pragma once

#include <cstdint>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
// the Object that can hold internal state and have internal process
// used on both IC and logic gates
struct Obj {

  // what kind of Object is it
  // either logic gate, device
  // or ic
  int type;
  
  // origin x
  float posx;
  // origin y
  float posy;

  // var that holds the vector on what the shape
  // of the  object would be relative to the origin
  sf::VertexArray shape;
  
  // IO nodes
  std::vector<bool> &interface_node;
  
  
  // function that change the state of its interface nodes
  // and perform a execution step on the logic inside
  virtual void step(std::vector<uint64_t>& local_nodes, std::vector<uint64_t>& external_nodes, int step_size = 1) = 0;
  Obj();
};


struct Gate : public Obj {
  
  std::vector<bool>& step(int step_size);
  Gate();
private:
  std::vector<bool> states;
  
  
};







