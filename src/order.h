#pragma once
#include <cstdint>
#include <iostream>

enum class OrderType { BUY, SELL };

struct Order {
  uint64_t id;
  OrderType type;
  double price;
  uint32_t quantity;
  uint32_t initial_quantity;

  Order(uint64_t id, OrderType type, double price, uint32_t qty)
      : id(id), type(type), price(price), quantity(qty), initial_quantity(qty) {
  }
};
