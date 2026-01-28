#pragma once
#include "market_data/types.hpp"
#include <optional>
#include <unordered_map>

namespace market_data {

struct DummySnapshotStore {
    // 后面可以替换为：共享内存、ring buffer、网络订阅、数据库、回放文件等
    std::unordered_map<std::string, L1> l1_by_key;
    std::unordered_map<std::string, L2> l2_by_key;

    static std::string key(const Instrument& inst) {
        return inst.exchange + ":" + inst.symbol + ":" + inst.contract;
    }

    std::optional<L1> read_l1(const Instrument& inst) const {
        auto it = l1_by_key.find(key(inst));
        if (it == l1_by_key.end()) return std::nullopt;
        return it->second;
    }

    std::optional<L2> read_l2(const Instrument& inst) const {
        auto it = l2_by_key.find(key(inst));
        if (it == l2_by_key.end()) return std::nullopt;
        return it->second;
    }
};

} // namespace market_data
