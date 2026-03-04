# Automated Security Door System
**H.A.R.D. Hack 2026 | DigiKey × Qualcomm Track** **Role:** Team Captain, G-CAD Engineering Team

---

## 1. Project Abstract
A high-integrity embedded access control system developed during a 24-hour rapid prototyping sprint. The system utilizes the **Arduino Uno Q** and **Modulino** ecosystem to bridge secure digital authentication with mechanical actuation. The project focuses on real-time logic processing, low-latency peripheral communication, and robust hardware-software integration.


https://github.com/user-attachments/assets/3cef6c3d-02a9-4073-a913-ffc11498aba4

**Automated Security Door Prototype.**

---

## 2. Technical Specifications
* **Microcontroller:** Arduino Uno Q (Logic Controller)
* **Input Interface:** 4-button Keypad with LED 
* **Actuation:** PWM-controlled Servomotor (High-torque locking mechanism)
* **Communication Protocols:** I2C (Peripheral Interconnect), Serial (Debugging/Logging)
* **Programming Language:** C-language (Firmware)
* **Power Management:** 5V DC Unified Power Rail

---

## 3. System Architecture & Design
The architecture follows a synchronous polling model for user input, coupled with an interrupt-driven response for physical actuation. 

### Hardware Design
The system was designed for modularity using the Modulino architecture. I oversaw the hardware-software mapping to ensure all sensors and actuators shared a common ground plane and stable voltage levels to prevent logic errors during motor high-draw events.

![IMG_7844](https://github.com/user-attachments/assets/d34dd895-6abc-4994-9879-26da88eae667)

**System Wiring Diagram and Pin Mapping for Arduino Uno Q.**

### Firmware Logic
The C-language firmware manages:
* **State Machine Management:** Handles transitions between `LOCKED`, `AUTHENTICATING`, `UNLOCKED`, and `ALARM` states.
* **Buffer Management:** Real-time processing of keypad inputs against stored security credentials.
* **PWM Optimization:** Fine-tuned pulse-width modulation signals to the servomotor to ensure precise 90-degree mechanical movement for the door latch.

---

## 4. Visual Documentation

### Physical Build

![IMG_9804](https://github.com/user-attachments/assets/3b739397-02c7-478b-887b-680d67405646)


**Internal hardware assembly and cable management.**

### Functional Validation

![IMG_1239 (1)](https://github.com/user-attachments/assets/6da7244a-b8db-4a28-a58e-4af3000f40dd)

**Final mechanical assembly featuring integrated security hardware.**

---

## The G-CAD Team
* **Daniela Gutierrez Hornedo** 
* **Gabriel Coronado Cardenas** 
* **Anthony Flores-Mendez** 
* **Christopher Inzunza** 
