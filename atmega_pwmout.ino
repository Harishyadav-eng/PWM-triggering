#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int pwmPin = 7;      // Pin where the PWM signal is connected
const int relayPin = 6;    // Pin connected to the relay

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED display address
#define OLED_ADDRESS 0x3C

// Create an instance of the SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);  

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop execution if the display fails to initialize
  }

  // Set up the pins
  pinMode(pwmPin, INPUT);    // Set the PWM pin as input
  pinMode(relayPin, OUTPUT); // Set the relay pin as output
  digitalWrite(relayPin, HIGH); // Initially turn off the relay (active-low)

  // Initial display: Show "PWM Receiver"
  display.clearDisplay();  // Clear the display buffer
  display.setTextSize(2);  // Set text size to small (1)
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
  display.setCursor(0, 0);  // Position at the top left (x: 0, y: 0)
  display.println("   PWM");
  display.println(" Receiver");
  display.display();  // Show "PWM Receiver" on the OLED

  delay(2000); // Delay for 2 seconds before showing frequency
}

void loop() {
  // Measure the high time and low time of the PWM signal
  unsigned long highTime = pulseIn(pwmPin, HIGH);
  unsigned long lowTime = pulseIn(pwmPin, LOW);

  if (highTime > 0 && lowTime > 0) {
    // Calculate the period and frequency
    unsigned long period = highTime + lowTime; // in microseconds
    float frequency = 1000000.0 / period;      // Convert period to frequency in Hz

    // Print the frequency to the Serial Monitor
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Second display: Clear the screen and show frequency and range
    display.clearDisplay();  // Clear the display buffer
    display.setTextSize(2);  // Set text size to small (1)
    display.setTextColor(SSD1306_WHITE);  // Set text color to white

    // First line: Display "Frequency"
    display.setCursor(0, 0);  // Set cursor at the top left (x: 0, y: 0)
    display.print("Freq: ");
   // display.print(frequency);
    //display.println(" Hz");

    // Second line: Display frequency range directly below the frequency
    display.setCursor(0, 16); 
    display.print(frequency); // Position cursor below the first line
    display.println("Hz");

    // Show the display buffer on the OLED
    display.display();

    // Control the relay based on frequency
    if (frequency >= 1950 && frequency <= 3000) {
      digitalWrite(relayPin, LOW);  // Activate the relay (turn it on)
      delay(5000);
      digitalWrite(relayPin, HIGH);
    } else {
      digitalWrite(relayPin, HIGH); // Deactivate the relay (turn it off)
    }
  } else {
    // No PWM signal detected10
    Serial.println("No signal detected");

    // Ensure the relay stays off
    digitalWrite(relayPin, HIGH);

    // Clear the display and show "No signal"
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PWM Receiver");
    display.setCursor(0, 16);
    display.println("No signal detected");
    display.display();
  }

  delay(1000); // Wait for a second before measuring again
}
