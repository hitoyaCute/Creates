#pragma once
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>
#include "Gates.hpp"


/// complex object
/// its a object that is not a basic gate nor input/output objects
enum struct complex {
  component,
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



class Circuits {
  static std::vector<std::vector<uint8_t>> types;
  static std::vector<std::vector<uint8_t>> nodes;
  static std::vector<std::vector<uint8_t>> circuits;
  static std::vector<std::string> info;
  static std::vector<std::vector<std::array<uint8_t, 2>>> gConnector;
  static std::vector<std::vector<std::array<uint8_t, 2>>> cConnector;

public:
  /// Creator sub object of Circuits
  class Creator {
    /// drafts
    std::vector<uint8_t> dTypes;
    std::vector<uint8_t> dCircuits;
    std::vector<uint8_t> nodes;
    std::string dInfo;
    std::vector<std::array<uint8_t, 2>> dGConnector;
    std::vector<std::array<uint8_t, 2>> dCConnector;

  public:
    /// saves the draffed type note that you cant change it ones changed
    /// this also auto detects objects has missing references
    void save();
    /// add gates
    void addGates(uint8_t gType);
    /// connect a internal node from gates,nodes and complex component to a gate
    /// where command is a unsinged char where 0b1000_0000 will tell if its a BasicGate
    /// or complex, where 1 connects from a BasicGate else complex
    /// the following bits are the index
    void gConnect(uint8_t gateId, uint8_t gateNode, uint8_t source, uint8_t sourceNode);
    /// add circuit from Circuits type
    void addCircuit(uint8_t cType);
    /// connect a internal node from gates, nodes and comples component to a circuit
    /// where command is a unsinged chat where 0b1000_0000 will tell if its a BasicGate
    /// the following bits are the index
    void cConnec(uint8_t circuitId, uint8_t circuitNode, uint8_t source, uint8_t sourceNode);

    /// connect a internal node from gates, nodes and comples component to a node
    /// where command is a unsinged chat where 0b1000_0000 will tell if its a BasicGate
    /// the following bits are the index
    void nodeConnect(uint8_t nodeId, uint8_t source, uint8_t sourceNode);
  };

  /// this will construct a circuit
  static Circuit construct(uint8_t type);
  
  /// creates new circuit
  static Circuits::Creator create(std::string info_);
  /// deletes a type using its ID/index
  static void incinirate(uint8_t index);
};

