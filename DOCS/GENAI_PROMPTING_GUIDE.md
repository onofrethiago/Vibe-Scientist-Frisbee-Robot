# 🤖 The GenAI Zero-Shot Prompting Guide for Robotics

As part of the **Society of Agents**, you are not just a coder. You are an **Auditor**. You will use AI to help you build code, but you MUST double-check its work. 

The goal of this guide is to teach you how to "speak" to the machine and learn from the code it generates. 

---

## 🚀 Concept 1: The "Zero-Shot" Prompt
A Zero-Shot prompt is when you ask the AI for a piece of code without giving it any prior examples (shots). 

### 💡 THE PROMPT (Try this one!)
> "Write a C function for ESP-IDF to perform a 180-degree turn for a two-wheeled robot using Seeed Studio XIAO ESP32-C3 pins 4, 5, 6, 7. Assume the pins are connected to a motor driver."

---

## 🔍 Concept 2: The "Auditor" Agent (Monitoring Outputs)
AI isn't perfect. Sometimes it makes mistakes or uses outdated libraries. As an Auditor, you must check for these three things:

1.  **Pin Numbers**: Did the AI use the correct pins from our workbook? (4, 5, 6, 7)
2.  **SDK compatibility**: Does it use `ledc_timer_config` or just `gpio_set_level`? (ESP32-C3 works better with `ledc` for PWM!)
3.  **The Logic**: Does the AI turn one wheel forward and the other backward to turn? Or does it just stop one wheel and move the other? Which is better for a 180-degree turn?

---

## 🔄 Concept 3: Iterative Prompting
If the code doesn't work, don't give up! Tell the AI what happened. 

### 💡 THE FEEDBACK PROMPT
> "The code you provided for the 180-degree turn worked, but the robot turned too fast and overshot the turn. Please rewrite the function but reduce the power by 50% using PWM duty cycles."

---

## 🧗 Reality Check: Learning from the AI
- **Don't just copy-paste!** Read each line. 
- **Identify unknown libraries.** If the AI uses `<driver/ledc.h>` and you've never seen it, ask: *"What does driver/ledc.h do in ESP-IDF?"*
- **Explain to your Teacher.** You must be able to explain how the AI-generated code works before you are allowed to flash it to the robot.

