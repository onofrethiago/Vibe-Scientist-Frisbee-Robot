# 🚀 FrisbeeRobot: Society of Agents Educational Module

I have successfully established the foundation for the **FrisbeeRobot** high school module using the **Society of Agents** (SoA) methodology. This framework delegates documentation and code tasks across specialized AI roles (Architect, Edu-Guide, and Auditor) to ensure a comprehensive learning experience.

## 📂 Module Structure

| Location | Component | Role | Description |
|---|---|---|---|
| `DOCS/TEACHER_GUIDE.md` | **Teacher's Guide** | *Edu-Guide* | Contains mini-lectures on MCUs, PWM, and pedagogical strategies like the "Buggy Code" method. |
| `DOCS/STUDENT_WORKBOOK.md` | **Student Workbook** | *Student Navigator* | Hands-on exercises including the "Opposite Wheels" logic challenge. |
| `DOCS/GENAI_PROMPTING_GUIDE.md` | **GenAI Prompting Guide** | *Auditor Agent* | Teaches students how to use Zero-Shot prompts and monitor AI-generated outputs. |
| `src/main.c` | **Core Code** | *Architect* | The final, production-ready firmware for the ESP32-C3-based robot. |
| `src/buggy_wheels.c.example` | **Educational Bug** | *Developer* | A version of the drive code with intentional logic errors for student troubleshooting. |

## 🛠️ Key Educational Features
- **The "Opposite Wheels" Scenario**: A real-world hardware problem solved through software logic. Students learn how to flip motor polarity in code (Logical Abstraction).
- **AI-Human Interaction**: Explicit training for students to act as **Auditors** for AI-generated code, moving from simple consumption to critical oversight.
- **Micro-Lectures**: Bite-sized technical concepts (RISC-V, PWM, H-Bridges) ready for classroom delivery.

## 🔜 Next Steps
1.  **Hardware Validation**: Ask students to verify their GPIO cabling matches the definitions in `main.c`.
2.  **GenAI Session**: Have students run their first "Zero-Shot" prompts using the provided guide.
3.  **Stress Testing**: Use the **Auditor Agent** (me or the student) to verify the AI-generated "S-Curve" or "180-turn" logic.

> [!NOTE]
> The code is built for the **Seeed Studio XIAO ESP32-C3** using the **ESP-IDF** framework. Ensure students are familiar with the `idf.py build` and `idf.py flash` commands or the PlatformIO interface.

