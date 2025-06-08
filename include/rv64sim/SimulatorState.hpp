#pragma once

#include "Memory.hpp"
#include "arch.hpp"
#include <unordered_map>

class SimulatorState {
public:
  rv64sim::reg_t pc;
  rv64sim::reg_t registers[32]; // x0 to x31
  Memory memory;

  void reset();
};