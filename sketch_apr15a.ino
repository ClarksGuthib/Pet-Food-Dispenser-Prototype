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
char ssid[] = "PLDTHOMEFIBRYhRzH"; 
char pass[] = "PLDTWIFIxubDG"; 

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