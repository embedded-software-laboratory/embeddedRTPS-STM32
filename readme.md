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
After installing the required dependencies, both projects can be compiled using the following instructions:

## STM32 Project
To compile and deploy the STM32 project, first open the STM32CubeIDE.
```
File -> Open projects from File System -> Directory -> Select the stm32 Folder 
```
Then press finish to import the project into your local workspace.

Now select the project in the project explorer:
```
Project Explorer -> embedded_rtps_stm32
```
After selecting the process, right click the hammer button in the navigation bar. 
This opens the menu to select the build configuration:
 - debug: The debug configuration compiles the code with debug symbols and lowers optimization for debugging.
 - release: This configuration disables debug symbols and increases optimizations to maximum.

The selected configuration is then compiled by STM32CubeIDE. 

#### Flashing the STM32
The STM32 should now be connected to the linux computer using a micro-USB cable. The cable should be plugged into a USB socket on your computer and into the __debugger__ side of the STM32 Nucleo board.

The compiled configuration can then be flashed on to the STM32 in the following steps:
```
Navigation bar -> Run -> Debug
```
It might now be necessary to select the target, in which case "STM32 Application" should be selected. The IDE will then flash the STM32 with your selected configuration. 

#### Tips
- The IDE may prompt you to update the firmware of the onboard ST-Link debugger, this is normal and you can follow the outlined process to update the firmware to the newest version.
- The IDE may also ask you to switch to the Run/Debug display after flashing a configuration to the STM32, this is the debug screen of the IDE and thus usefull to see the current callstack and more.

## Linux project

To compile the Linux project navigate to the linux folder. Then compile the CMakeLists project using the following commands:
```bash
mkdir build \
cd build \
cmake .. \
make 
```

The resulting executable can then be found in the build directory and is called `simple_receiver`. 

---

## Testing communication with STM32

After compiling both projects the communication between both devices can be tested. To conduct this test follow these steps:

#### Setup on Linux
1. Connect the STM32 to your computer using a ethernet cable.
2. Ensure all firewalls are disable (probably a OSX issue)
3. Manually assign an IP address (and subnet mask, ...) to the STM32 <br>
   (for example: IP:192.168.0.1, subnet: 255.255.255.0, router: 192.168.0.1) 

#### Executing the Test

1. Execute the simple_receiver executable in the linux/build folder
2. Flash a configuration to the STM32
3. The debugger will halt on the first line of the main method, press 

