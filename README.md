# Frisby Robot 🏎️

This project controls two motors using a **Seeed Studio XIAO ESP32-C3** and an **L298N H-Bridge**.

## 🔌 Wiring Guide

| XIAO ESP32-C3 | L298N Module | Function |
| :--- | :--- | :--- |
| **GND** | **GND** | Common Ground (ESSENTIAL) |
| **D0** | **ENA** | Motor A Speed (Remove Jumper!) |
| **D1** | **IN1** | Motor A Direction 1 |
| **D2** | **IN2** | Motor A Direction 2 |
| **D3** | **ENB** | Motor B Speed (Remove Jumper!) |
| **D4** | **IN3** | Motor B Direction 1 |
| **D5** | **IN4** | Motor B Direction 2 |

## 🚀 Getting Started

1.  **Board Setup:** Install the `esp32` board core in Arduino IDE.
2.  **Select Board:** Choose `XIAO_ESP32C3`.
3.  **Upload:** Flash the `FrisbyRobot.ino` file.
4.  **Control:** Open Serial Monitor (115200 baud) and type:
    *   `F` - Forward
    *   `B` - Backward
    *   `S` - Stop

## ⚠️ Safety Tips
*   Power motors from an external battery (e.g., 2x 18650 or a 9V).
*   Connect the Battery GND to BOTH the L298N GND and XIAO GND.
