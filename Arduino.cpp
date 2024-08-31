/*
  Arduino Mega Code for Sensor Handling and Communication with ESP32

  **Connection Details:**

  **Arduino Mega to ESP32:**
  - TX1 (Pin 18) of Arduino Mega -> RX (GPIO 16) of ESP32
  - RX1 (Pin 19) of Arduino Mega -> TX (GPIO 17) of ESP32
  - GND of Arduino Mega -> GND of ESP32

  **Sensors:**
  - Ultrasonic Sensor:
    - TRIG pin -> Pin 9 on Arduino Mega
    - ECHO pin -> Pin 10 on Arduino Mega
  - Touch Sensor:
    - Signal pin -> Pin 11 on Arduino Mega

  This code reads inputs from an ultrasonic sensor and a touch sensor,
  and sends text responses to the ESP32 based on these inputs. Responses
  are predefined and related to sensor data or received questions.
*/

const int trigPin = 9;  // Trigger pin for ultrasonic sensor
const int echoPin = 10; // Echo pin for ultrasonic sensor
const int touchPin = 11; // Touch sensor pin

// Define question-response pairs
const int numResponses = 6;
const char* questions[numResponses] = {
  "How are you?",
  "What is your name?",
  "What time is it?",
  "Tell me a joke.",
  "Where am I?",
  "Goodbye!"
};

const char* answers[numResponses] = {
  "I am doing great, thank you!",
  "I am a friendly robot.",
  "I don't have a clock, but I am always here!",
  "Why don't scientists trust atoms? Because they make up everything!",
  "You are where you are supposed to be.",
  "Goodbye! Have a nice day!"
};

void setup() {
  Serial1.begin(9600);  // Start serial communication on Serial1 (TX1/RX1 pins)
  pinMode(trigPin, OUTPUT);  // Set TRIG pin as output
  pinMode(echoPin, INPUT);   // Set ECHO pin as input
  pinMode(touchPin, INPUT);  // Set touch sensor pin as input
}

void loop() {
  long duration;
  int distance;
  int touchState = digitalRead(touchPin);  // Read touch sensor state

  // Read distance from ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;  // Convert duration to distance in cm

  // Handle touch sensor response
  if (touchState == HIGH) {
    Serial1.println("You touched me!");
  } else {
    // Placeholder for receiving a question from a source
    String receivedText = "";  // Replace this with actual text input

    // Check if the received text matches any question
    bool questionMatched = false;
    for (int i = 0; i < numResponses; i++) {
      if (receivedText.indexOf(questions[i]) != -1) {
        Serial1.println(answers[i]);  // Send the corresponding answer
        questionMatched = true;
        break;
      }
    }

    // If no question matched, provide a default response based on distance
    if (!questionMatched) {
      if (distance < 10) {
        Serial1.println("You are very close!");
      } else if (distance >= 10 && distance < 50) {
        Serial1.println("You are at a moderate distance.");
      } else {
        Serial1.println("You are far away!");
      }
    }
  }

  delay(1000);  // Delay between readings
}
