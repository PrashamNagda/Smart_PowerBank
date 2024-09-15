# SmartBank Project - Phase I

## Table of Contents
* [Introduction](#introduction)
* [Specifications](#specifications)
* [Unique Features](#unique-features)
* [Tools Used](#tools-used)
  * [EasyEDA](#easyeda)
  * [Arduino IDE](#arduino-ide)
  * [Fritzing](#fritzing)
  * [Autodesk Fusion 360](#autodesk-fusion-360)
  * [Figma](#figma)
  * [Flutter](#flutter)
* [Methodology](#methodology)
* [Microcontroller Specifications](#microcontroller-specifications)
* [Power Bank SoC Specifications](#power-bank-soc-specifications)
  * [SoC Pin Definition](#soc-pin-definition)
  * [SoC I2C Connection](#soc-i2c-connection)
  * [SoC Application Component List](#soc-application-component-list)
  * [Reference SoC Application Circuit Diagram](#reference-soc-application-circuit-diagram)
* [SmartBank Charging Module](#smartbank-charging-module)
  * [Schematic](#schematic)
  * [PCB](#pcb)
  * [3D PCB Model](#3d-pcb-model)
  * [3D Case Prototype Model](#3d-case-prototype-model)
  * [Fabricated PCB](#fabricated-pcb)
* [Microcontroller Interfacing](#microcontroller-interfacing)
* [References](#references)
* [Acknowledgement](#acknowledgement)

## Introduction
SmartBank is a connected power bank featuring two-way adaptive fast charging, 12-layer circuit protection, device tracking, and simultaneous fast charging. It integrates Qualcomm Quick Charge 3.0 technology and includes Bluetooth LE 5.0 connectivity, enabling users to monitor battery parameters such as status, temperature, and charge cycles via the SmartBank Connect mobile app.

## Specifications
* Qualcomm Quick Charge 3.0 technology
* Supports up to 18W Fast Charging
* 12-layer circuit protection
* Bluetooth LE 5.0 with SmartBank Connect App integration
* Device tracking (similar to Apple's AirTag)
* Support for multiple charging protocols: QC2.0, QC3.0, FCP, AFC, USB DRP, BC1.2, PD3.0/PD2.0
* 20,000 mAh battery capacity
* USB-A, Type-C, and Micro USB support for both input and output
* Simultaneous fast charging (13W per port)
* Integrated high-brightness flashlight

## Unique Features
* Device tracking via Bluetooth LE 5.0
* Real-time battery monitoring with SmartBank Connect App

## Tools Used

### EasyEDA
EasyEDA is a web-based EDA tool for designing, simulating, and discussing schematics and PCB layouts.  
* [Learn More](https://easyeda.com)

### Arduino IDE
The Arduino IDE is a software tool for writing and uploading code to Arduino hardware.  
* [Learn More](https://www.arduino.cc/en/software)

### Fritzing
Fritzing is an open-source platform for documenting prototypes and producing professional PCBs.  
* [Learn More](https://fritzing.org)

### Autodesk Fusion 360
Fusion 360 is a cloud-based tool that combines 3D modeling, CAD, CAM, and PCB design functionalities.  
* [Learn More](https://www.autodesk.in/products/fusion-360/overview)

### Figma
Figma is a collaborative interface design tool used for UI/UX design and prototyping.  
* [Learn More](https://www.figma.com/)

### Flutter
Flutter is Google's open-source framework for building natively compiled apps for mobile, web, and desktop using a single codebase.  
* [Learn More](https://flutter.dev/)

## Methodology

### Hardware
1. Planning
2. SWOT Analysis
3. Feature Selection
4. Schematic Design
5. PCB Design
6. Component Sourcing
7. PCB Fabrication and Assembly
8. Hardware Testing
9. Firmware Programming
10. Firmware Testing
11. Outer Case Design

### Software
1. Planning
2. Requirement Analysis
3. Feature Selection
4. UI Design
5. Frontend Development
6. Backend Development
7. Application Testing
8. Hardware-Software Integration Testing
9. Version Control

## Microcontroller Specifications
* **Chipset**: Espressif ESP32-C3FH4
* **Processor**: 32-bit RISC-V single-core at 160 MHz
* **RAM**: 400 KB SRAM
* **Connectivity**: WiFi (802.11 b/g/n), Bluetooth LE 5.0
* **Peripherals**: GPIO, SPI, UART, I2C, I2S, LED PWM controller
* **Power**: On-board PCB antenna, SAR ADC, USB Serial/JTAG

## Power Bank SoC Specifications
* **Model**: Injoinic IP5328P
* **Input/Output**: 5V, 9V, 12V voltage
* **Features**: USB Power Delivery (PD2.0/PD3.0), adaptive charging, I2C interface, overvoltage/short circuit protection

## SoC Pin Definition
![image](https://github.com/user-attachments/assets/c5c704b1-e868-4729-afde-b25251a5945b)


## SoC I2C Connection
![image](https://github.com/user-attachments/assets/c4727d75-8ad4-46b7-aa36-7729ed95a12d)


## SoC Application Component List
![image](https://github.com/user-attachments/assets/e8ee31bd-edfd-482b-87db-5710b6184c56)


## Reference SoC Application Circuit Diagram
![image](https://github.com/user-attachments/assets/45500100-f1e8-415b-a592-5d00dc2f3581)


## SmartBank Charging Module

### Schematic
![image](https://github.com/user-attachments/assets/f5233c1b-941e-4826-8f45-c3f75e4df6f7)


### PCB
Top Layer  
![image](https://github.com/user-attachments/assets/53b3dde5-b483-46ef-a406-07e8a80c2dd8)

Bottom Layer  
![image](https://github.com/user-attachments/assets/5413a2ff-3103-4791-b373-d49de3f6e920)


### 3D PCB Model
![image](https://github.com/user-attachments/assets/724b9b4f-f61b-48d6-9dfe-0e54279a2df6)


### 3D Case Prototype Model
![image](https://github.com/user-attachments/assets/f59912bb-8427-4922-a17c-8ff21f0a17fe)


### Fabricated PCB
![image](https://github.com/user-attachments/assets/fb367a7a-9e4e-47a9-a195-9659e4b61908)


## Microcontroller Interfacing
* I2C protocol for ESP32C3 to IP5328P communication
* BLE 5.0 for app connectivity
* Temperature sensor for battery monitoring
* LED, buzzer, and push button for interaction and controls


## References
* [Injoinic Technology](http://www.injoinic.com/?lang=en-us)
* [Mouser Electronics](https://www.mouser.in/)
* [LCSC](https://www.lcsc.com/)

## Acknowledgement

### Project Mentors
1. **Dr. Manoj Sankhe**, BTI EXTC In-charge, MPSTME Mumbai Campus
2. **Vishram Bapat**, Founder, Databyte Services and Systems

### Guidance
* **Ajit Bapat**, CEO, Dataserve Pvt. Ltd.
