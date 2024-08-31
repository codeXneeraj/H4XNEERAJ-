/*
  ESP32 Code for Text-to-Speech with Arduino Mega Integration

  **Connection Details:**

  **Arduino Mega to ESP32:**
  - TX1 (Pin 18) of Arduino Mega -> RX (GPIO 16) of ESP32
  - RX1 (Pin 19) of Arduino Mega -> TX (GPIO 17) of ESP32
  - GND of Arduino Mega -> GND of ESP32

  **ESP32 to Audio Amplifier:**
  - DAC Output (GPIO 25) of ESP32 -> Audio Amplifier Input (IN+)
  - GND of ESP32 -> Audio Amplifier Ground (IN-)

  **Audio Amplifier to Speaker:**
  - Audio Amplifier Output (+) -> Speaker (+) Terminal
  - Audio Amplifier Output (-) -> Speaker (-) Terminal

  This code receives text from the Arduino Mega via serial communication,
  converts the text to speech using the ESP32's TTS library, and outputs 
  the speech through an audio amplifier connected to a speaker.
*/

#include <ESP8266SAM.h>

// Create a TTS (Text-To-Speech) object
SAM tts;  

// Define DAC pin for audio output
const int dacPin = 25;  // Connect to Audio Amplifier Input (IN+)

void setup() {
  // Initialize the TTS library with the DAC pin
  tts.begin(dacPin);

  // Start serial communication at 9600 baud rate to match Arduino Mega
  Serial.begin(9600);  

  // Configure the DAC pin as an output (for audio)
  pinMode(dacPin, OUTPUT);
}

void loop() {
  // Check if there is incoming data from Arduino Mega
  if (Serial.available()) {
    // Read the incoming text from Arduino Mega
    String textToSpeak = Serial.readStringUntil('\n');

    // Convert the text to speech and output it through the DAC pin
    tts.say(textToSpeak.c_str());
  }

  // Small delay to avoid overwhelming the serial buffer
  delay(100);
}
