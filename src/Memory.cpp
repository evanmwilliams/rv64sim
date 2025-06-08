#include "rv64sim/Memory.hpp"

Memory::Page *Memory::get_or_allocate_page(rv64sim::addr_t addr) {
  auto page_addr = addr & ~(PAGE_SIZE - 1); // Align to page boundary
  auto it = pages.find(page_addr);
  if (it != pages.end()) {
    return it->second.get(); // Return existing page
  }

  // Allocate a new page
  auto new_page = std::make_unique<Page>();
  pages[page_addr] = std::move(new_page);
  return pages[page_addr].get();
}

const Memory::Page *Memory::get_page(uint64_t addr) const {
  uint64_t page_num = addr / PAGE_SIZE;
  auto it = pages.find(page_num);
  return it != pages.end() ? it->second.get() : nullptr;
}

void Memory::store_byte(uint64_t addr, uint8_t val) {
  auto *page = get_or_allocate_page(addr);
  (*page)[addr % PAGE_SIZE] = val;
}

uint8_t Memory::load_byte(uint64_t addr) const {
  auto *page = get_page(addr);
  if (!page)
    throw std::runtime_error("Invalid memory read");
  return (*page)[addr % PAGE_SIZE];
}

void Memory::store_bytes(uint64_t addr, const uint8_t *data, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    store_byte(addr + i, data[i]);
  }
}

void Memory::load_bytes(uint64_t addr, uint8_t *buffer, size_t len) const {
  for (size_t i = 0; i < len; ++i) {
    buffer[i] = load_byte(addr + i);
  }
}