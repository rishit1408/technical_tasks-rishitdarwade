# Smartwatch Health Monitoring over LoRaWAN (Theoretical Design)

**Name:** Rishit Darwade  
**Phone:** 9322558733  
**Email:** rishitdarwade85@gmail.com  

## 1. Project Overview

**Objective:**  
Design a smartwatch that measures **heart rate** and **SpO₂**, transmits the data over **LoRaWAN** up to 3 km, and displays it on a **custom GUI**.

**Key Features:**
- Heart rate and SpO₂ monitoring
- Long-range wireless communication using LoRaWAN
- Real-time data visualization on GUI
- Low-power wearable operation

---

## 2. Block Diagram

<img width="338" height="415" alt="image" src="https://github.com/user-attachments/assets/248ac2ed-6b1a-44c8-841d-28f13bd23033" />

---

## 3. Bill of Materials (BOM)

| Component | Purpose | Example Part | Specifications / Notes |
|-----------|---------|--------------|------------------------|
| MCU / Processor | Main controller | STM32L4, ESP32-PICO | Low-power, small size, supports I²C/SPI, 32-bit |
| Heart rate + SpO₂ sensor | Measure health data | MAX30102 / MAX30105 | I²C interface, wrist-wearable, 1–5% SpO₂ accuracy |
| LoRa module | Wireless communication | SX1276 / SX1278 | LoRaWAN compliant, small PCB, 433/868/915 MHz |
| Battery | Power source | Li-Po 300–500 mAh | Thin, rechargeable, provides ~12–24 hours runtime depending on usage |
| Battery charging module | Charge battery safely | TP4056 | Supports micro-USB / USB-C input |
| Voltage regulator | Stable 3.3V supply | AMS1117 | Protects MCU and sensors from voltage fluctuations |
| Display (optional) | Show readings | OLED 0.96” I2C | Can display heart rate, SpO₂, battery status |
| Push button / touch input | User interface | Tactile switch | Optional start/stop measurement |
| PCB / Watch case | Assembly | Custom PCB & case | Compact wearable design, lightweight |

---

## 4. Theoretical Implementation Plan

**Step 1: Sensor Integration**
- MCU reads heart rate and SpO₂ via I²C from MAX30102.
- Data is processed to calculate beats per minute (BPM) and oxygen saturation.
- Optional filtering to remove noise from wrist movements.

**Step 2: LoRaWAN Communication**
- Processed data is sent to LoRa module via SPI.
- LoRaWAN protocol transmits data up to 3 km to a gateway.
- LoRaWAN ensures low-power and secure transmission.

**Step 3: Gateway & Server**
- LoRaWAN gateway receives data and forwards it to a server or MQTT broker.
- Server stores data for visualization and optionally for historical trends.

**Step 4: Custom GUI**
- GUI fetches data from the server in real-time.
- Displays heart rate, SpO₂, and optional alerts (e.g., low oxygen saturation).
- Can include line graphs to show trends over time.
- Color coding for safe/alert zones (green, yellow, red).

**Step 5: Power Management**
- MCU and sensors enter low-power mode when not measuring.
- Battery management ensures safe charging and longer runtime.
- Optional auto-sleep feature during inactivity.

---

## 5. Inside the Watch

All components inside the smartwatch must be **compact and low-power**:


- MCU: Small, low-power microcontroller (STM32L4 or ESP32-PICO)  
- Sensor: MAX30102 (5 × 5 mm)  
- LoRa Module: SX1276 / SX1278, small PCB  
- Battery: Thin Li-Po 300–500 mAh  
- Optional display: OLED 0.96”  

> The LoRa gateway, server, and GUI are external, so they do not affect the watch size.

---

## 6. LoRaWAN Overview

- LoRaWAN is a **long-range, low-power wireless protocol**.
- Provides communication range up to 3–5 km in open areas.
- Operates at low data rates, ideal for small packets like health sensor data.
- Uses **end-to-end encryption**, ensuring privacy of health information.
- Perfect for wearable devices where battery life is critical.

---

## 7. Software Stack (Theoretical)

| Layer | Software / Libraries | Purpose |
|-------|--------------------|---------|
| MCU Firmware | STM32CubeIDE / Arduino IDE | Read sensors, manage LoRa communication |
| LoRaWAN | LMIC / Semtech LoRaWAN stack | Handle long-range communication, packet formation |
| Server | MQTT broker (Mosquitto), Node-RED | Receive and process data from LoRa gateway |
| GUI | Web: ReactJS + Chart.js / Desktop: Python Dash | Display real-time health metrics and trends |

---

## 8. Power Estimation

- MAX30102 sensor: ~1.8 mA active  
- MCU: ~5–15 mA active, <1 mA sleep  
- LoRa transmission: ~20–30 mA per packet  
- Battery: 300 mAh Li-Po → ~12–24 hours runtime depending on measurement frequency  
- Strategies to save power:
  - Measure every 1–5 seconds instead of continuously  
  - Enter deep-sleep mode between readings  
  - Minimize display usage

---

## 9. GUI Mockup Ideas

- **Dashboard layout**: Real-time heart rate and SpO₂  
- **Trends chart**: Line graph showing readings over time  
- **Color coding**: Green = normal, Yellow = borderline, Red = alert  
- **Optional alerts**: Sound, notification, or email if SpO₂ < 90%  

---

## 10. Limitations / Challenges

- LoRaWAN range can be affected by **obstacles and interference**.  
- Wrist-worn SpO₂ readings can be **noisy due to movement**.  
- Battery size limits **continuous operation**; trade-off between runtime and measurement frequency.  
- Compact PCB design may be **challenging** to fit MCU, sensors, and LoRa module.  

---

## 11. Summary

This theoretical design provides:  
- A **complete BOM** for a smartwatch with health sensors and LoRaWAN communication.  
- A **block diagram** showing data flow from sensors to GUI.  
- A **step-by-step implementation plan** (theoretical).  
- Inside-watch component layout and low-power considerations.  
- Software stack, GUI mockup ideas, power estimation, and limitations.  

