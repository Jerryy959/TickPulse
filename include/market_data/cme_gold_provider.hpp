#pragma once
#include "market_data_provider.hpp"
#include <memory>

namespace market_data {

class CMEGoldFuturesProvider final : public IMarketDataProvider {
public:
    // 依赖注入：你可以把任何“数据存储/数据源”塞进来
    // 这里用 DummySnapshotStore 作为占位实现
    explicit CMEGoldFuturesProvider(std::shared_ptr<const void> snapshot_store);

    std::optional<L1> get_l1(const Instrument& inst) const override;
    std::optional<L2> get_l2(const Instrument& inst, std::size_t depth = 10) const override;
    std::optional<Price> get_price(const Instrument& inst) const override;

private:
    // 为了保持头文件稳定，这里用 void 做 type-erasure
    // 也可以直接写成 std::shared_ptr<const DummySnapshotStore>
    std::shared_ptr<const void> store_;
};

} // namespace market_data
