#include "order_book.h"
#include <iostream>
#include <memory>


int main() {
  OrderBook book;

  std::cout << "Initializing HFT Simulation..." << std::endl;

  // Seed the book
  book.addOrder(std::make_shared<Order>(1, OrderType::SELL, 100.50, 100));
  book.addOrder(std::make_shared<Order>(2, OrderType::SELL, 101.00, 50));
  book.addOrder(std::make_shared<Order>(3, OrderType::BUY, 99.00, 100));

  book.printBook();

  // Aggressive Buy that eats into simulated spread
  std::cout << "Submitting Market Aggressive BUY..." << std::endl;
  book.addOrder(std::make_shared<Order>(4, OrderType::BUY, 100.50, 120));

  book.printBook();

  return 0;
}
