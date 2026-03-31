# 🎓 FrisbeeRobot Student Workbook

Welcome to the **FrisbeeRobot Developer Training**. You are now a **Robotics Engineer**. In this module, you'll learn to control motors, troubleshoot hardware inconsistencies, and use AI to accelerate your development.

---

## 🛠️ Challenge 1: The "Drunken Robot" (Incorrect Rotation)
### The Problem
You've uploaded the code, and you want the robot to go forward. But when you press 'Go', the left wheel goes forward and the right wheel goes backward. The robot just spins in circles!

### 💡 The Solution (Logic over Soldering)
In the file `src/motors.c`, find the function `motor_right_forward()`. It currently sets `GPIO_RIGHT_A` to HIGH and `GPIO_RIGHT_B` to LOW. 

**Student Task**: 
1.  Flip the logic for the right motor in the code.
2.  If `GPIO_RIGHT_A` was HIGH, make it LOW. If `GPIO_RIGHT_B` was LOW, make it HIGH.
3.  Re-flash the robot and test!

---

## 🤖 Challenge 2: Talking to the Machine (GenAI Zero-Shot)
In real-world engineering, we often use AI agents to generate boilerplate code. 

### The Task
Ask a GenAI (like ChatGPT, Gemini, or Claude) to write a function that performs a "S-Curve" turn. 

**Example Prompt**:
> "Write a C function for ESP-IDF that smoothly increases the speed of the left wheel while decreasing the speed of the right wheel to perform a gradual turn."

### 🔬 Experiment & Monitor
- **Compare**: How does the AI's logic compare to your manual logic?
- **Verify**: Does the AI use the correct pin numbers for the FrisbeeRobot?
- **Debug**: If the AI's code doesn't compile, can you figure out why?

---

## 🏗️ Core Code Concepts to Master
| Concept | Description | Why it matters |
|---|---|---|
| **#include** | Including external libraries | Accessing the "drivers" for the motors. |
| **GPIO** | General Purpose Input/Output | How the code talks to the physical pins. |
| **Main Loop** | `while(1) { ... }` | The robot's heartbeat. It keeps running forever. |

