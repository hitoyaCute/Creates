#include "../objects.hpp"
#include <cstdint>
#include <string>

namespace Creates {

namespace Simulation {


Circuits::Circuits(std::string type):
  _type{type}
{
  buffer.reserve(256);
  states.reserve(256);
  port.reserve(32);
  gates.reserve(128);
  circuits.reserve(8);
}

uint32_t& Circuits::get_port(uint32_t i) {
    return port[i].first;
}

uint32_t Circuits::add_gate(GateTypes type) {
  gates.push_back(Gates{type});
  
  return gates.size();
}

int Circuits::gates_connect_output(uint32_t node_index, uint32_t gate_index) {
  return gates[gate_index].connect_out(node_index);
}

void Circuits::gates_dissconnect(uint32_t node_index, uint32_t gate_index) {
  gates[gate_index].remove_out(node_index);
}

void Circuits::gates_connect_input(uint32_t node_index, uint32_t gate_index, bool input_index) {
  gates[gate_index].connect_input(node_index, input_index);
}

uint8_t Circuits::add_circuit(const Circuits& circuit) {
  circuits.push_back(circuit);
  
  return circuits.size();
}

void Circuits::circuit_connect(uint32_t node_index, uint8_t circuit_index, uint8_t port_index) {
  auto c = circuits[circuit_index];

  auto& port = c.get_port(port_index);

  port = node_index;

}


void Circuits::eval(std::vector<bool>& state_ref, std::vector<bool>& buffer_ref) {
  
  for (uint16_t _{0}; _ < step_count; _++) {

    // evaluate pheripherals
    //
    // later
    
    // process external node first
    for (uint8_t en{0}; en < port.size(); en++) {
      states[port[en].second] = state_ref[port[en].first];
    }


    // apply the buffer
    for (uint32_t s{0}; s < states.size(); s++){
      states[s] = buffer[s];
    };
    // evaluate the gates and OR its output to the buffer
    for (uint16_t g{0}; g < gates.size(); g++) {
      gates[g].eval(states, buffer);
    }

    // evaluate circuit
    for (uint8_t c{0}; c < circuits.size(); c++) {
      circuits[c].eval(states, buffer);
    }

  }
}




}; // namespace Creates
}; // namespace Simulation
