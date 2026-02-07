# C++ High Frequency Trading Core

[![C++20](https://img.shields.io/badge/C++-20-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.0+-green.svg)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A **low-latency matching engine** designed for high-frequency trading simulations. Implemented in C++20, this repository features a price-time priority order book, efficient order management, and minimal dynamic allocation for maximum performance.

## 🚀 Features

- **Price-Time Priority**: Standard matching algorithm for fair order execution.
- **Low Latency**: Optimized data structures (std::map for price levels, std::list for order queues).
- **Supports Partial Fills**: Automatic handling of remaining quantities.
- **Limit Orders**: Support for Buy and Sell limit orders.
- **Market Impact Simulation**: Real-time visualization of the order book state.

## 📁 Project Structure

```
cpp-high-frequency-trading-core/
├── src/
│   ├── order.h           # Order data structure
│   ├── order_book.h      # Matching engine logic
│   └── main.cpp          # Simulation entrypoint
├── CMakeLists.txt
└── README.md
```

## 🛠️ Quick Start

```bash
# Clone
git clone https://github.com/Shivay00001/cpp-high-frequency-trading-core.git
cd cpp-high-frequency-trading-core

# Build
mkdir build && cd build
cmake ..
cmake --build .

# Run Matching Engine
./HFTCore
```

## 📄 License

MIT License
