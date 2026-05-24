#include "gap.h"

bool gap::predict_branch(champsim::address ip) {
    const auto &pht = pattern_history_tables_[hash(ip)];
    const auto &pattern = pht[branch_history_register_.to_ullong()];
    return pattern.value() > (Pattern::maximum / 2);
}

void gap::last_branch_result(champsim::address ip, champsim::address branch_target, bool taken, uint8_t branch_type) {
    auto &pht = pattern_history_tables_[hash(ip)];
    auto &pattern = pht[branch_history_register_.to_ullong()];
    if (taken) {
        ++pattern;
    } else {
        --pattern;
    }

    branch_history_register_ <<= 1;
    branch_history_register_[0] = taken;
}
