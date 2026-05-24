#ifndef BRANCH_PAP_H
#define BRANCH_PAP_H

#include <array>
#include <bitset>
#include <utility>

#include "address.h"
#include "modules.h"
#include "msl/fwcounter.h"

class pap : champsim::modules::branch_predictor
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
  using BHR = std::bitset<kBranchHistoryRegisterWidth>;
  using PHT = std::array<Pattern, kPatternHistoryTableSize>;

  [[nodiscard]] static constexpr auto hash(champsim::address ip) { return ip.to<unsigned long>() % kPHTCount; }

  std::array<std::pair<BHR, PHT>, kPHTCount> tables_{};
};

#endif // BRANCH_PAP_H
