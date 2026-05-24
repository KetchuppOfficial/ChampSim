#ifndef BRANCH_GAP_H
#define BRANCH_GAP_H

#include <array>
#include <bitset>

#include "address.h"
#include "modules.h"
#include "msl/fwcounter.h"

class gap : champsim::modules::branch_predictor
{
public:
  using branch_predictor::branch_predictor;

  bool predict_branch(champsim::address ip);
  void last_branch_result(champsim::address ip, champsim::address branch_target, bool taken, uint8_t branch_type);

private:
  static constexpr std::size_t kBits = 14;
  static constexpr std::size_t kBranchHistoryRegisterWidth = kBits / 2;
  static constexpr std::size_t kPatternHistoryTableSize = (1 << kBranchHistoryRegisterWidth);
  static constexpr std::size_t kPHTCount = kPatternHistoryTableSize;

  using Pattern = champsim::msl::fwcounter<2>;
  using PHT = std::array<Pattern, kPatternHistoryTableSize>;

  [[nodiscard]] static constexpr auto hash(champsim::address ip) { return ip.to<unsigned long>() % kPHTCount; }

  std::bitset<kBranchHistoryRegisterWidth> branch_history_register_{};
  std::array<PHT, kPHTCount> pattern_history_tables_{};
};

#endif // BRANCH_GAP_H
