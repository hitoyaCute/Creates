#include <cstdint>
#include <stdexcept>
#include <string>
#include <system_error>
#include "Gates.hpp"

BasicGate::BasicGate (uint8_t type_):
  nodes(BasicGateType::nodeAmount[type_]),
  type{type_} {
  if (type_ != 0){
    nodes[0] = new bool{BasicGateType::defaultState[type_]};
    buffer = new bool{*nodes[0]};
  }
};
void BasicGate::connect(bool *node, uint8_t index) {
  nodes[index] = node;
}; 

uint8_t BasicGate::getType() {
  return type;
}

bool* BasicGate::getOutpNode() {
  return buffer;
}

void BasicGate::process() {
  if (type != 0) {
    *nodes[0] = *buffer;
  }

  try {
  switch (type) {
    case 0: {break;} // null
    case 1: {*buffer = !*nodes[1]; break;} // not
    case 2: {*buffer = *nodes[1];break;} // buffer
    case 3: {*buffer = *nodes[1] && *nodes[2];break;} // and
    case 4: {*buffer = !(*nodes[1] && *nodes[2]);break;} // nand
    case 5: {*buffer = *nodes[1] || *nodes[2];break;} // or
    case 6: {*buffer = !(*nodes[1] || *nodes[2]);break;} // nor
    case 7: {*buffer = *nodes[1] != *nodes[2];break;} // xor
    case 8: {*buffer = *nodes[1] == *nodes[2];break;} // xnor
    default: {throw std::runtime_error(std::to_string(type) + " is not a valid gate type");break;}
  }} catch (const std::error_code err) {
    throw std::runtime_error("Segmentation fault (Core dumped): probably theres no ");
  }

}




