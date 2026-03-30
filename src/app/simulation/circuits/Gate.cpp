#include "../objects.hpp"
#include <cstdint>

namespace Creates {

namespace Simulation {

Gates::Gates(const GateTypes type):
  _type{type} {

  output.fill(0xffffffff);
}

template <typename Iteratable, typename Item, typename Reff>
void array_apply(const Iteratable& arr, const Item fill, Reff& reff, const uint32_t count) {
  for (uint32_t i{0}; i < count; i++) {
    reff[arr[i]] = fill;
  }
}

// id
void Gates::eval(std::vector<bool>& state_ref, std::vector<bool>& buffer_ref) {
  switch (_type) {
    case GateTypes::Not: {
      array_apply(output, !(state_ref[input[0]]), buffer_ref, 16); break;
    } case GateTypes::Buffer: {
      array_apply(output, state_ref[input[0]], buffer_ref, 16); break;
    } case GateTypes::And: {
      array_apply(output, state_ref[input[0]] and state_ref[input[1]], buffer_ref, 16); break;
    } case GateTypes::Nand: {
      array_apply(output, !(state_ref[input[0]] and state_ref[input[1]]), buffer_ref, 16); break;
    } case GateTypes::Or: {
      array_apply(output, state_ref[input[0]] or state_ref[input[1]], buffer_ref, 16); break;
    } case GateTypes::Nor: {
      array_apply(output, !(state_ref[input[0]] or state_ref[input[1]]), buffer_ref, 16); break;
    } case GateTypes::Xor: {
      array_apply(output, state_ref[input[0]] == state_ref[input[1]], buffer_ref, 16); break;
    } case GateTypes::Xnor: {
      array_apply(output, state_ref[input[0]] != state_ref[input[1]], buffer_ref, 16); break;
    }
  }
}

// connect
void Gates::connect_input(uint32_t inp, const uint8_t index) {
  input[index] = inp;
}

// connect?
// int Gates::connect_out(bool& outp) {
//   // if the address of the output is already added
//   bool already_in = false;
//   // check if the address is already added
//   for (uint8_t i{0}; i < 16; i++) {
//     if (&outp == output[i]) {already_in = true;break;}
//   }
//   // return if the pointer alr on the output
//   if (already_in) return 0;
//
//   // search for slot thats not occupied and apply it
//   for (uint8_t i{0}; i < 16; i++) {
//     if (output[i] == 0) {
//       output[i] = &outp;
//       already_in = true;
//     }
//   }
//   // call error callback
//   if (not already_in) {
//     return -1;
//   };
//
//   return 0;
// }

// faster?
int Gates::connect_out(uint32_t outp) {
  
  uint8_t port{16};
  for (uint8_t i{0}; i < 16; i++) {
    if (port == 16 and output[i] == 0) {
      port = i;
    } else if (output[i] == outp) return 0; // already connected
  }
  // the slot is full try using extra OR gate
  if (port == 16) return -1;
  
  output[port] = outp;
  // connection success
  return 0;
}

void Gates::remove_out(uint32_t outp) {
  for (uint8_t i{0}; i < 16; i++) {
    if (output[i] == outp) output[i] = 0;
  }
}

}; // namespace Creates

}; // namespace Simulation
