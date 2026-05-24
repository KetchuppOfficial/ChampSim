#include "gag.h"

bool gag::predict_branch(champsim::address ip) {
    const auto &pattern = pattern_history_table_[branch_history_register_.to_ullong()];
    return pattern.value() > (Pattern::maximum / 2);
}

void gag::last_branch_result(champsim::address ip, champsim::address branch_target, bool taken, uint8_t branch_type) {
    auto &pattern = pattern_history_table_[branch_history_register_.to_ullong()];
    if (taken) {
        ++pattern;
    } else {
        --pattern;
    }

    branch_history_register_ <<= 1;
    branch_history_register_[0] = taken;
}
