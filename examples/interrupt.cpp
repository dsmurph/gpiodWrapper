/**
 * @file interrupt.cpp
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
#include <thread>
#include <chrono>

#include "gpiodWrapper.hpp"

int main() {
    // Chip open
    gpiodWrapper chip(0);

    // Configure Pin (GPIO18 Input)
    chip.configurePin(18, Input);

    // Interrupt with callback WITHOUT parameters
    chip.attachInterrupt(18, RISING, []() {
        std::cout << "Button pressed!\n";
    });

    // Interrupt with callback and pin parameters
    chip.attachInterrupt(18, FALLING, [](int pin) {
        std::cout << "Pin " << pin << " has triggered a FALLING event!\n";
    });

    std::cout << "Interrupts are active. Wait 15 seconds....\n";

    // Test duration (15 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(15));

    std::cout << ""End interrupts...\n";
    chip.detachInterrupt(18);

    return 0;
}
