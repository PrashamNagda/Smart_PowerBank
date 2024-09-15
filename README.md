SmartBank Project Phase - I <a name="TOP"></a>
===================

## Table of Contents
* [Introduction](#Introduction)
* [Specifications](#Specifications)
* [Unique Features](#Unique-Features)
* [Tools Used](#Tools-Used)
  * [EasyEDA](#EasyEDA)
  * [Arduino IDE](#Arduino-IDE)
  * [Fritzing](#Fritzing)
  * [Autodesk Fusion 360](#Autodesk-Fusion-360)
  * [Figma](#Figma)
  * [Flutter](#Flutter)
* [Methodology](#Methodology)
* [Microcontroller Specifications](#Microcontroller-Specifications)
* [Power Bank SoC Specifications](#Power-Bank-SoC-Specifications)
  * [SoC Pin Definition](#SoC-Pin-Definition)
  * [SoC I2C Connection](#SoC-I2C-Connection)
  * [SoC Application Component List](#SoC-Application-Component-List)
  * [Reference SoC Application Circuit Diagram](#Reference-SoC-Application-Circuit-Diagram)
* [SmartBank Charging Module](#SmartBank-Charging-Module)
  * [Schematic](#Schematic)
  * [PCB](#PCB)
  * [3D PCB Model](#3D-PCB-Model)
  * [3D Case Prototype Model](#3D-Case-Prototype-Model)
  * [Fabricated PCB](#Fabricated-PCB)
* [Microcontroller Interfacing](#Microcontroller-Interfacing)
* [SmartBank Connect Application UI Flow](#SmartBank-Connect-Application-UI-Flow)
* [References](#References)
* [Acknowledgement](#Acknowledgement)

## Introduction
Smart bank is a connected power bank which has various features like two-way adaptive fast charging, 12 – layer protection, find my device, simultaneous fast charging support, and it is also integrated with Qualcomm’s Quick Charge 3.0 technology. It has Bluetooth LE 5.0 connectivity with a mobile application through which the device’s parameters like battery status, battery temperature, charge discharge cycles, time left till 0%, etc. can be monitored.

## Specifications
* Qualcomm’s Quick Charge 3.0 technology
* Supports upto 18W Fast Charging
* 12 - layer ciruit protection
* Bluetooth LE 5.0 connectivity with SmartBank Connect App
* Find my device feature (Similar to apple's air tag)
* Compatible protocols (QC2.0/QC3.0, FCP, AFC, USBC DRP, BC1.2, and many more)
* USB Power Delivery (PD3.0/PD2.0)
* 20000 mAh battery capacity
* USB-A, Type-C and Micro USB support for input and output
* Simultaneous fast charging (13W per port)
* Built in high-brightness flash

## Unique Features
* Find My Device
* Bluetooth Low Energy v5.0 connectivity
* Device parameter monitoring using SmartBank Connect App

## Tools Used
#### EasyEDA
EasyEDA is a web-based EDA tool suite that enables hardware engineers to design, simulate, share publicly and privately and discuss schematics, simulations and printed circuit boards.
* For more details refer: <https://easyeda.com/>

#### Arduino IDE 
Arduino Integrated Development Environment or Arduino Software (IDE) contains a text editor for writing code, a message area, a text console, a toolbar with buttons for common functions and a series of menus. It connects to the Arduino hardware to upload programs and communicate with them. 
* For more details refer: <https://www.arduino.cc/en/software>

#### Fritzing
Fritzing is an open-source hardware initiative that makes electronics accessible as a creative material for anyone. We offer a software tool, a community website and services in the spirit of Processing and Arduino, fostering a creative ecosystem that allows users to document their prototypes, share them with others, teach electronics in a classroom, and layout and manufacture professional PCBs. 
* For more details refer: <https://fritzing.org/>

#### Autodesk Fusion 360
Fusion 360 is a cloud-based 3D modeling, CAD, CAM, CAE, and PCB software platform for professional product design and manufacturing. 
* For more details refer: <https://www.autodesk.in/products/fusion-360/overview>

#### Figma
Figma is a powerful web-based design tool that helps you create anything, websites, applications, logos, and much more. It is a vector graphics editor and prototyping tool that is often used for UI design.
* For more details refer: https://www.figma.com/

#### Flutter
Flutter is a mobile app development platform created by Google. It allows developers to create web, desktop, and cross-platform apps that run on Android and iOS devices. Flutter uses a reactive programming language called Dart, making development faster and easier than traditional methods. Flutter is an open source framework by Google for building beautiful, natively compiled, multi-platform applications from a single codebase.
* For more details refer: https://flutter.dev/

## Methodology
#### Hardware
1. Planning
2. SWOT Analysis
3. Feature Selection
4. Schematic Designing
5. PCB Designing
6. Component Sourcing
7. PCB Fabrication and Assembly
8. Hardware Testing
9. Firmware Programming
10. Firmware Testing and Compatibility
11. Outer Case Designing

#### Software
1. Planning
2. Analysis
3. Feature Selection
4. UI Designing
5. Front-end Programming
6. Back-end Programming
7. Application Testing
8. Application-Hardware Connectivity Testing
10. Version Control

## Microcontroller Specifications
* Espressif System's ESP32-C3FH4
* 32-bit RISC-V single-core processor
* Clock speed up to 160 MHz
* 384 KB ROM
* 400 KB SRAM (16 KB for cache)
* WiFi - IEEE 802.11 b/g/n-compliant
* Bluetooth LE: (Speed: 125 Kbps, 500 Kbps, 1 Mbps, 2 Mbps)
  * Bluetooth 5
  * Bluetooth mesh
* Peripherals: 
  * GPIO, SPI, UART, I2C, I2S, LED PWM controller, USB Serial/JTAG controller,Temperature sensor, SAR ADC
* Antenna: On-board PCB antenna (ESP32-C3-MINI-1)

## Power Bank SoC Specifications
* Injoinic Technology IP5328P with Fully Integrated Bi directional PD3.0 and Fast Charge Power Bank SOC
* QFN-48 Package
* Support 5V, 9V, 12V voltage input/output
* Integrated USB Power Delivery (PD2.0/PD2.0) protocol
* Up to 5.0A charging current at battery port
* Adaptive charging current adjustment
* Discharge: 5V/3.1A (15W) 9V/2.0A (18W) 12V/1.5A (18W)
* I2C interface for flexible and low cost customized solution
* Single inductor for charging and discharging
* Output overcurrent, overvoltage and short circuit protection
* Battery overcharge, over discharge and overcurrent protection
* Over temperature protection
* Battery NTC protection

## SoC Pin Definition
![image](https://user-images.githubusercontent.com/127144315/223557740-36cd38b4-8c98-4057-8497-7916965bfec5.png)

## SoC I2C Connection
![image](https://user-images.githubusercontent.com/127144315/223559000-46c6d3b1-e2b1-4314-a11c-d28ab26bb6c2.png)

## SoC Application Component List
![image](https://user-images.githubusercontent.com/127144315/223559292-1a4c5e33-c9f5-49dd-859c-daf2097a57c7.png)

## Reference SoC Application Circuit Diagram
![SoC Reference Circuit](https://user-images.githubusercontent.com/127144315/223557157-5dd1aef8-1442-42fd-9f8d-2e75b665941f.png)

## SmartBank Charging Module
#### Schematic
![Schematic_SmartBank V2 0_2023-03-08](https://user-images.githubusercontent.com/127144315/223560833-468495cc-5802-4742-908d-133820ef0a78.png)

#### PCB
Top Layer

![image](https://user-images.githubusercontent.com/127144315/223562499-f002172f-948f-4635-8494-f3c16681e8b9.png)

![image](https://user-images.githubusercontent.com/127144315/223562064-7aebca20-e865-46a4-b882-e0b92bd076da.png)

Bottom Layer

![image](https://user-images.githubusercontent.com/127144315/223562559-14fdf376-e826-458a-b7b0-674ca9e3361d.png)

![image](https://user-images.githubusercontent.com/127144315/223561978-77fc8a1d-ea9c-48ac-8302-9f5ba9f3dc8b.png)

#### 3D PCB Model
![image](https://user-images.githubusercontent.com/127144315/223563612-a5669cda-3361-4dfd-ac4c-55b85a82aaa7.png)
![image](https://user-images.githubusercontent.com/127144315/223563678-b7caccbc-5913-4156-8b43-8a8badca0208.png)
![image](https://user-images.githubusercontent.com/127144315/223563867-22ac1ca5-fe47-4f34-ab56-8b9cfc9a6b94.png)
![image](https://user-images.githubusercontent.com/127144315/223563956-5cb6a7f8-9836-47d8-9def-073787bb7be8.png)

#### 3D Case Prototype Model
![CASE_V1](https://user-images.githubusercontent.com/127144315/223565589-ad6fab32-bca8-4f64-9298-f44475089ee4.png)

#### Fabricated PCB
![image](https://user-images.githubusercontent.com/127144315/223567838-76239e7f-ab74-4ea7-9fbd-33b273ab107b.png)
![image](https://user-images.githubusercontent.com/127144315/223567942-972300dd-691a-43cc-b769-739083b83d3f.png)

## Microcontroller Interfacing
* Used I2C protocol to interface ESP32C3 Microcontroller to IP5328P Power Bank SoC
* Used BLE 5.0 for Connectivity with the SmartBank Mobile Application
* Interfaced DS18B20 Digital temperature sensor to monitor the Power Bank's battery temperature
* LED and Buzzer for the Find My Device Feature as an output device
* Push Button for Turning ON/OFF, Torch, and Connectivity

## SmartBank Connect Application UI Flow
#### Onboarding (Start-up) screen
  ![image](https://user-images.githubusercontent.com/127144315/223569701-08bf7130-c0d9-4498-b507-af49af3a757e.png)

#### Search and Scan for devices
![image](https://user-images.githubusercontent.com/127144315/223569824-7ac3801d-94c6-4396-82cc-a1c5ce58d470.png)

#### Scan Fail/Error Connecting to device

![image](https://user-images.githubusercontent.com/127144315/223570078-9febf7a9-cc0c-4982-aec5-595f18282880.png)

#### Main Dashboard
![image](https://user-images.githubusercontent.com/127144315/223570145-b830e62d-bf16-46ae-a51e-5ef9e7b46c58.png)

#### Dashboard and Find My Device
![image](https://user-images.githubusercontent.com/127144315/223570180-042728c7-9de8-4bcd-9562-d5047397ecb2.png)

#### Settings, Connected Devices and Notification
![image](https://user-images.githubusercontent.com/127144315/223570371-b78765a1-8d30-4d6c-ba72-27583ee36ffc.png)

#### Usage History
![IMG-20220523-WA0009](https://user-images.githubusercontent.com/127144315/223571704-e967b5e7-0977-4336-8e10-0d493433b5e4.jpg)

#### Data Reset/Accessibilty Functions and T&C
![image](https://user-images.githubusercontent.com/127144315/223570588-7ff5fe9d-addc-4232-a1ac-8625e992a580.png)

## References
 - [1] http://www.injoinic.com/?lang=en-us
 - [2] https://www.mouser.in/
 - [3] https://www.lcsc.com/

## Acknowledgement
#### Project Mentors
1. Dr. Manoj Sankhe, BTI EXTC In-charge, MPSTME Mumbai Campus
2. Vishram Bapat, Founder, Databyte Services and Systems, http://databyteservices.com/

#### Guidance
* Ajit Bapat, CEO, Dataserve Pvt. Ltd., https://www.rightocare.com/ 
