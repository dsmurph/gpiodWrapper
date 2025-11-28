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


// Include class gpiodWrapper
#include "gpiodWrapper.hpp"

int main() {
    try {

        // /dev/gpiochip0 open        
        gpiodWrapper chip(0);
        
        // Internal pull-up resistor ensures a clear high signal
        chip.configurePin(18, Pullup);
        
        // Interrupt on falling edge
        chip.attachInterrupt(18, FALLING, []() {
            std::cout << "Button pressed!\n";
        });
        
        // Give it some time for the issue
        std::this_thread::sleep_for(std::chrono::seconds(20));

        // Interrupt reset
        chip.detachInterrupt(18);
        
        // Pin reset
        chip.resetPin(18);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
