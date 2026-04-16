IoT Pet Food & Water Dispenser
An automated, ESP32-powered pet care system featuring a motorized food flap and a water pump, controllable via the Blynk IoT mobile app.

Project Overview
This project provides a discreet, reliable way to manage pet nutrition remotely. Utilizing an ESP32 as the central hub, it controls a servo-driven food dispenser and a relay-switched water pump. The system is designed for PETG-printed housings to ensure durability and food safety.

Hardware Components
Microcontroller: ESP32 (38-pin or 30-pin variant)

Food Mechanism: SG90 Micro Servo (9g)

Water Mechanism: RS360 Mini DC Water Pump

Switching: 5V Single Channel Relay Module

Power Supply: 5V 1.5A DC Adapter (Common ground with ESP32)

Materials: 3D Printed PETG Housing

Wiring Diagram
Component	                  ESP32 Pin	                    Notes
SG90 Servo               (Signal)	GPIO 13	             PWM Control
Relay                    (Signal)	GPIO 12	       Switches 5V to Water Pump
Relay VCC	                   5V / VIN	             Ensure common ground
RS360 Pump	               Relay COM/NO	         Powered by the 5V Adapter


Note: The RS360 pump can draw significant current on startup. Ensure your 5V 1.5A adapter is dedicated to the power rail, while the ESP32 is powered via the same rail or USB.

Blynk Cloud Configuration
The system uses Blynk 2.0 for remote monitoring and manual overrides.

V1 (Button): Toggle Water Pump (Digital High/Low)

V2 (Slider/Button): Dispense Food (Trigger Servo position 0° to 90°)

Installation & Setup
Mechanical Assembly:

Mount the SG90 Servo internally to keep the mechanism discreet.

Install the RS360 Pump in a separate reservoir, ensuring the relay is housed in a dry compartment.

Software Configuration:

Install the Blynk and ESP32Servo libraries in your Arduino IDE.

Update the BLYNK_TEMPLATE_ID, BLYNK_DEVICE_NAME, and BLYNK_AUTH_TOKEN in the source code.

Input your WiFi credentials in the char ssid[] and char pass[] variables.

Deployment:

Flash the code to the ESP32 via Mac/PC.

Test the servo range to ensure the PETG flap opens fully without hitting the housing.

Mechanical Design Notes
Discreet Flap: The food flap is designed to sit flush with the dispenser body.

PETG Printing: High-strength PETG is used for the mechanical parts to withstand the torque of the SG90 and provide better moisture resistance near the water pump.

Clearance: Maintain a 0.5mm - 1.0mm gap between the flap and the main body to prevent friction jams.

License
This project is open-source. Feel free to modify the CAD files and code for your specific pet's needs.
