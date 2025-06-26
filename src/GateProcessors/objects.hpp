#pragma once

#include <cstdint>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>


/* this holds the circuits and operations*/
struct Circuits {
  
}; 



// the Object that can hold internal state and have internal process
// used on both IC and logic gates
struct Obj {

  // what kind of Object is it
  // either logic gate, device
  // or ic
  const uint32_t type;
  
  // origin x
  float posx;
  // origin y
  float posy;
  
  // nodes the object will be readiing
  std::vector<bool> input_node;
  // nodes that the object will change
  std::vector<bool> *output_node;
  
  Obj(int type_);
  // function that change the state of its interface nodes
  // and perform a execution step on the logic inside
  virtual void step(int step_size = 1) = 0;
  // take a node and put it on output node array
  virtual void connect(bool *outp) = 0;
};

/* basic gates
 * 0 not
 * 1 buffer
 * 2 and
 * 3 nand
 * 4 or
 * 5 nor
 * 6 xor
 * 7 xnor
 * 8+ = Invalid component*/
struct Gate : public Obj {
  Gate(int type_);
  void step(int step_size);
  void connect(bool *outp);
private:
  bool state;
};


// aka IC
struct Circuit {
  Circuit(int type_);
  void step(int step_size);
  void connect(bool *outp);
private:
  std::vector<bool> states;
};

