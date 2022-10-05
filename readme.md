# embeddedRTPS on STM32Nucleo-F767ZI
This repository contains all components necessary to create a minimal working example of communication between an STM32F767ZI using embeddedRTPS and a Linux system using FastRTPS. This repository contains two projects:
1. The first project in the `stm32/` directory is a STM32CubeIDE project which uses EmbeddedRTPS and is deployed to the STM32Nucleo-F767ZI.
2. The second project in the `linux/` directory is a C++ project that uses eProsima FastRTPS for the Linux system. It can also be compiled and executed on macOS.

When both of these projects are executed, the Linux system will send RTPS messages with test data to the STM32F767ZI, to which the STM32F767ZI will then respond. This simple communication test is executed 10 times.

**[The main embeddedRTPS repository is located here.](https://github.com/embedded-software-laboratory/embeddedRTPS)**

## Dependencies
### STM32F767ZI Project
To compile the project for the STM32, install the following Software:
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (version 1.9.0 or later)
- st-stlink-server.1.2.0-5.1 (Provided with the [IDE](https://www.st.com/en/development-tools/stm32cubeide.html))

---

### Linux/macOS Project
To compile the project for Linux, install the following Software:

#### Ubuntu 18.04
Packages to install using apt-get:
```bash
sudo apt-get -y update && sudo apt-get -y upgrade
sudo apt-get install -y \
    software-properties-common \
    libboost-all-dev \
    libssl-dev \
    build-essential \
    cmake
```
## Compilation
After installing the required dependencies, both projects can first cloned and compiled using the following instructions:

```bash
git clone --recursive https://github.com/embedded-software-laboratory/embeddedRTPS-STM32
```

### STM32F767ZI Project
To compile and deploy the STM32 project, first open the STM32CubeIDE.
```
File -> Open projects from File System -> Directory -> Select the stm32/ directory
```
Then press finish to import the project into your local workspace.

Now select the project in the project explorer:
```
Project Explorer -> embedded_rtps_stm32
```

If you are using CMSIS v2, you have to edit the task priorities in `Core/Inc/rtps/config.h` as follows.

```config.h
l63        const uint8_t SPDP_WRITER_PRIO = 24;
l72        const int THREAD_POOL_WRITER_PRIO = 24;
l73        const int THREAD_POOL_READER_PRIO = 24;
```

Then, right click the hammer button in the navigation bar. 
This opens the menu to select the build configuration:
 - debug: The debug configuration compiles the code with debug symbols and lowers optimization for debugging.
 - release: This configuration disables debug symbols and increases optimizations to maximum.

The selected configuration is then compiled by STM32CubeIDE. 

#### Code generation using CubeMX
You also can use the CubeMX code generating feature in CubeIDE to configure the project.
After code generation, you have to do the following steps:

* delete auto-generated `Src/main.c` (**not** `main.cpp`)
* edit `Middlewares/Third_Party/LwIP/system/arc/cc.h l41` as follows
```
//#define LWIP_PROVIDE_ERRNO
#define LWIP_ERRNO_INCLUDE <sys/errno.h>
```
* edit `Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_eth.c l1877` as follows
```
 macinit.PromiscuousMode = ETH_PROMISCUOUS_MODE_ENABLE;
```
Note that when you change the STM's IP address, you also have to change the IP address configure in `rtps/include/rtps/config.h l37`


#### Flashing the STM32F767ZI
The STM32 should now be connected to the Linux/macOS computer using a micro-USB cable. The cable should be plugged into a USB socket on your computer and into the __debugger__ side of the STM32 Nucleo board.

The compiled configuration can then be flashed on to the STM32 in the following steps:
```
Navigation bar -> Run -> Debug
```
It might now be necessary to select the target, in which case "STM32 Application" should be selected. The IDE will then flash the STM32 with your selected configuration. 

#### Tips
- The IDE may prompt you to update the firmware of the onboard ST-Link debugger, this is normal and you can follow the process to update the firmware to the newest version.
- The IDE may also ask you to switch to the Run/Debug display after flashing a configuration to the STM32, this is the debug screen of the IDE and thus usefull to see the current callstack and more.

---

### Linux/macOS Project

To compile the Linux/macOS project navigate to the `linux/` directory. Then compile the CMakeLists project using the following commands:
```bash
cd linux
mkdir build
cd build
cmake -DTHIRDPARTY=ON ..
make 
```

The resulting executable can then be found in the build directory and is called `embedded_rtps_test`. 

## Testing Communication with STM32

After compiling both projects the communication between both devices can be tested. To conduct this test follow these steps:

#### Setup on Linux/macOS
1. Connect the STM32 to your computer using a ethernet cable.
2. Ensure all firewalls are disable. (probably an OSX issue)
3. Manually assign an IP address (and subnet mask) to the STM32. <br>
   (for example: IP:192.168.0.1, subnet: 255.255.255.0) 
4. (It may be necessary to disable other network connections, like wifi, if the chosen IP address is in your local network, necessary with the example adresses provided here.)
5. (You can also communicate with the STM32 via a router. Network settings such as IP address are in `rtps/include/rtps/config.h` and `Src/lwip.c`.)

#### Executing the Test

1. Flash a configuration to the STM32 and run it.
2. The debugger will halt on the first line of the main method, press either F8 or the Resume button.
3. The STM32 should now wait for a subscriber match (to verify this flash the debug configuration and execute steps one and two, then halt the debugger after a couple of seconds after clicking resume in step 2, the debugger should halt on line 495).
4. Execute the `embedded_rtps_test` executable in the `linux/build` directory.
5. The executable will then send test data to the STM32 and the STM32 should respond to by returning other test data of the following form: <br>
``` 
Received message from STM32 with len:10
0 : 10
1 : 10
2 : 10
3 : 10
4 : 10
5 : 10
6 : 10
7 : 10
8 : 10
9 : 10
```
The first component is the byte index while the second component is the value. As the test code sets all values in the test array to 10, this is the expected output.
