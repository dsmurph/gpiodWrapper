/**
 * @file taster.cpp
 * @class gpiodWrapper.hpp
 * @brief Lightweight C++ wrapper for libgpiod GPIO access.
 *
 * Simplifies GPIO input/output handling on Linux systems using libgpiod.
 * Supports basic operations such as set/get, toggling, and automatic cleanup.
 *
 * @author Kay (dsmurph)
 * @version 0.1.0
 * @date 2025-11-23
 * @license MIT
 *
 * Requires:
 *  - libgpiod (version 2.x recommended)
 *
 * GitHub: https://github.com/dsmurph/gpiodWrapper
 */

#include <iostream>
#include <chrono>
#include <thread>

#include "gpiodWrapper.hpp"

int main() {
    try {
        gpiodWrapper chip(0);
        chip.configurePin(18, Input);

        chip.attachInterrupt(18, RISING, []() {
            std::cout << "Taster gedrückt!\n";
        });

        std::this_thread::sleep_for(std::chrono::seconds(20));

        chip.detachInterrupt(18);
        chip.resetPin(18);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
