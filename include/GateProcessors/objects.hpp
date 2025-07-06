#pragma once

#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

enum struct Obj {
  Gate,
  Circuit,
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
struct Gate {
  // what kind of Object is it
  // either logic gate, device
  // or ic
  const int type;
  
  // origin x
  float posx;
  // origin y
  float posy;
  
  // nodes the object will be readiing
  std::vector<bool> input_node;
  // nodes that the object will change
  std::vector<bool> *output_node; 

  Gate(int type_);
  void step(int step_size);
  void connect(bool &outp);
private:
  bool state;
};



// aka IC
struct Circuit {
  // what kind of Object is it
  // either logic gate, device
  // or ic
  const int type;
  
  // origin x
  float posx;
  // origin y
  float posy;
  
  // nodes the object will be readiing
  std::vector<bool> input_node;
  // nodes that the object will change
  std::vector<bool> *output_node;

  Circuit(int type_);
  /*internally calls the Circuit::evaluate_curcuit*/
  void step(int step_size);
  void connect(bool &outp);
private:
  std::vector<bool> states;
};

/* this holds the circuits and
 * dictate operations*/
struct CircuitType {
  void create_curcuit_type(std::vector<Obj> operations);
  /* creates a circuit and return the index of the created circuit type
   * parameters:
   *    initialize - perform a step  evaluation untill thers no object updating
   *      or the object exhaust the eval step lim
   *    eval_step_limit - defines the limit on how much to wait for the circuit
   *      to settle on a stable state*/
  int make_circuit(int type, bool initialize = false, int eval_step_limit = 10);
  /* take the circuit, look on its type, search on what type it is, use the internal state
   * evaluate the curcuit using the states, type and nodes
  */
  void evaluate_curcuit(Circuit &circuit);


private:
  
};












