#pragma once

#include <vector>

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
  std::vector<float> shape;
  
  // var the state of each nodes
  std::vector<bool> interface_node;

  // var that holds what the object can do
  std::vector<bool> state;

  // holds the array of connected nodes
  std::vector<std::vector<int>> internal_nodes;
  
  // function that change the state of its interface nodes
  // and perform a execution step on the logic inside
  virtual std::vector<bool>& step(int step_size = 1) = 0;


};


struct Gate : public Obj {
  std::vector<bool>& step(int step_size); 
};

struct Circuit : public Obj {
  std::vector<bool>& step(int step_size);
};

namespace type_holder {
std::vector<Obj> type;
}

