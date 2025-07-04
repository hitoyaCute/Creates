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
  // and perform evaluation step on the logic inside
  virtual void step(int step_size = 1) = 0;
  // take a node and put it on output node array
  virtual void connect(bool &outp) = 0;
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
  /*internally calls the Circuit::evaluate_curcuit*/
  void step(int step_size);
  void connect(bool &outp);
private:
  std::vector<bool> states;
};

/* this holds the circuits and
 * dictate operations*/
struct Circuits {
  void create_curcuit_type(std::vector<Gate> operations);
  /* creates a circuit
   * parameters:
   *    initialize - perform a step  evaluation untill thers no object updating
   *      or the object exhaust the eval step lim
   *    eval_step_limit - defines the limit on how much to wait for the circuit
   *      to settle on a stable state*/
  Circuit* make_circuit(int type, bool initialize = false, int eval_step_limit = 10);
  /* take the circuit, look on its type, search on what type it is, use the internal state
   * evaluate the curcuit using the states, type and nodes
  */
  void evaluate_curcuit(Circuit &circuit);


private:
  std::vector<Obj> objs;
  
};








