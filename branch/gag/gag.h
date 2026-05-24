#ifndef BRANCH_GAG_H
#define BRANCH_GAG_H

#include <array>
#include <bitset>

#include "address.h"
#include "modules.h"
#include "msl/fwcounter.h"

class gag : champsim::modules::branch_predictor
{
public:
  using branch_predictor::branch_predictor;

  bool predict_branch([[maybe_unused]] champsim::address ip);
  void last_branch_result([[maybe_unused]] champsim::address ip, [[maybe_unused]] champsim::address branch_target, bool taken, uint8_t branch_type);

private:
  static constexpr std::size_t kBranchHistoryRegisterWidth = 14;
  static constexpr std::size_t kPatternHistoryTableSize = (1 << kBranchHistoryRegisterWidth);

  using Pattern = champsim::msl::fwcounter<2>;

  std::bitset<kBranchHistoryRegisterWidth> branch_history_register_{};
  std::array<Pattern, kPatternHistoryTableSize> pattern_history_table_{};
};

#endif // BRANCH_GAG_H
