/**
 * @file pwm.cpp
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

#include <thread>
#include <iostream>
#include <chrono>

#include "gpiodWrapper.hpp"

int main() {
    try {
        gpiodWrapper chip(0);

        // LED Pin 17
        chip.configurePin(17, Output);

        // PWM LED (50% Duty, 2 Hz)
        chip.pwmPin(17, 50, 2);

        std::this_thread::sleep_for(std::chrono::seconds(10));

        // Clean up
        chip.resetPin(17);

    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
