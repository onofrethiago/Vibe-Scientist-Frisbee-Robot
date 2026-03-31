# 🔍 SENTINEL-NEXUS SECURITY AUDIT — Frisbee Robot

> **Status:** HARDENED 🛡️  
> **Protocol:** Zero-Trust (Shield Token Auth)  
> **Audit Date:** 2026-03-31

---

## 1. Executive Summary
The Frisbee Robot project has transitioned from a **"Trust-on-First-Sight"** architecture to a **Hardened Zero-Trust** model. Previously, anyone on the local network could command the hardware via unauthenticated HTTP endpoints. The current implementation introduces a private API key (Shield Token) and strict input boundary clamping.

---

## 2. Vulnerability Audit & Remediation

### [VULN-001]: Unauthenticated Control Interface
- **Severity:** **CRITICAL**
- **Vetor de ataque:** Local Network Hijacking.
- **Impacto:** Unauthorized physical control of the robot.
- **Remediação:** Implemented `hasValidKey()` middleware on the ESP32-C3 WebServer.
- **Status:** ✅ FIXED (Requires `?key=SECRET_API_KEY`)

### [VULN-002]: Lack of Input Rate Limiting & Bounds
- **Severity:** **HIGH**
- **Vetor de ataque:** Parameter Tampering / Overdrive.
- **Impacto:** Potential hardware damage due to out-of-bounds speed values.
- **Remediação:** Implemented `constrain(speed, 0, 255)` in firmware logic.
- **Status:** ✅ FIXED

### [VULN-003]: Information Disclosure
- **Severity:** **MEDIUM**
- **Vetor de ataque:** Error probing.
- **Impacto:** Leaking internal state through error messages.
- **Remediação:** Standardized response codes (401 for Unauthorized, 400 for Invalid Params).
- **Status:** ✅ FIXED

---

## 3. The "Secret Shield" Architecture
We implemented a **Double-Gated** security system:

1.  **The Secret Repository**: API Keys are stored in `arduino_secrets.h`, which is strictly excluded from Git via `.gitignore`.
2.  **The Shield Token Handshake**: The Vite UI (Command Center) saves the key in browser `localStorage` and includes it in the query string of every fetch request.

---

## 4. Cyber Teaching Moments (The Vibe Scientist)

### 🕵️ For Students: The "Invisibility" Fallacy
Local networks are often considered "safe zones." However, in modern cybersecurity, we assume the network is *already* compromised (**Zero-Trust**). We protect the **Resource** (the Robot), not just the **Perimeter** (the Router).

### 📏 For Teachers: Boundary Protection
By using `constrain()`, we prevent **"Logic Overflows."** If a user (or a bug) tries to send a speed of 500, the robot "safely degrades" it to 255. This is the foundation of building resilient systems.

---

## 5. Trade-off Log
- **Decision:** API Key in Query String vs. Request Headers.
- **Choice:** Query String (`?key=...`).
- **Rationale:** Simplicity. For an educational project using Arduino's `WebServer` library, query parameter parsing is more robust and easier for students to debug than custom header inspection.

---

*All code snippets and prompts are provided "as-is" under the Apache 2.0 License. Responsibility for security and output accuracy remains strictly with the human-in-the-loop. Copyright 2026 Thiago Borba Onofre, Licensed under the Apache License, Version 2.0*
