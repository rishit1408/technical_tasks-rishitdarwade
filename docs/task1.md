## Task 1 - Linear Actuator Position Control and PPR Control

**MCU:** STM32F446RE

### Task Overview

Aim is to achieve **position control of a Linear Actuator**. Feedback unit is a simple **potentiometer** mechanically coupled with the actuator stroke. A bare-bone **PID control** is implemented. A simple code demonstrates position control with **4 set points**. The position can be selected by manipulating a variable in a debug session.

After this is achieved, a **PPR (Pilot-Operated Pressure Relief) valve** is to be controlled. The valve is manipulated using the linear actuator based on readings from a **pressure sensor** connected to a 12-bit ADC.

### Code Flow & Control Algorithm

1. **Timer Configuration**
   - **TIMER2**: Triggers at **100 Hz** to run the **control loop**.
   - **TIMER3**: Configured for **PWM generation** on **PA6**, which drives the linear actuator motor.

2. **Position Feedback**
   - Potentiometer attached to the actuator provides **position feedback**.
   - **ADC1** reads values in the range **0–4095**, corresponding to the actuator stroke.

3. **PID Control for Actuator**
   - The **error** is calculated as the difference between the **target position** and the **current position**.
   - PID output is converted into a **PWM duty cycle**.
   - **TIMER3 PWM** on PA6 is updated to drive the actuator motor.

4. **PPR Valve Control**
   - **ADC2** reads the **pressure sensor** value.
   - Based on **set pressure** and **relief pressure**, the actuator moves to **open or close the valve**.
   - This control loop runs in the **TIMER2 callback**.

### Summary

- **Linear actuator positions** are controlled via PID using **ADC1 feedback**.
- **PWM generation** uses **TIMER3 on PA6**.
- **PPR valve** is controlled via the actuator based on **pressure sensor readings (ADC2)**.

 ### Limitations / Drawbacks

- The code attempts to be modular, but some aspects could not be fully abstracted.
- Separate variables had to be declared for **ADC1 and ADC2 outputs**, rather than using a unified data structure or generic ADC handler.
- As a result, adding additional sensors or actuators would require duplicating code, reducing scalability.
- Future improvements could include creating a **generic ADC read function** and a **unified actuator control module** to handle multiple inputs more cleanly.

