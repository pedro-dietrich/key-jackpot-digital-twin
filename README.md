# Key Jackpot - Digital Twin

## Description

This is a digital twin of a digital system called **Key Jackpot**, inspired by the game "Key Master".
The digital twin will mirror everything the physical system does, and it can also control it by a serial communication through USB.

This project is made for the discipline PCS3645.

## Install Guide

In order to install the digital twin, you will need to install:

- C++ compiler, such as g++, MSVC or CLang++;
- CMake (version 3.17 or superior);
- vcpkg;
- A build tool, such as MinGW Makefile, Ninja or Visual Studio 2022;

---

To install the packages run the following vcpkg command:

```bash
vcpkg install
```

It installs all packages specified in the `vcpkg.json` file. Usually, running CMake also runs this command by default.

---

After cloning the repository, run the following command to build the source files.
The CMake website has a list with all the build tools available.
The `-DCMAKE_TOOLCHAIN_FILE` option receives the full path to the `vcpkg.cmake` file in your vcpkg installation, allowing CMake to find the installed libraries.

*Note: It is also possible to install the packages manually, using the `-DCMAKE_PREFIX_PATH="/path_to_package_1;/path_to_package_2"` option to list the packages paths, separated by `;`. If using this method, there is no reason to set the `-DCMAKE_TOOLCHAIN_FILE` option.*

```bash
cmake -S . -B build/ -G <choose your build tool> -DCMAKE_TOOLCHAIN_FILE="/your_path_to_vcpkg_installation_folder/scripts/buildsystems/vcpkg.cmake"
```

---

Use your build tool to generate the executable (the following command uses Ninja as example).

```bash
ninja -C build/
```

---

It is recommended to copy the `cmake` and the build tool commands into a .cmd or .sh file, since it is necessary to do this everytime you compile this program.

The executable can be found inside the `build/` folder, with the specific path depending on the build tool used.
