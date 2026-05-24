#include "pap.h"

bool pap::predict_branch(champsim::address ip) {
    const auto &[bhr, pht] = tables_[hash(ip)];
    const auto &pattern = pht[bhr.to_ullong()];
    return pattern.value() > (Pattern::maximum / 2);
}

void pap::last_branch_result(champsim::address ip, champsim::address branch_target, bool taken, uint8_t branch_type) {
    auto &[bhr, pht] = tables_[hash(ip)];
    auto &pattern = pht[bhr.to_ullong()];
    if (taken) {
        ++pattern;
    } else {
        --pattern;
    }

    bhr <<= 1;
    bhr[0] = taken;
}
