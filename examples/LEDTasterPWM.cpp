/**
 * @file LEDTasterPWM.cpp
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
    try {
        gpiodWrapper chip(0);

        // LED Pin 17
        chip.configurePin(17, Output);

        // Taster Pin 18
        chip.configurePin(18, Input);

        // Interrupt RISING (Button pressed!)
        chip.attachInterrupt(18, RISING, []() {
            std::cout << "Button pressed!\n";
        });

        // Blink LED 10x
        chip.blinkPin(17, 500, 10);

        // PWM LED (50% Duty, 2 Hz)
        chip.pwmPin(17, 50, 2);

        // Detach/Pattern LED (HIGH/LOW every 100 ms)
        chip.detachPin(17, HIGH, LOW, 100);

        std::this_thread::sleep_for(std::chrono::seconds(10));

        // Clean up
        chip.detachInterrupt(18);
        chip.resetPin(17);
        chip.resetPin(18);

    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
