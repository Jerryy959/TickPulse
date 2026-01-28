#pragma once
#include "types.hpp"
#include <optional>

namespace market_data {

// 这是你对外暴露的“获取数据接口”
// 任何数据源（假数据/回放/实时）都可以实现它
class IMarketDataProvider {
public:
    virtual ~IMarketDataProvider() = default;

    // 获取最新 L1 快照（如果暂时没有数据，返回 nullopt）
    virtual std::optional<L1> get_l1(const Instrument& inst) const = 0;

    // 获取最新 L2 快照
    virtual std::optional<L2> get_l2(const Instrument& inst, std::size_t depth = 10) const = 0;

    // 快捷接口：获取最新成交价/最新价
    virtual std::optional<Price> get_price(const Instrument& inst) const = 0;

    // 你可以自由扩展更多接口：
    // - get_volume()
    // - get_open_interest()
    // - get_settlement()
    // - get_trade_ticks(...)
};

} // namespace market_data
