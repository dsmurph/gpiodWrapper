/**
 * @file highlow.cpp
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

int main() {
    gpiodWrapper chip(0);          // Open
    chip.configurePin(17, Output); // configure Pin 
    chip.setPin(17, HIGH);         // Set Pin HIGH
    chip.setPin(17, LOW);          // Set Pin LOW
}
