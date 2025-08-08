#pragma once
#include <vector>





namespace Creates {

struct Connection{
  std::vector<bool> state;

  Connection();

  // take a reference of the node and add to the collection of the nodes 
  void connect(bool* node) {

  }

  // a connect call that will join 2 Connection object and destroy the "old" object
  void connect_combine(Connection* other) {
    
  }
};




}; // Creates

