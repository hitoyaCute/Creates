#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Gates.hpp"

enum struct Obj {
  Gates,
  Circuit
};


struct Circuit {
  Circuit(uint8_t type_,
          std::vector<bool*> nodes_,
          std::vector<BasicGate> &gates_,
          std::vector<Circuit> &comp_);
  // takes a pointer to a node and connect it to a node on the Circuit
  void connect(bool* node, uint8_t index);
  void step();
  // return the pointer to the state of internal gates
  std::vector<bool*> getState();
  // return a object for observation
  std::vector<bool*> getObjState(uint8_t index);
  // return reference of of the circuit's node(external)
  std::vector<bool*> getNode();
  uint8_t stepSize;
private:
  const uint8_t type;
  // the external nodes the Circuit using
  std::vector<bool*> nodes;
  // the individual gates inside the circuit
  std::vector<BasicGate> gates;
  // complex components
  std::vector<Circuit> comp;
};



struct Circuits {
  static std::vector<std::vector<BasicGate>> types;
  static std::vector<std::vector<Circuit>> circuits;
  static std::vector<std::vector<bool*>> nodes;
  static std::vector<std::string> info;

  static void create(std::string info);
  /// this will construct a circuit
  static Circuit construct(uint8_t type);
};


struct Node {
  bool* state;
};



