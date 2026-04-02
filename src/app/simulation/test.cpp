#include <array>
#include <cstdint>
#include <string>
#include <list>
#include <vector>

// 64 gates....
struct GateArray64 {
    enum Types: int8_t {
        Unknown = 0,
        Buffer,
        And,
        Or,
        Xor,
        Not,
        Nand,
        Nor,
        Xnor
    };
    std::array<uint_fast64_t, 2> current_inputs;
    std::array<uint_fast64_t, 2> new_inputs;
    std::string         name;
    // this holds the current state
    // this temporarily holds the old output
    uint_fast64_t                current_output;
    uint_fast64_t                old_output;
    Types               type;


    void operator()() {
        current_inputs = new_inputs;
        new_inputs = {0,0};
        old_output = current_output;
        
        if (type == Unknown);
        else if (type == Buffer) {
            current_output = current_inputs[0];
        } else if (type == And) {
            current_output = current_inputs[0] & current_inputs[1];
        } else if (type == Or) {
            current_output = current_inputs[0] | current_inputs[1];
        } else if (type == Xor) {
            current_output = current_inputs[0] ^ current_inputs[1];
        } else if (type == Not) {
            current_output =  ~current_inputs[0];
        } else if (type == Nand) {
            current_output = ~(current_inputs[0] & current_inputs[1]);
        } else if (type == Nor) {
            current_output = ~(current_inputs[0] | current_inputs[1]);
        } else if (type == Xnor) {
            current_output = ~(current_inputs[0] ^ current_inputs[1]);
        }
    }
};
struct Gate {
    enum class Types: int8_t {
        Unknown = 0,
        Buffer,
        And,
        Or,
        Xor,
        Not,
        Nand,
        Nor,
        Xnor
    };
    std::array<bool, 2> current_inputs;
    std::array<bool, 2> new_inputs;
    std::string         name;
    // this holds the current state
    // this temporarily holds the old output
    bool                current_output;
    bool                old_output;
    Types               type;

    void operator()() {
        current_inputs = new_inputs;
        new_inputs = {0,0};
        old_output = current_output;
        
        if (type == Types::Unknown);
        else if (type == Types::Buffer) {
            current_output = current_inputs[0];
        } else if (type == Types::And) {
            current_output = current_inputs[0] and current_inputs[1];
        } else if (type == Types::Or) {
            current_output = current_inputs[0] or current_inputs[1];
        } else if (type == Types::Xor) {
            current_output = current_inputs[0] != current_inputs[1];
        } else if (type == Types::Not) {
            current_output = not current_inputs[0];
        } else if (type == Types::Nand) {
            current_output = not (current_inputs[0] and current_inputs[1]);
        } else if (type == Types::Nor) {
            current_output = not (current_inputs[0] or current_inputs[1]);
        } else if (type == Types::Xnor) {
            current_output = current_inputs[0] == current_inputs[1];
        }
    }
};

// stuff that connect 2 Nodes...

template <typename T>
struct Wire {
    T* a;
    T* b;

    void operator()() {
        *a = *b = *a | *b;
    }
};

struct Circuit {
    // stuff that connects gates
    std::vector<Wire<bool>> wires;
    std::vector<bool*> external_node;
    std::vector<Circuit> internal_circuits;
    std::list<Gate> gates;

};

int main_(void) {
    bool running = 1;

    while (running) {
    }
    return 0;
}

