#pragma once
#include <cstdint>
#include <vector>


namespace Creates {

struct Connection{
  std::vector<bool*> state;

  Connection();

  // take a reference of the node and add to the collection of the nodes 
  void connect(bool& node);

  // a connect call that will join 2 Connection object and destroy the "old" object
  void connect_combine(Connection& other);
};


// a gate instance???
struct Gates {
  uint8_t type;
  // may be different size but at most its 3
  // the first bool is always the output
  std::vector<bool> state;
  
};


// a circuit object is a stucture of simulation instance where it has its own process and might have differenet process speed
struct Circuit {
  bool type;

};

// struff that handles input and output
struct Input{
  uint8_t type;
  uint8_t state;
};

struct Output {
  uint8_t type;
  uint64_t state;
};




}; // Creates

