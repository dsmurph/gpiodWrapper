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

#include "gpiodWrapper.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Chip öffnen
    gpiodWrapper chip(0);

    // Pin konfigurieren (z.B. GPIO18 als Input mit Pull-Up)
    chip.configurePin(18, Input);

    // Interrupt mit Callback OHNE Parameter
    chip.attachInterrupt(18, RISING, []() {
        std::cout << "Taster gedrückt! (ohne Parameter)\n";
    });

    // Interrupt mit Callback MIT Pin-Parameter
    chip.attachInterrupt(18, FALLING, [](int pin) {
        std::cout << "Pin " << pin << " hat ein FALLING Event ausgelöst!\n";
    });

    std::cout << "Interrupts aktiv. Warte 15 Sekunden...\n";

    // Test-Dauer (z.B. 15 Sekunden)
    std::this_thread::sleep_for(std::chrono::seconds(15));

    std::cout << "Beende Interrupts...\n";
    chip.detachInterrupt(18);

    return 0;
}
