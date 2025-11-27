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

#include <iostream>
#include <chrono>
#include <thread>

#include "gpiodWrapper.hpp"

int main() {
    try {
        // /dev/gpiochip0 open
        gpiodWrapper chip(0);
        // Configure pin as output
        chip.configurePin(17, Output);
        // Turn on LED
        chip.setPin(17, HIGH);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // // Turn off LED
        chip.setPin(17, LOW);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Unlock PIN (optional)
        chip.resetPin(17);
    }
    catch (const std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }

    // Destructor of gpiodWrapper is called automatically
    return 0;
}

```

---


## ⚡ Interrupt Example

```cpp

#include <iostream>

#include "gpiodWrapper.hpp"

int main() {
    // /dev/gpiochip0 open
    gpiodWrapper chip(0);

    // Configure pin as input
    chip.configurePin(22, Input);

    // Configure pin as interrupt
    chip.attachInterrupt(22, RISING, [](int pin) 
         {std::cout << "Interrupt! Pin: " << pin << std::endl;});

    while (true) {
        // Main application loop
    }
}

```
---


📁 examples/
```
 ├── blink.cpp         // Make individual LEDs blink
 ├── taster.cpp        // Query buttons
 ├── pwm.cpp           // PWM-control unit for LEDs or motors
 ├── interrupt.cpp     // Interrupt on pins
 ├── highlow.cpp       // Set Pin high/low
 └── LEDTasterPWM.cpp  // Combination: LED, push button & PWM simultaneously

```
 
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

CMakeLists.txt (change blink.cpp for your project)
```cmake
cmake_minimum_required(VERSION 3.10)

project(your_project VERSION 1.00 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/your_source_file.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} gpiod)


```
---


## 📦 Build Instructions

```bash
cd gpiodWrapper-master
mkdir src include build
mv gpiodWrapper.hpp include
mv *.cpp src
cd build
cmake ..
make
./blink
```
## 🔧 Your build station looks like this:
📁 gpiodWrapper/
```
  CMakeLists.txt
  📁 include
   ├── gpiodWrapper.hpp
  📁 src
   ├── blink.cpp
   ├── taster.cpp
   ├── pwm.cpp
   ├── interrupt.cpp
   ├── highlow.cpp
   └── LEDTasterPWM.cpp
  📁 build
   ├── blink //your Executable
   ├── ...

```

## or quickly
(The files to be compiled are located in one directory!)
```bash
 g++ blink.cpp -o blink -lgpiod
```
---

## 🛠️ Projekt 
Here's another nice example from a different project where I'm using gpiodWrapper.

```cpp
void faultCtrl() {
    // /dev/gpiochip0 open
    gpiodWrapper chip(0);
    // Configure Pin as Output 
    chip.configurePin(faultLED, Output);
    // Turn faultLED off (hardware-related)
    chip.setPin(faultLED, HIGH);
    while (true) {
       //In case of errors
       if (fault) {
          // Interval
          static unsigned long last = 0;
          // Set toggle variable
          static bool state = true;
          // Query timer
          if (millis() - last >= 500) {
             // Set Timer 
             last = millis();
             // toggle state
             state = !state;
             // Turn the LED on or off depending on the state (bool to PinValue)
             chip.setPin(faultLED, state ? HIGH : LOW);
           }
        } else { delay(50); }
    }
}
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
