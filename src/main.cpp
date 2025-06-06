#include <elfio/elfio.hpp>
#include <iomanip>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <file.elf>\n";
    return 1;
  }

  ELFIO::elfio reader;
  if (!reader.load(argv[1])) {
    std::cerr << "Failed to load ELF file.\n";
    return 1;
  }

  std::cout << "ELF file class    : ";
  if (reader.get_class() == ELFIO::ELFCLASS32) {
    std::cout << "ELF32\n";
  } else {
    std::cout << "ELF64\n";
  }

  std::cout << "ELF file encoding : ";
  if (reader.get_encoding() == ELFIO::ELFDATA2LSB) {
    std::cout << "Little endian\n";
  } else {
    std::cout << "Big endian\n";
  }

  ELFIO::Elf_Half sec_num = reader.sections.size();
  std::cout << "Number of sections: " << sec_num << "\n";
  for (int i = 0; i < sec_num; ++i) {
    ELFIO::section *psec = reader.sections[i];
    std::cout << "  [" << std::setw(2) << i << "] " << std::left
              << std::setw(20) << psec->get_name() << std::right << std::setw(6)
              << psec->get_size() << "\n";
    const char *p = reader.sections[i]->get_data();
    if (psec->get_type() == ELFIO::SHT_SYMTAB) {
      const ELFIO::symbol_section_accessor symbols(reader, psec);
      for (unsigned int j = 0; j < symbols.get_symbols_num(); ++j) {
        std::string name;
        ELFIO::Elf64_Addr value;
        ELFIO::Elf_Xword size;
        unsigned char bind;
        unsigned char type;
        ELFIO::Elf_Half section_index;
        unsigned char other;
        symbols.get_symbol(j, name, value, size, bind, type, section_index,
                           other);
        std::cout << "    Symbol: " << name << " (value: 0x" << std::hex
                  << value << ", size: " << std::dec << size
                  << ", bind: " << (int)bind << ", type: " << (int)type
                  << ", section index: " << section_index
                  << ", other: " << (int)other << ")\n";
      }
    }
  }

  ELFIO::Elf_Half seg_num = reader.segments.size();
  std::cout << "Number of segments: " << seg_num << "\n";
  for (int i = 0; i < seg_num; ++i) {
    const ELFIO::segment *pseg = reader.segments[i];
    std::cout << "  [" << std::setw(2) << i << "] 0x" << std::hex
              << std::setw(8) << pseg->get_virtual_address()
              << "  size: " << std::dec << std::setw(6) << pseg->get_file_size()
              << "  type: " << std::setw(10) << pseg->get_type() << "\n";
    const char *p = reader.segments[i]->get_data();
  }

  return 0;
}
