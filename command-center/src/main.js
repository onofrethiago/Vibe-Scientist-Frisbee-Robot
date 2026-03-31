/**
 * main.js
 * All code snippets and prompts are provided "as-is" under the Apache 2.0 License. 
 * While the technical barriers to coding are lower, the responsibility for security, 
 * compliance (including HIPAA/GDPR), and output accuracy remains strictly with the human-in-the-loop. 
 * Copyright 2026 Thiago Borba Onofre, Licensed under the Apache License, Version 2.0
 */
import './style.css'

// -- STATE AND DOM COFIG --
const elements = {
  ip: document.getElementById('esp-ip'),
  apiKey: document.getElementById('api-key'),
  speed: document.getElementById('motor-speed'),
  status: document.getElementById('status-text'),
  indicator: document.getElementById('status-indicator'),
  logs: document.getElementById('log-container'),
  btnUp: document.getElementById('btn-up'),
  btnLeft: document.getElementById('btn-left'),
  btnRight: document.getElementById('btn-right'),
  btnDown: document.getElementById('btn-down'),
  btnStop: document.getElementById('btn-stop')
};

// -- PERSIST CONFIG --
const savedIP = localStorage.getItem('esp32_ip');
const savedKey = localStorage.getItem('esp32_key');
if (savedIP) elements.ip.value = savedIP;
else elements.ip.value = 'Frisbee.local';
if (savedKey) elements.apiKey.value = savedKey;

elements.ip.addEventListener('change', () => {
  localStorage.setItem('esp32_ip', elements.ip.value);
  addLog(`REMOTE IP UPDATED: ${elements.ip.value}`);
});
elements.apiKey.addEventListener('change', () => {
  localStorage.setItem('esp32_key', elements.apiKey.value);
  addLog('SHIELD KEY UPDATED');
});

// -- LOGGING UTILITY --
function addLog(msg, active = false) {
  const entry = document.createElement('div');
  entry.className = `log-entry ${active ? 'active' : ''}`;
  entry.innerText = `[${new Date().toLocaleTimeString()}] ${msg}`;
  elements.logs.prepend(entry);
}

// -- COMMAND EXECUTION --
async function sendCommand(action, params = {}) {
  const ip = elements.ip.value.trim();
  const speed = elements.speed.value;
  const key = elements.apiKey.value.trim();
  
  if (!ip) {
    addLog('SYSTEM ERROR: NO TARGET IP CONFIGURED');
    return;
  }

  const queryParams = new URLSearchParams({ ...params, speed, key });
  const url = `http://${ip}/${action}?${queryParams.toString()}`;

  try {
    const response = await fetch(url, { mode: 'cors' });
    if (response.ok) {
      elements.status.innerText = 'CONNECTED';
      elements.status.style.color = 'var(--primary)';
      elements.indicator.style.animation = 'pulse 0.5s infinite';
    } else {
      addLog(`ERR: SERVER REJECTED COMMAND (${response.status})`);
    }
  } catch (error) {
    addLog(`ERR: FAILED TO REACH ${ip}. ENSURE CORS IS ENABLED ON FIRMWARE.`);
    elements.status.innerText = 'OFFLINE';
    elements.status.style.color = 'var(--text-dim)';
    elements.indicator.style.animation = 'pulse 2s infinite';
  }
}

// -- BUTTON LOGIC --
const bindBtn = (el, dir, label) => {
  const startAction = () => {
    el.classList.add('active');
    addLog(`INITIATING: ${label}`);
    sendCommand('move', { dir });
  };
  
  const endAction = () => {
    el.classList.remove('active');
    sendCommand('stop');
  };

  el.addEventListener('mousedown', startAction);
  el.addEventListener('mouseup', endAction);
  el.addEventListener('mouseleave', endAction);
  
  // Touch support
  el.addEventListener('touchstart', (e) => { e.preventDefault(); startAction(); });
  el.addEventListener('touchend', (e) => { e.preventDefault(); endAction(); });
};

bindBtn(elements.btnUp, 'F', 'FORWARD THRUST');
bindBtn(elements.btnDown, 'B', 'REVERSE THRUST');

// Stop logic is special (doesn't need to hold)
elements.btnStop.addEventListener('mousedown', () => {
  addLog('EMERGENCY BRAKE ENGAGED');
  sendCommand('stop');
});

// Steer logic
elements.btnLeft.addEventListener('mousedown', () => {
  addLog('POINT TURN: PORT');
  sendCommand('move', { dir: 'L' }); // Ensure firmware supports L/R if needed, or define tank turns
});
elements.btnRight.addEventListener('mousedown', () => {
  addLog('POINT TURN: STARBOARD');
  sendCommand('move', { dir: 'R' });
});

// -- KEYBOARD CONTROL --
window.addEventListener('keydown', (e) => {
  if (e.repeat) return;
  const key = e.key.toUpperCase();
  if (key === 'W' || key === 'ARROWUP') elements.btnUp.dispatchEvent(new Event('mousedown'));
  if (key === 'S' || key === 'ARROWDOWN') elements.btnDown.dispatchEvent(new Event('mousedown'));
  if (key === 'A' || key === 'ARROWLEFT') elements.btnLeft.dispatchEvent(new Event('mousedown'));
  if (key === 'D' || key === 'ARROWRIGHT') elements.btnRight.dispatchEvent(new Event('mousedown'));
  if (key === ' ') elements.btnStop.dispatchEvent(new Event('mousedown'));
});

window.addEventListener('keyup', (e) => {
  const key = e.key.toUpperCase();
  if (['W', 'S', 'A', 'D', 'ARROWUP', 'ARROWDOWN', 'ARROWLEFT', 'ARROWRIGHT'].includes(key)) {
    elements.btnStop.dispatchEvent(new Event('mousedown'));
    elements.btnUp.classList.remove('active');
    elements.btnDown.classList.remove('active');
    elements.btnLeft.classList.remove('active');
    elements.btnRight.classList.remove('active');
  }
});

addLog('COMMAND CENTER READY. ENTER ROBOT IP TO START LINK.');
