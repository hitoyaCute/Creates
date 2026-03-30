#pragma once
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <array>

namespace Creates {

namespace Simulation {


enum GateTypes {
  Not,
  Buffer,
  And,
  Nand,
  Or,
  Nor,
  Xor,
  Xnor,
  
};

enum Pheriphirals {
  // I/O
  external_node,
  touch_screen_LCD,
  // input
  constant,
  button,
  lever,
  // output
  bulb,
  char_display,
  LCD,
  seg_7_display,

};


class Gates {
  // index of where on buffer the gate will write
  std::array<uint32_t, 16>         output;
  // index of on where to get the value from the states
  uint32_t         input[2] = {0xffffffff,0xffffffff};

  GateTypes const _type;
public:
  Gates(const GateTypes type);
  /////////////////////////////////////////////////////
  /// eval breifely evaluate the gate
  /////////////////////////////////////////////////////
  void eval(std::vector<bool>& state_ref, std::vector<bool>& buffer_ref);
  /////////////////////////////////////////////////////
  /// connect_input breifely connect a input port
  /// param inp the port will be connected
  /// param index the input where the port will be placed
  /////////////////////////////////////////////////////
  void connect_input(uint32_t inp, const uint8_t index = 0);
  /////////////////////////////////////////////////////
  /// connect_out breifely connect a output port
  /// param outp the port will be added/connect to the output port
  ////////////////////////////////////////////////////
  int connect_out(uint32_t outp);
  ////////////////////////////////////////////////////
  /// remove_out breifely remove a output port
  /// param outp the port that will be removed
  ////////////////////////////////////////////////////
  void remove_out(uint32_t outp);


  // gates

  static const Gates Not;
  static const Gates Buffer;
  static const Gates And;
  static const Gates Nand;
  static const Gates Or;
  static const Gates Nor;
  static const Gates Xor;
  static const Gates Xnor;
};

class Circuits {
  // contains the state of the circuit 1 step behind
  std::vector<bool> buffer;
  // the current state of the circuit
  std::vector<bool> states;
  // index of states connected to the external port
  std::vector<std::pair<uint32_t, uint32_t>> port;
  // gates holder
  std::vector<Gates> gates;
  // circuits holder
  std::vector<Circuits> circuits;
  
  uint32_t step_count;

  const std::string _type;

public:
  Circuits(std::string type);
  
  ////////////////////////////////////////////////////
  /// eval perform a evaluation of the gates and circuits with pheriphirals
  /// 
  ////////////////////////////////////////////////////
  void eval(std::vector<bool>& state_ref, std::vector<bool>& buffer_ref);

  uint32_t& get_port(uint32_t i);

/*////////////////////////////////////////////////////////////
                      GATES
////////////////////////////////////////////////////////////*/

  ////////////////////////////////////////////////////
  /// add_gate breif including a gate
  /// param type the gates to be appended
  ///
  /// returns the gate index
  ////////////////////////////////////////////////////
  uint32_t add_gate(GateTypes type);

  ////////////////////////////////////////////////////
  /// gates_connect_output connect something from the internal state
  ///
  /// arg node_index the index from internal nodes
  /// arg gate_index the gates where the output will be connected
  ///
  /// returns result
  ////////////////////////////////////////////////////
  int gates_connect_output(uint32_t node_index, uint32_t gate_index);
  
  ////////////////////////////////////////////////////
  /// gates_dissconnect detach output node from the internal state to the gates
  ///
  /// arg node_index the index from internal nodes
  /// arg gate_index the gates where the output will be connected
  ////////////////////////////////////////////////////
  void gates_dissconnect(uint32_t node_index, uint32_t gate_index);

  ////////////////////////////////////////////////////
  /// gates_connect_input connect something from
  ///
  /// arg node_index the index from internal nodes
  /// arg gate_index the gates where the output will be connected
  /// arg input_index where on the gate's input it will connected
  ///
  /// returns result
  ////////////////////////////////////////////////////
  void gates_connect_input(uint32_t node_index, uint32_t gate_index, bool input_index);

/*////////////////////////////////////////////////////////////
                       CIRCUITS
/*////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////
  /// add_circuit append circuit
  ///
  /// arg circuit the pointer to the circuit will be added
  ///
  /// and return the index of the circuit
  ////////////////////////////////////////////////////
  uint8_t add_circuit(const Circuits& circuit);

  ////////////////////////////////////////////////////
  /// circuit_connect connect a node to the port of circuit
  ///
  /// arg node_index the node will be referenced
  /// arg circuit_index the circuit where the node will be connected
  /// arg port_index which port it would be connected
  ///
  /// returns the result
  ////////////////////////////////////////////////////
  void circuit_connect(uint32_t node_index, uint8_t circuit_index, uint8_t port_index);


  ////////////////////////////////////////////////////
  /// circuit_disconnect detach a node to the port of circuit
  ///
  /// arg circuit_index the owner of the port
  /// arg port_index which port it would be detach
  ////////////////////////////////////////////////////
  void circuit_disconnect(uint8_t circuit_index, uint8_t port_index);

/*////////////////////////////////////////////////////////////
                       PHERIPHERAL
/*////////////////////////////////////////////////////////////
};

inline const Gates Gates::Not   (GateTypes::Not);
inline const Gates Gates::Buffer(GateTypes::Buffer);
inline const Gates Gates::And   (GateTypes::And);
inline const Gates Gates::Nand  (GateTypes::Nand);
inline const Gates Gates::Or    (GateTypes::Or);
inline const Gates Gates::Nor   (GateTypes::Nor);
inline const Gates Gates::Xor   (GateTypes::Xor);
inline const Gates Gates::Xnor  (GateTypes::Xnor);

}; // Creates
}; // Simulation
