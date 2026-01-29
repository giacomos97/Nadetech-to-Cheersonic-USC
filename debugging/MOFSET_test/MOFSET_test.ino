# Define MOFSET control pin
const int mosfetPin = 9;

void setup() {

  # Configure digital pin
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW);

  # Start serial communication
  Serial.begin(9600);
  Serial.println("Commands:  1 = ON, 0 = OFF. Type your command:");
}

void loop() {

  if (Serial.available() > 0) {
    # Read user command from terminal
    char received = Serial.read();

    if (received == '1') {
      digitalWrite(mosfetPin, HIGH);
      Serial.println("Status = ON");
    }
    else if (received == '0') {
      digitalWrite(mosfetPin, LOW);
      Serial.println("Status = OFF");
    }
    else{
      Serial.println("Invalid command.");
    }
  }
}
