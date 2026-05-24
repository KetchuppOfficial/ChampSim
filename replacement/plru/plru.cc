#include "plru.h"

long plru::find_victim(uint32_t triggering_cpu, uint64_t instr_id, long set, const champsim::cache_block* current_set, champsim::address ip,
                       champsim::address full_addr, access_type type)
{
  for (long way = 0; way != NUM_WAY; ++way) {
    if (!current_set[way].valid) {
      return way;
    }
  }

  long node = 0;

  while (node < leaf_base()) {
    if (tree_bits[set][node]) {
      node = 2 * node + 2;
    } else {
      node = 2 * node + 1;
    }
  }

  return get_leaf(node);
}

void plru::update_replacement_state(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip,
                                    champsim::address victim_addr, access_type type, uint8_t hit)
{
  long node = leaf_base() + way;
  while (node > 0) {
    const long parent = (node - 1) / 2;
    const bool accessed_left_child = (node == (2 * parent + 1));
    tree_bits[set][parent] = accessed_left_child;
    node = parent;
  }
}
