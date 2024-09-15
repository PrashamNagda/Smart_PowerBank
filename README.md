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
* [SmartBank Connect Application UI Flow](#smartbank-connect-application-ui-flow)
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
![Pin Diagram](#)

## SoC I2C Connection
![I2C Diagram](#)

## SoC Application Component List
![Component List](#)

## Reference SoC Application Circuit Diagram
![Circuit Diagram](#)

## SmartBank Charging Module

### Schematic
![Schematic](#)

### PCB
Top Layer  
![Top Layer](#)  
Bottom Layer  
![Bottom Layer](#)

### 3D PCB Model
![3D Model](#)

### 3D Case Prototype Model
![Case Model](#)

### Fabricated PCB
![Fabricated PCB](#)

## Microcontroller Interfacing
* I2C protocol for ESP32C3 to IP5328P communication
* BLE 5.0 for app connectivity
* Temperature sensor for battery monitoring
* LED, buzzer, and push button for interaction and controls

## SmartBank Connect Application UI Flow

### Onboarding Screen
![Onboarding](#)

### Device Search and Scan
![Device Scan](#)

### Main Dashboard
![Dashboard](#)

### Settings and Notifications
![Settings](#)

### Usage History
![Usage History](#)

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
