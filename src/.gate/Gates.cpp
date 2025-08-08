#include <cstdint>
#include <stdexcept>
#include <string>
#include <system_error>
#include "Gates.hpp"

namespace Creates{

BasicGate::BasicGate (uint8_t type_):
  nodes(BasicGateType::nodeAmount[type_]),
  type{type_} {
};
void BasicGate::connect(bool *node, uint8_t index) {
  if (nodes[index] != 0) {
    throw std::runtime_error("connecting to a node already connected will result to the gate loosing its reference to the node its previusly connected to");
  }
  

  nodes[index] = node;
}; 

uint8_t BasicGate::getType() {
  return type;
}

void BasicGate::process() {
  try {
    switch (type) {
      case 0: {break;} // null
      case 1: {*nodes[0] = !*nodes[1];break;} // not
      case 2: {*nodes[0] = *nodes[1];break;} // buffer
      case 3: {*nodes[0] = *nodes[1] and *nodes[2];break;} // and
      case 4: {*nodes[0] = !(*nodes[1] and *nodes[2]);break;} // nand
      case 5: {*nodes[0] = *nodes[1] or *nodes[2];break;} // or
      case 6: {*nodes[0] = !(*nodes[1] or *nodes[2]);break;} // nor
      case 7: {*nodes[0] = *nodes[1] != *nodes[2];break;} // xor
      case 8: {*nodes[0] = *nodes[1] == *nodes[2];break;} // xnor
      default: {throw std::runtime_error(std::to_string(type) + " is not a valid gate type");break;}
    }
  } catch (const std::error_code err) {
    throw std::runtime_error("Segmentation fault (Core dumped): probably theres no nodes");
  }
}



/*





*/
}; // Creates



