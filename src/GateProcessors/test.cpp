#include "objects.hpp"
#include <iostream>
#include <vector>



std::vector<bool>& Circuit::step(int step_size) {
  for (int i = 0; i < step_size; i++) {
    
  }

  return interface_node;
}










void test() {
  
  Circuit dat;

}

// attemp 3
struct process_type {
  // what type of gate is it
  std::vector<int> type;
  
  // containes the NODE id of each gates
  std::vector<std::vector<int>> nodes;
  
  // current state of each gates
  std::vector<bool> states;
};


struct process_group {
  std::vector<process_type> groups;
};





