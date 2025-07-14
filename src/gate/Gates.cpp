#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Gates.hpp"


BasicGate::BasicGate (uint8_t type_):
  nodes(BasicGateType::nodeAmount[type_]),
  type{type_} {
  if (type_ != 0){
    nodes[0] = new bool{BasicGateType::defaultState[type_]};
  }
};
void BasicGate::connect(bool *node, uint8_t index) {
  nodes[index] = node;
}; 

uint8_t BasicGate::getType() {
  return type;
}

bool* BasicGate::getOutpNode() {
  return nodes[0];
}

void BasicGate::process() {
  switch (type) {
    case 0: {break;} // null
    case 1: {*nodes[0] = !*nodes[1]; break;} // not
    case 2: {break;} // buffer
    case 3: {*nodes[0] = *nodes[1] && *nodes[2];break;} // and
    case 4: {*nodes[0] = !(*nodes[1] && *nodes[2]);break;} // nand
    case 5: {*nodes[0] = *nodes[1] || *nodes[2];break;} // or
    case 6: {*nodes[0] = !(*nodes[1] || *nodes[2]);break;} // nor
    case 7: {*nodes[0] = *nodes[1] ^ *nodes[2];break;} // xor
    case 8: {*nodes[0] = !(*nodes[1] ^ *nodes[2]);break;} // xnor
    default: {throw std::runtime_error(std::to_string(type) + " is not a valid gate type");break;}
  }
}




