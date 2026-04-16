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

Source Code:

#define BLYNK_PRINT Serial
/* Fill in information from your Blynk Template here */
#define BLYNK_TEMPLATE_ID "TMPL60tWlNaEE"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN  "o_pmVfrApCIghOyklFftgvSuMhqStxxI"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Function Prototypes
void feedPet(); 
void waterPet(); 

Servo foodDispenser;

// ESP32-S3 Pin Selection: 
// GPIO 18 and 19 are valid, but ensure they don't conflict with your board's native USB/JTAG
const int servoPin = 18; 
const int relayPin = 10; 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Your WIFI name"; 
char pass[] = "WIFI password"; 

// --- BLYNK DASHBOARD LISTENERS ---

BLYNK_WRITE(V1) {
  if (param.asInt() == 1) {
    Serial.println("Blynk command received: FEEDING!");
    feedPet();
  }
}

BLYNK_WRITE(V2) {
  if (param.asInt() == 1) {
    Serial.println("Blynk command received: WATERING!");
    waterPet();
  }
}

void setup() {
  // Use a longer delay for S3 USB Serial to initialize properly
  Serial.begin(115200);
  delay(3000); 
  
  // ESP32-S3 Specific: Allocate hardware timers for PWM
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  
  foodDispenser.setPeriodHertz(50);    // Standard 50hz servo
  foodDispenser.attach(servoPin, 500, 2400); // S3 often prefers explicit min/max pulse widths
  
  foodDispenser.write(0); 
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); 
  
  Serial.println("ESP32-S3 System Ready.");
  
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run(); 
}

// --- HARDWARE ACTION SEQUENCES ---

void feedPet() {
  Serial.println("Opening trapdoor...");
  foodDispenser.write(90); 
  delay(3000);             
  Serial.println("Closing trapdoor...");
  foodDispenser.write(0);  
}

void waterPet() {
  Serial.println("Pump ON...");
  digitalWrite(relayPin, HIGH); 
  delay(4000); 
  Serial.println("Pump OFF.");
  digitalWrite(relayPin, LOW);  
}
