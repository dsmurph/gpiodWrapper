/**
 * @file blink.cpp
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
        // /dev/gpiochip0 open
        gpiodWrapper chip(0);
        // Pin17 as Output
        chip.configurePin(17, Output);

        // Simple blinking (pin, interval in ms, repetitions)
        chip.blinkPin(17, 500, 10);

        std::this_thread::sleep_for(std::chrono::seconds(6));
        // Optional Pin reset
        chip.resetPin(17);

    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
