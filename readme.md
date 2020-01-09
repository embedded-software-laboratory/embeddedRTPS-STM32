# Embedded RTPS on STM32
This repository contains all components necessary to create a minimal working example, showing the communication of an STM32 using Embedded RTPS. 
1. The first component in the `stm32` folder is a STM32CubeIDE project which uses EmbeddedRTPS to send a simple RTPS message.
2. The second component in the `linux` folder is a C++ project using the ASOA RTPS Driver library and Eprosima FastRTPS to receive the message sent by STM32.

## Dependencies
### STM32
To compile the project for the STM32, install the following Software
- STM32CubeIDE
- st-stlink-server.1.2.0-5.1.pkg (Provided with the IDE)

### Linux/MacOS
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



## Compilation


## Testing communication with STM32

