#include "riscv.h"

// #include "target-reloc.h"
// #include "symtab.h"

namespace {
using namespace gold;

// template<int size, bool big_endian>
// inline void
// Target_riscv<size, big_endian>::scan_relocs(
//   Symbol_table* symtab,
//   Layout* layout,
//   Sized_relobj_file<size, big_endian>* object,
//   unsigned int data_shndx,
//   unsigned int sh_type,
//   const unsigned char* prelocs,
//   size_t reloc_count,
//   Output_section* output_section,
//   bool needs_special_offset_handling,
//   size_t local_symbol_count,
//   const unsigned char* plocal_symbols)
// {
// }

template<int size, bool big_endian>
class Target_riscv<size, big_endian>::Scan
{
public:
  Scan() {
    printf("Target_riscv::Scan\n");
  }
};

template<int size, bool big_endian>
const Target::Target_info Target_riscv<size, big_endian>::riscv_info =
{
  size,                 // size
  big_endian,           // is_big_endian
  elfcpp::EM_RISCV,      // machine_code
  true,                 // has_make_symbol
  false,                // has_resolve
  false,                // has_code_fill
  true,                 // is_default_stack_executable
  false,                // can_icf_inline_merge_sections
  '\0',                 // wrap_char
  size == 32 ? "/lib/ld.so.1" : "/lib64/ld.so.1",      // dynamic_linker
  0x400000,             // default_text_segment_address
  64 * 1024,            // abi_pagesize (overridable by -z max-page-size)
  4 * 1024,             // common_pagesize (overridable by -z common-page-size)
  false,                // isolate_execinstr
  0,                    // rosegment_gap
  elfcpp::SHN_UNDEF,    // small_common_shndx
  elfcpp::SHN_UNDEF,    // large_common_shndx
  0,                    // small_common_section_flags
  0,                    // large_common_section_flags
  NULL,                 // attributes_section
  NULL,                 // attributes_vendor
  "__start",		// entry_symbol_name
  32,			// hash_entry_size
  elfcpp::SHT_PROGBITS,	// unwind_section_type
};

template<int size, bool big_endian>
inline Target*
Target_selector_riscv<size, big_endian>::do_recognize(Input_file* input_file,
                                                      off_t offset,
                                                      int machine,
                                                      int osabi,
                                                      int abiversion)
{
  printf("Target_selector_riscv::do_recognize\n");
  if (machine == elfcpp::EM_RISCV)
    return this->do_instantiate_target();
  return NULL;
}

template<int size, bool big_endian>
Target*
Target_selector_riscv<size, big_endian>::do_instantiate_target()
{
  std::cout << "Target_selector_riscv::do_instantiate_target" << std::endl;
  return new Target_riscv<size, big_endian>();
}
// template<int size, bool big_endian>
// Target* Target_selector_riscv::do_recognize(Input_file* input_file, off_t
// offset,
//                                int machine, int osabi, int abiversion) {
//   return new Target_riscv<size, big_endian>();
// }
// template<int size, bool big_endian>
// void
// Target_riscv<size, big_endian>::scan_relocs(
//   Symbol_table* symtab,
//   Layout* layout,
//   Sized_relobj_file<size, big_endian>* object,
//   unsigned int data_shndx,
//   unsigned int sh_type,
//   const unsigned char* prelocs,
//   size_t reloc_count,
//   Output_section* output_section,
//   bool needs_special_offset_handling,
//   size_t local_symbol_count,
//   const unsigned char* plocal_symbols)
// {
//   typedef Target_riscv<size, big_endian> Riscv;
// };
} // anonymous namespace