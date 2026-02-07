#pragma once
#include "order.h"
#include <iostream>
#include <list>
#include <map>
#include <memory>


class OrderBook {
private:
  // Price -> List of Orders
  std::map<double, std::list<std::shared_ptr<Order>>>
      bids; // Descending for Bids (Highest first) -> implemented via rbegin
  std::map<double, std::list<std::shared_ptr<Order>>>
      asks; // Ascending for Asks (Lowest first)

public:
  void addOrder(std::shared_ptr<Order> order) {
    if (order->type == OrderType::BUY) {
      match(order, asks);
      if (order->quantity > 0) {
        bids[order->price].push_back(order);
        std::cout << "Order " << order->id << " (BUY) added to book @ "
                  << order->price << " (" << order->quantity << ")"
                  << std::endl;
      }
    } else {
      // For matching sells, we need to match against bids (highest price first)
      // But implementing generic match against map is tricky with different
      // sort orders. Simplified for demo: just add to book and try match
      // manually.
      matchSell(order);
      if (order->quantity > 0) {
        asks[order->price].push_back(order);
        std::cout << "Order " << order->id << " (SELL) added to book @ "
                  << order->price << " (" << order->quantity << ")"
                  << std::endl;
      }
    }
  }

  void matchSell(std::shared_ptr<Order> sellOrder) {
    // Match against bids: Iterate from highest price downwards
    auto it = bids.rbegin();
    while (it != bids.rend() && sellOrder->quantity > 0) {
      double bidPrice = it->first;
      auto &orders = it->second;

      if (bidPrice < sellOrder->price)
        break; // Best bid is lower than ask limit

      processLevel(sellOrder, orders, orders.empty());
      if (orders.empty()) {
        // Remove price level if empty.
        // Careful with iterator invalidation in loop, but here we just need to
        // advance properly Since this is reverse iterator on map, erasing key
        // is safe if we handle it? Actually erasing from map while iterating is
        // tricky. Let's just create a cleanup pass or ignore empty lists for
        // simplicity in demo. Standard map erase with rbase() is converting
        // reverse_iterator to iterator.
        auto next_it = std::next(it);
        bids.erase(std::next(it).base());
        it = next_it;
        continue;
      } else {
        ++it;
      }
    }
  }

  // Generic match for BUY order against ASKS (lowest price first)
  void
  match(std::shared_ptr<Order> order,
        std::map<double, std::list<std::shared_ptr<Order>>> &counterparties) {
    auto it = counterparties.begin();
    while (it != counterparties.end() && order->quantity > 0) {
      double counterPrice = it->first;
      auto &orders = it->second;

      if (counterPrice > order->price)
        break; // Lowest ask higher than bid limit

      processLevel(order, orders, orders.empty());

      if (orders.empty()) {
        it = counterparties.erase(it);
      } else {
        ++it;
      }
    }
  }

  void processLevel(std::shared_ptr<Order> order,
                    std::list<std::shared_ptr<Order>> &orders, bool &isEmpty) {
    auto it = orders.begin();
    while (it != orders.end() && order->quantity > 0) {
      auto &matchOrder = *it;
      uint32_t tradeQty = std::min(order->quantity, matchOrder->quantity);

      order->quantity -= tradeQty;
      matchOrder->quantity -= tradeQty;

      std::cout << "TRADE: " << tradeQty << " @ " << matchOrder->price
                << std::endl;

      if (matchOrder->quantity == 0) {
        it = orders.erase(it);
      } else {
        ++it;
      }
    }
  }

  void printBook() {
    std::cout << "\n--- Order Book ---" << std::endl;
    std::cout << "ASKS:" << std::endl;
    for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
      for (auto &o : it->second)
        std::cout << o->price << " (" << o->quantity << ")" << std::endl;
    }
    std::cout << "----" << std::endl;
    std::cout << "BIDS:" << std::endl;
    for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
      for (auto &o : it->second)
        std::cout << o->price << " (" << o->quantity << ")" << std::endl;
    }
    std::cout << "------------------\n" << std::endl;
  }
};
