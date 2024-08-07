#include "gold.h" // for Symbol_table, Layout, Sized_relobj_file, Output_section

#include <iostream> // config.h must be #included before system headers

#include "elfcpp.h"
#include "layout.h" // must include before target-reloc.h
#include "symtab.h"
#include "target-reloc.h"
#include "target-select.h" // for Target_selector
#include "target.h"

namespace {
using namespace gold;

// The riscv target class.
template<int size, bool big_endian>
class Target_riscv : public Sized_target<size, big_endian>
{
public:
  // the constructor pass the target information to the base class.
  // In mips, Target_info is a static const member of Target_mips.
  // In sparc, it is a static private member of Target_sparc.
  // Here, we define a private member target_info to store the target
  // information.
  Target_riscv()
    : Sized_target<size, big_endian>(&riscv_info)
  {
    printf("Target_riscv: size=%d, big_endian=%d\n", size, big_endian);
  };

public:
  Sized_symbol<size>* make_symbol(const char*,
                                  elfcpp::STT,
                                  Object*,
                                  unsigned int,
                                  uint64_t)
  {
    printf("make_symbol\n");
    return new Sized_symbol<size>();
  }
  void gc_process_relocs(Symbol_table* symtab,
                         Layout* layout,
                         Sized_relobj_file<size, big_endian>* object,
                         unsigned int data_shndx,
                         unsigned int sh_type,
                         const unsigned char* prelocs,
                         size_t reloc_count,
                         Output_section* output_section,
                         bool needs_special_offset_handling,
                         size_t local_symbol_count,
                         const unsigned char* plocal_symbols)
  {
    printf("gc_process_relocs\n");
  }
  // Scan the relocations to look for symbol adjustments.
  void scan_relocs(Symbol_table* symtab,
                   Layout* layout,
                   Sized_relobj_file<size, big_endian>* object,
                   unsigned int data_shndx,
                   unsigned int sh_type,
                   const unsigned char* prelocs,
                   size_t reloc_count,
                   Output_section* output_section,
                   bool needs_special_offset_handling,
                   size_t local_symbol_count,
                   const unsigned char* plocal_symbols)
  {
    printf("scan_relocs\n");
  }
  // Relocate a section.
  void relocate_section(const Relocate_info<size, big_endian>*,
                        unsigned int sh_type,
                        const unsigned char* prelocs,
                        size_t reloc_count,
                        Output_section* output_section,
                        bool needs_special_offset_handling,
                        unsigned char* view,
                        typename elfcpp::Elf_types<size>::Elf_Addr view_address,
                        section_size_type view_size,
                        const Reloc_symbol_changes*)
  {
    printf("relocate_section\n");
  }

  void scan_relocatable_relocs(Symbol_table* symtab,
                               Layout* layout,
                               Sized_relobj_file<size, big_endian>* object,
                               unsigned int data_shndx,
                               unsigned int sh_type,
                               const unsigned char* prelocs,
                               size_t reloc_count,
                               Output_section* output_section,
                               bool needs_special_offset_handling,
                               size_t local_symbol_count,
                               const unsigned char* plocal_symbols,
                               Relocatable_relocs*)
  {
    printf("scan_relocatable_relocs\n");
  }
  void emit_relocs_scan(Symbol_table* symtab,
                        Layout* layout,
                        Sized_relobj_file<size, big_endian>* object,
                        unsigned int data_shndx,
                        unsigned int sh_type,
                        const unsigned char* prelocs,
                        size_t reloc_count,
                        Output_section* output_section,
                        bool needs_special_offset_handling,
                        size_t local_symbol_count,
                        const unsigned char* plocal_syms,
                        Relocatable_relocs* rr)
  {
    printf("emit_relocs_scan\n");
  }
  void relocate_relocs(
    const Relocate_info<size, big_endian>*,
    unsigned int sh_type,
    const unsigned char* prelocs,
    size_t reloc_count,
    Output_section* output_section,
    typename elfcpp::Elf_types<size>::Elf_Off offset_in_output_section,
    unsigned char* view,
    typename elfcpp::Elf_types<size>::Elf_Addr view_address,
    section_size_type view_size,
    unsigned char* reloc_view,
    section_size_type reloc_view_size)
  {
    printf("relocate_relocs\n");
  }

private:
  // The class which scans relocations.
  // The Scan class should provide two functions: local() and global()
  class Scan;

private:
  // The target_info must be passed to the base class `Target`.
  static const Target::Target_info riscv_info;

protected:
  void do_adjust_elf_header(unsigned char* view, int len);
};

// Target selector for RISC-V.
// endian have two options: true for big-endian, false for little-endian.
template<int size, bool big_endian>
class Target_selector_riscv : public Target_selector
{
public:
  Target_selector_riscv()
    : Target_selector(elfcpp::EM_RISCV,
                      size,
                      big_endian,
                      (size == 64 ? "elf64-littleriscv" : "elf32-littleriscv"),
                      (size == 64 ? "elf64-littleriscv" : "elf32-littleriscv"))
  {
    // std::cout << "Target_selector_riscv" << std::endl;
    printf("Target_selector_riscv: size=%d, big_endian=%d\n", size, big_endian);
  };

public:
  virtual Target* do_recognize(Input_file* input_file,
                               off_t offset,
                               int machine,
                               int osabi,
                               int abiversion);
  virtual Target* do_instantiate_target();
};

// instiantiate the target selector to register target in gold.
Target_selector_riscv<32, false> target_selector_riscv_32;
Target_selector_riscv<64, false> target_selector_riscv_64;

template<int size, bool big_endian>
inline void
Target_riscv<size, big_endian>::do_adjust_elf_header(unsigned char* view,
                                                     int len)
{
  printf("do_adjust_elf_header\n");
}

} // anonymous namespace
