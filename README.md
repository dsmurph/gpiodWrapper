# 🚀 gpiodWrapper

A lightweight and user-friendly C++ wrapper for **libgpiod 2.x**, designed to make GPIO access on Linux and Raspberry Pi simple, readable, and intuitive.

Instead of complex gpiod structures, this wrapper provides easy functions like:

```

configurePin()
setPin()
getPin()
resetPin()
attachInterrupt()
detachInterrupt()

```

Perfect for hobbyists, students, and projects where you just want GPIO control — without becoming a libgpiod expert.

---

## 📦 Dependencies

| Requirement | Version |
|-------------|---------|
| libgpiod    | ≥ 2.0   |
| C++         | ≥ C++17 |
| CMake       | optional for building |

Install libgpiod (Debian / Raspberry Pi OS):

```bash
sudo apt install libgpiod-dev
```

---

## ✨ Features

✔️ Simple GPIO input/output  
✔️ One-line pin configuration  
✔️ Interrupt support (RISING, FALLING, BOTH)  
✔️ Automatic cleanup  
✔️ No dynamic memory handling required  
✔️ Works with libgpiod 2.x  

---

## 🧩 Provided Functions

| Function | Description |
|----------|-------------|
| `gpiodWrapper(index)` | Opens `/dev/gpiochipX` |
| `configurePin(pin, Output/Input/Pullup/Pulldown)` | Configures pin direction |
| `setPin(pin, HIGH/LOW)` | Sets pin output state |
| `getPin(pin)` | Reads digital input |
| `resetPin(pin)` | Releases pin and clears configuration |
| `attachInterrupt(pin, edge, callback)` | Executes function on edge event |
| `detachInterrupt(pin)` | Stops monitoring interrupt on the pin |

---

## 🚀 Basic Example

```cpp

#include "gpiodWrapper.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    try {
        gpiodWrapper chip(0);          // /dev/gpiochip0 öffnen

        chip.configurePin(17, Output); // Pin als Output konfigurieren

        chip.setPin(17, HIGH);         // LED ein
        std::this_thread::sleep_for(std::chrono::seconds(1));

        chip.setPin(17, LOW);          // LED aus
        std::this_thread::sleep_for(std::chrono::seconds(1));

        chip.resetPin(17);             // Pin freigeben (optional)
    }
    catch (const std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }

    return 0;                          // Destruktor von gpiodWrapper wird automatisch aufgerufen
}

```

---

## ⚡ Interrupt Example

```cpp

#include "gpiodWrapper.hpp"
#include <iostream>

int main() {
    gpiodWrapper chip(0);                        // /dev/gpiochip0 öffnen

    chip.configurePin(22, Input);                // Pin als Input konfigurieren

    chip.attachInterrupt(22, RISING, [](int pin) // Pin als Interrupt konfigurieren
         {std::cout << "Interrupt! Pin: " << pin << std::endl;});

    while (true) {
        // Main application loop
    }
}

```
---

📁 examples/
blink.cpp
taster.cpp
pwm.cpp
interrupt.cpp
highlow.cpp
LEDTasterPWM.cpp
 
---

## 📦 Install build-essential and CMake 
```bash
sudo apt update
sudo apt upgrade -y
sudo apt install build-essential -y
sudo apt install cmake -y
```
---

## 🔧 Integration Example 

CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(gpiodWrapperExample)

set(CMAKE_CXX_STANDARD 17)

add_executable(example blink.cpp)
target_link_libraries(example gpiod)
target_include_directories(example PRIVATE include)
```
---
### 📦 Build Instructions

```bash
cd gpiodWrapper-master
mkdir src include build
mv gpiodWrapper.hpp include
mv *.cpp src
cd build
cmake ..
make
./blink

BASH
```bash
 g++ blink.cpp -o blink -lgpiod
```
---

## 📄 License

MIT License  
You are free to use, modify, and distribute this project.

---

## 🤝 Contributions

Pull requests and improvements are welcome.  
Feel free to fork, enhance, or suggest features.

---

⭐ If this wrapper helps your project — consider starring it on GitHub!
