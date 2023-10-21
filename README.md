# Key Jackpot - Digital Twin

## Description

This is a digital twin of a digital system called **Key Jackpot**, inspired by the game "Key Master".
The digital twin will mirror everything the physical system does, and it can also control it by a serial communication using MQTT.
This project is made for the discipline PCS3645.

## Install Guide

In order to install the digital twin, you will need to install:

- C++ compiler, such as g++, MSVC or CLang++;
- CMake (version 3.17 or superior);
- vcpkg, installing the following packages:
  - GLFW3;
  - GLAD;
- A build tool, such as MinGW Makefile, Ninja or Visual Studio Code;

After cloning the repository, run the following command to build the source files:

```bash
cmake -S . -B build/ -G <choose your build tool> -DCMAKE_TOOLCHAIN_FILE="/your_path_to_vcpkg_installation_folder/scripts/buildsystems/vcpkg.cmake"
```

Use your build tool to generate the executable (the following command uses Ninja as example).

```bash
ninja -C  build/
```

It is recommended to copy these commands into a .cmd or .sh file, since it is necessary to do this everytime you compile this program.

The executable can be found inside the `build/` folder, with the specific path depending on the build tool used.
