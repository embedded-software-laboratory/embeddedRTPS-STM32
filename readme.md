# Embedded RTPS on STM32
This repository contains all components necessary to create a minimal working example of communication between an STM32 using Embedded RTPS and a Linux system using FastRTPS. This repository contains two projects:
1. The first project in the `stm32` folder is a STM32CubeIDE project which uses EmbeddedRTPS and is deployed to the STM32.
2. The second project in the `linux` folder is a C++ project using the ASOA RTPS Driver library and Eprosima FastRTPS to be used on the Linux system.

When both of these projects are executed, the STM32 will send a simple RTPS message using EmbeddedRTPS to the linux system, which will receive the message and display its contents.

---

## Dependencies
### STM32 Project
To compile the project for the STM32, install the following Software:
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- st-stlink-server.1.2.0-5.1.pkg (Provided with the [IDE](https://www.st.com/en/development-tools/stm32cubeide.html))

### Linux/MacOS Project
To compile the project for linux, install the following Software:

#### Ubuntu 18.04
Packages to install using apt-get:
```bash
apt-get -y update && apt-get -y upgrade
apt-get install -y \
    sudo \
    software-properties-common \
    python \
    python-pip \
    wget \
    libboost-all-dev \
    libssl-dev \
    build-essential \
    castxml \
    cmake \
```
Python dependencies:
```bash
pip install pyplusplus 
```

#### MacOS 10.15.2 
Install XCode command line tools:
```bash
xcode-select --install
```

Packages to install using [Homebrew](https://brew.sh/index_de):
```bash
brew install cmake \
             python \
             boost-python \
             boost \
             castxml \
```

Python dependencies:
```bash
pip install pyplusplus 
```

---

## Compilation
After installing the required dependencies, both projects can be compiled:

### STM32 Project
To compile and deploy the STM32 project, first open the STM32CubeIDE.

---

## Testing communication with STM32

