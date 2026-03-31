# 🍎 Teacher's Guide: The FrisbeeRobot Module

This guide is designed for high school level instructors to teach the fundamentals of robotics, embedded programming (ESP-IDF), and human-AI collaboration (GenAI).

## 🎓 Module Overview
The FrisbeeRobot is a compact, autonomous, or remote-controlled bot powered by the **Seeed Studio XIAO ESP32-C3**. This module focuses on:
1.  **Hardware Literacy**: Understanding MCUs, GPIOs, and Motors.
2.  **Code Architecture**: Navigating a professional-grade ESP-IDF project.
3.  **Problem Solving**: Debugging "real-world" hardware logic errors.
4.  **AI Literacy**: Leveraging GenAI for zero-shot robotics code generation.


---

## 📘 Mini-Lecture 1: The "Brain" (ESP32-C3)
### Objective
Understand the role of the Microcontroller Unit (MCU).

### Lecture Points
- **What is an ESP32-C3?** It's a single-core RISC-V microcontroller with built-in Wi-Fi and Bluetooth. Think of it as a tiny computer dedicated to one task: controlling the robot.
- **Why RISC-V?** It's an open-source architecture, meaning anyone can use and build on it. It’s the "Linux of processors."
- **GPIO Pins**: These are the "nervous system." They send signals (PWM) to the motors and receive signals from sensors.

---

## 📘 Mini-Lecture 2: The "Muscle" (Motor Control)
### Objective
Explain how code moves physical objects.

### Lecture Points
- **PWM (Pulse Width Modulation)**: We don't just "turn motors on." We pulse them really fast! By changing the "duty cycle" (how long the pulse is on), we control the speed.
- **H-Bridge Logic**: To change directions, we flip the polarity of the voltage. In code, this means setting one pin HIGH and another LOW, or vice versa.
- **The "Opposite Wheels" Problem**: Wiring is messy. Often, one motor is flipped physically. Students must learn to fix this in **code** rather than re-soldering the robot.

---

## 👨‍🏫 Instructional Strategy: The "Buggy Code" Method
Instead of giving students perfect code, provide them with a version containing a logical flaw.
-   **The Scenario**: The robot's left wheel spins forward, but the right wheel spins backward when told to move "Forward."
-   **The Lesson**: Logical abstraction. Fixing the `move_forward()` function by inverting the polarity logic for the specific motor.

---

## 🤖 AI Integration: Prompting for Robotics
Introduce students to "Zero-Shot Prompting." Instead of writing every line, they describe the behavior to an AI.

### Zero-Shot Example
> "Write a C function for ESP-IDF using the Seeed XIAO ESP32-C3 to control two DC motors on GPIO 4, 5 and 6, 7. The function should take a speed parameter from 0 to 255."

### Teaching Moment
Monitor the output! Is the AI using the correct libraries? Is it using `ledc` for PWM? Students must become **Audit Agents** to verify AI-generated code.
