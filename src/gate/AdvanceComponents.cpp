#include "Components.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>




Circuit::Circuit(uint8_t type_,
                 std::vector<bool*> nodes_,
                 std::vector<BasicGate> &gates_,
                 std::vector<Circuit> &comp_):
  type{type_},
  nodes{nodes_},
  gates{gates_},
  comp{comp_},
  stepSize{1}{
};



// takes a pointer to a node and connect it to a node on the Circuit
void Circuit::connect(bool* node, uint8_t index){};
void Circuit::step() {
  for (uint8_t j{0}; j < stepSize; j++){
    for (std::size_t i{0}; i <  std::size(gates); i++) {
      gates[i].process();
    }

    for (size_t i{0}; i < std::size(comp); i++) {
      comp[i].step();
    }
  }
};

std::vector<bool*> Circuit::getState() {
  std::vector<bool*> outp{std::size(gates)};
  
  for (size_t i{0}; i < std::size(gates); i++) {
    outp.push_back(gates[i].getOutpNode());
  }

  return outp;
};
std::vector<bool*> Circuit::getObjState(uint8_t index) {
  return comp[index].getNode();
};

std::vector<bool*> Circuit::getNode(){
  return nodes;
}


/// this will construct a circuit
std::vector<std::vector<uint8_t>> Circuits::types{};
std::vector<std::vector<uint8_t>> Circuits::circuits{};
std::vector<std::vector<uint8_t>> Circuits::nodes{};
std::vector<std::string> Circuits::info{};
std::vector<std::vector<std::array<uint8_t, 2>>> gConnector{};
std::vector<std::vector<std::array<uint8_t, 2>>> cConnector{};



Circuits::Creator Circuits::create(std::string info_) {
  Creator creator{};
  /// creating and initiating the required data



  return creator;
}


Circuit Circuits::construct(uint8_t type) {
  
}



