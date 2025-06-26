#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
const int pwmPin = 7;  // Pin where the PWM signal is connected


// Define the OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED display address
#define OLED_ADDRESS 0x3C

// Create an instance of the SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);    // Start serial communication
  pinMode(pwmPin, INPUT);  // Set the pin as input
    // Initialize the display with the correct I2C address
 // Create an instance of the SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
    for (;;)
      ;  // Don't proceed, loop forever
  }}

  void loop() {
    // Measure the high time and low time of the PWM signal
    unsigned long highTime = pulseIn(pwmPin, HIGH);
    unsigned long lowTime = pulseIn(pwmPin, LOW);

    if (highTime > 0 && lowTime > 0) {
      // Calculate the period and frequency
      unsigned long period = highTime + lowTime;  // in microseconds
      float frequency = 1000000.0 / period;       // Convert period to frequency in Hz

      display.clearDisplay();
      // Set text size and color
      display.setTextSize(1);               // Text size (1 is small, 2 is larger, etc.)
      display.setTextColor(SSD1306_WHITE);  // White text
      // Set the cursor position (x, y)
      display.setCursor(0, 0);
      display.println("PWM Received");
      display.setCursor(0, 0);
      display.print("Frequency : ");
      display.println(frequency);
      display.display();

      Serial.print("Frequency: ");
      Serial.print(frequency);
      Serial.println(" Hz");
    } else {
      Serial.println("No signal detected");
    }

    delay(1000);  // Wait for a second before measuring again
  }