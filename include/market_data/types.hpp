#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace market_data {

struct Price {
    double value = 0.0;
};

struct Level {
    double price = 0.0;
    std::int64_t qty = 0;
};

struct L1 {
    // 最基础：买一/卖一/最新价
    Level bid;
    Level ask;
    Price last;
    std::int64_t ts_ns = 0; // 时间戳（纳秒）
};

struct L2 {
    // 简化版深度（可扩展为 N 档，或包含订单簿增量）
    std::vector<Level> bids; // 从高到低
    std::vector<Level> asks; // 从低到高
    std::int64_t ts_ns = 0;
};

struct Instrument {
    // CME 黄金期货常见：GC / MGC；到期月可以用 YYYYMM 或类似编码
    std::string symbol;     // e.g. "GC"
    std::string contract;   // e.g. "202604"  (2026年4月)
    std::string exchange;   // e.g. "CME"
};

} // namespace market_data
