#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Gates.hpp"

enum struct Obj {
  Gates,
  Circuit
};


struct Circuit{
  Circuit(uint8_t type_);
  // takes a pointer to a node and connect it to a node on the Circuit
  void connect(bool* node, uint8_t index);
  void step(uint8_t stepSize);
private:
  const uint8_t type;
  // the external nodes the Circuit using
  std::vector<bool*> nodes;
  // the individual gates inside the circuit
  std::vector<BasicGate> gates;
  // complex components
  std::vector<Obj> comp;
};



struct Circuits {
  static std::vector<std::vector<BasicGate>> types;
  static std::vector<std::vector<bool*>> nodes;
  static std::vector<std::string> info;

  uint8_t craftCircuit(std::string info);
};


struct Node {
  
};



