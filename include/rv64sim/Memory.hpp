#pragma once
#include "arch.hpp"
#include <array>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>

constexpr uint64_t PAGE_SIZE = 4096; // 4 KiB

class Memory {
public:
  using Page = std::array<uint8_t, PAGE_SIZE>;
  void store_byte(rv64sim::addr_t addr, uint8_t val);
  uint8_t load_byte(rv64sim::addr_t addr) const;
  void store_bytes(rv64sim::addr_t addr, const uint8_t *data, size_t size);
  void load_bytes(rv64sim::addr_t addr, uint8_t *data, size_t size) const;
  Page *get_or_allocate_page(rv64sim::addr_t addr);
  const Page *get_page(rv64sim::addr_t addr) const;

private:
  std::unordered_map<uint64_t, std::unique_ptr<Page>> pages;
};
