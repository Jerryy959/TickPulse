#include "market_data/cme_gold_provider.hpp"
#include "market_data/types.hpp"

// 注意：dummy_source.hpp 在 src/ 里，库内部使用；示例为了造数据直接 include（简单起见）
#include "../src/dummy_source.hpp"

#include <iostream>
#include <memory>

using namespace market_data;

int main() {
    auto store = std::make_shared<DummySnapshotStore>();

    Instrument gc_apr_2026{.symbol="GC", .contract="202604", .exchange="CME"};
    const auto key = DummySnapshotStore::key(gc_apr_2026);

    // 塞入假 L1
    store->l1_by_key[key] = L1{
        .bid = Level{.price=2049.8, .qty=12},
        .ask = Level{.price=2050.1, .qty=9},
        .last = Price{.value=2050.0},
        .ts_ns = 1700000000000000000LL
    };

    // 塞入假 L2
    L2 l2;
    l2.ts_ns = 1700000000000000000LL;
    l2.bids = {{2049.8, 12}, {2049.7, 20}, {2049.6, 15}};
    l2.asks = {{2050.1, 9}, {2050.2, 18}, {2050.3, 11}};
    store->l2_by_key[key] = l2;

    CMEGoldFuturesProvider provider(store);

    if (auto l1 = provider.get_l1(gc_apr_2026)) {
        std::cout << "L1 bid=" << l1->bid.price << "@" << l1->bid.qty
                  << " ask=" << l1->ask.price << "@" << l1->ask.qty
                  << " last=" << l1->last.value << "\n";
    }

    if (auto px = provider.get_price(gc_apr_2026)) {
        std::cout << "Price=" << px->value << "\n";
    }

    if (auto book = provider.get_l2(gc_apr_2026, 2)) {
        std::cout << "L2 depth=2\n";
        std::cout << " bids:\n";
        for (auto& lv : book->bids) std::cout << "  " << lv.price << "@" << lv.qty << "\n";
        std::cout << " asks:\n";
        for (auto& lv : book->asks) std::cout << "  " << lv.price << "@" << lv.qty << "\n";
    }

    return 0;
}
