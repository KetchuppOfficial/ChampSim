#ifndef REPLACEMENT_PLRU_H
#define REPLACEMENT_PLRU_H

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "cache.h"
#include "modules.h"

class plru : public champsim::modules::replacement
{
public:
  explicit plru(CACHE* cache) : plru(cache, cache->NUM_SET, cache->NUM_WAY) {}
  plru(CACHE* cache, long num_set, long num_way) : replacement(cache), NUM_WAY(num_way)
  {
    if ((num_way & (num_way - 1)) != 0) {
      throw std::invalid_argument{"pseudo-lru requires associativity to be a power of 2"};
    }

    tree_bits.resize(num_set, std::vector<bool>(num_way - 1, 0));
  }

  long find_victim(uint32_t triggering_cpu, uint64_t instr_id, long set, const champsim::cache_block* current_set, champsim::address ip,
                   champsim::address full_addr, access_type type);

  void update_replacement_state(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip, champsim::address victim_addr,
                                access_type type, uint8_t hit);

private:
  long leaf_base() const noexcept { return NUM_WAY - 1; }
  long get_leaf(long node) const noexcept { return node - leaf_base(); }

  long NUM_WAY;
  std::vector<std::vector<bool>> tree_bits;
};

#endif // REPLACEMENT_PLRU_H
