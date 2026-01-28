#include "market_data/cme_gold_provider.hpp"
#include "dummy_source.hpp"
#include <algorithm>

namespace market_data {

static const DummySnapshotStore& as_store(const std::shared_ptr<const void>& p) {
    return *static_cast<const DummySnapshotStore*>(p.get());
}

CMEGoldFuturesProvider::CMEGoldFuturesProvider(std::shared_ptr<const void> snapshot_store)
    : store_(std::move(snapshot_store)) {}

std::optional<L1> CMEGoldFuturesProvider::get_l1(const Instrument& inst) const {
    // 这里将来可以做：合约合法性校验（比如 inst.symbol == "GC" or "MGC"）
    return as_store(store_).read_l1(inst);
}

std::optional<L2> CMEGoldFuturesProvider::get_l2(const Instrument& inst, std::size_t depth) const {
    auto l2opt = as_store(store_).read_l2(inst);
    if (!l2opt) return std::nullopt;

    // 裁剪 depth
    L2 out = *l2opt;
    if (out.bids.size() > depth) out.bids.resize(depth);
    if (out.asks.size() > depth) out.asks.resize(depth);
    return out;
}

std::optional<Price> CMEGoldFuturesProvider::get_price(const Instrument& inst) const {
    auto l1opt = get_l1(inst);
    if (!l1opt) return std::nullopt;
    return l1opt->last;
}

} // namespace market_data
