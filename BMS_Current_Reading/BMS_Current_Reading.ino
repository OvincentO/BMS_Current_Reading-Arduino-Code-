#include <Wire.h>
#include <Adafruit_SSD1306.h>

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected using I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ACS758LCB-050B-PFF-T sensor configuration
const int currentSensorPin = A0;  // Analog input pin connected to the sensor
const float offsetVoltage = 2.5;  // Offset voltage at 0A (2.5V for ACS758LCB-050B-PFF-T)
const float sensitivity = 0.04;   // Sensitivity for ACS758LCB-050B-PFF-T (40mV/A)

// Function to initialize the OLED display
void setup() {
  Serial.begin(9600);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0,0);      // Start at top-left corner
  display.print("Initializing...");
  display.display();
  delay(2000);
}

// Function to read and display current
void loop() {
  int sensorValue = analogRead(currentSensorPin);  // Read the sensor value
  float voltage = sensorValue * (5.0 / 1023.0);    // Convert to voltage
  float current = (voltage - offsetVoltage) / sensitivity; // Calculate current
  
  // Display the current on the OLED
  display.clearDisplay();
  display.setCursor(0,0); 
  display.print("Current: ");
  display.print(current);
  display.println(" A");
  display.display();
  
  // Print the current value to the Serial Monitor (optional)
  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");
  
  delay(1000);  // Update every 1 second
}



/* 
Explanation:
Libraries: The code uses the Adafruit_SSD1306 library for controlling the OLED display.
Pin Configuration: The ACS758LCB-050B-PFF-T current sensor is connected to the A0 pin of the Arduino. The OLED display is connected via I2C.
Calculations:
The sensor's output voltage is read and converted to current using the formula:
Current (A) = (Voltage − Offset Voltage)/Sensitivity

where:
Offset Voltage is the output at 0A (2.5V for this sensor).
Sensitivity is 40mV/A for the ACS758LCB-050B-PFF-T.
Display: The current value is displayed on the OLED in real-time.
Make sure you have the correct libraries installed (Adafruit_SSD1306 and Adafruit_GFX) and the OLED is connected properly to your Arduino.








*/