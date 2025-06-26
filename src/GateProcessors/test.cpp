#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>




class Gate {
  const std::string type;
  
  std::vector<std::vector<bool*>> inp;

  std::vector<bool*> state;
public:
  Gate(std::string type_):
    type{type_}{};
  void add_inp(bool& inp_, int target) {
    inp[target].push_back(&inp_);
  }
  std::vector<bool&>& step_process() {
    
  };
};








