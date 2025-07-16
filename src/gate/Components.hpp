#pragma once
#include <cstdint>
#include <vector>
#include "Gates.hpp"

enum struct Obj {
  BasicGate,
  Gates,
  Circuit
};


struct Circuit{
  Circuit(uint8_t type_);
  void connect(bool* node, uint8_t index);
private:
  const uint8_t type;
  // the external nodes the Circuit using
  std::vector<bool*> nodes;
  std::vector<BasicGate> gates;
};



struct Circuits {
  
   
};




