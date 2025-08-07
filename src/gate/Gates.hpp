#pragma once
#include <cstdint>
#include <vector>

namespace Creates{

// component that represent a logic gate
struct BasicGate {
  // construct the gate object
  // and create its own output node
  BasicGate(uint8_t type);
  // connect
  // param:
  // \ \ \ \ bool &node - the node will be connected
  // \ \ \ \ uint8_t index - where it will be attach
  //
  // void connect(bool &node, uint8_t index)
  void connect(bool *node, uint8_t index);
  
  // get type
  uint8_t getType();

  // evaluate the gate
  void process();
private:
  // what kind of logic gate it is, 0 is null component with 0 input and 0 output
  uint8_t type = 0;

  // nodes reference on what the gate will use
  std::vector<bool*> nodes;
};

namespace BasicGateType {
  constexpr int nodeAmount[] = {
  0, // null
  2, // not gate
  2, // buffer gate
  3, // and gate
  3, // nand gate
  3, // or gate
  3, // nor gate
  3, // xor gate
  3, // xnor gate
  };
  constexpr bool defaultState[] = {
  false,
  true,
  false,
  false,
  true,
  false,
  true,
  false,
  true
  };
}; // BasicGateType

}; // Creates
