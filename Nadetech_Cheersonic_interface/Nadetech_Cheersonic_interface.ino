#include <SoftwareSerial.h>

// Arduino board pin assignement
SoftwareSerial Slave(11, 10);

// MOSFET pin assignement
const int mosfetPin = 9;

// Variable and buffer to collect incoming RS485 commands
char val;
char inputBuffer[20];           

// Variables to trigger responses when RS485 command received
int inputIndex = 0;
bool commandReceived = false;

// Track current ON/OFF state of the USC generator
bool generatorEnabled = false;

// Dummy responses to getSTATE request. 
/* Refer to https://github.com/PiezoDrive/RS485-API/blob/master/README.md#get-amplifier-state */

char dummyResponseDisabled[80] = {
  0, 0, 0, 0, 0, 0, 0, 0, // (enabled, phase tracking, etc.)
  0x00, 0x00, 0xC8, 0x42, // 230.0 (voltage)
  0x00, 0x00, 0x00, 0x42, // 50.0 (frequency)
  0x00, 0x00, 0x00, 0x42, // 50.0 (min frequency)
  0x00, 0x00, 0x00, 0x42, // 50.0 (max frequency)
  0x00, 0x00, 0x00, 0x00, // 0.0 (target phase)
  0x00, 0x00, 0x00, 0x00, // 0.0 (phase control gain)
  0x00, 0x00, 0x00, 0x00, // 0.0 (target current)
  0x00, 0x00, 0x00, 0x00, // 0.0 (current control gain)
  0x00, 0x00, 0x00, 0x00, // 0.0 (target power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (power control gain)
  0x00, 0x00, 0x00, 0x00, // 0.0 (max load power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (amplifier power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (load power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (temperature)
  0x00, 0x00, 0x00, 0x00, // 0.0 (measured phase)
  0x00, 0x00, 0x00, 0x00, // 0.0 (measured current)
  0x00, 0x00, 0x00, 0x00  // 0.0 (impedance)
};

char dummyResponseEnabled[80] = {
  1, 0, 0, 0, 0, 0, 0, 0, // (enabled, phase tracking, etc.)
  0x00, 0x00, 0xC8, 0x42, // 230.0 (voltage)
  0x00, 0x00, 0x00, 0x42, // 50.0 (frequency)
  0x00, 0x00, 0x00, 0x42, // 50.0 (min frequency)
  0x00, 0x00, 0x00, 0x42, // 50.0 (max frequency)
  0x00, 0x00, 0x00, 0x00, // 0.0 (target phase)
  0x00, 0x00, 0x00, 0x00, // 0.0 (phase control gain)
  0x00, 0x00, 0x00, 0x00, // 0.0 (target current)
  0x00, 0x00, 0x00, 0x00, // 0.0 (current control gain)
  0x00, 0x00, 0x00, 0x00, // 0.0 (target power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (power control gain)
  0x00, 0x00, 0x00, 0x00, // 0.0 (max load power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (amplifier power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (load power)
  0x00, 0x00, 0x00, 0x00, // 0.0 (temperature)
  0x00, 0x00, 0x00, 0x00, // 0.0 (measured phase)
  0x00, 0x00, 0x00, 0x00, // 0.0 (measured current)
  0x00, 0x00, 0x00, 0x00  // 0.0 (impedance)
};

void setup() {
  
  // Initialize the MOSFET control pin
  pinMode(mosfetPin, OUTPUT);

  // Start with the Cheersonic generator off
  digitalWrite(mosfetPin, LOW);

  //Computer-Arduino interface
  Serial.begin(9600);
  
  //Arduino-Nadetech interface
  Slave.begin(9600);

}

void loop() {
  
  // Forward data from Serial input to Slave
  while (Serial.available()) {
    val = Serial.read();
    Slave.write(val);
  }

  // Collect data from Slave into inputBuffer
  while (Slave.available()) {
    val = Slave.read();

    if (val == '\r') {
      // Command received
      inputBuffer[inputIndex] = '\0';   // Null-terminate the string
      commandReceived = true;           // Trigger response via RS485
      inputIndex = 0;                   // Reset input index counter
    } else {
      // Command not received, contine recording in buffer
      inputBuffer[inputIndex++] = val;
    }
  }

  // Respond via RS485 if command received
  if (commandReceived) {
    delay(3); // "Allow 2.5 ms between commands"

    if (strcmp(inputBuffer, "getSTATE") == 0) {
      // Respond to getSTATE request

      if (generatorEnabled){
        // Send dummy 80-byte enabled response
        Slave.write(dummyResponseEnabled, 80);
        Serial.println("Working enabled\r");
      }else{
        // Send dummy 80-byte disabled response
        Slave.write(dummyResponseDisabled, 80);
        Serial.println("Working disabled\r");
      }

    } else if (strcmp(inputBuffer, "ENABLE") == 0) {

      if (!generatorEnabled){
        // Enable Cheersonic generator
        digitalWrite(mosfetPin, HIGH);
      }
      // Respond to ENABLE request
      generatorEnabled = true;  // Keep track of new state
      Slave.write("TRUE\r");
      Serial.println("Enabled\r");
      
    } else if (strcmp(inputBuffer, "DISABLE") == 0) {

      if (generatorEnabled){
        // Disable Cheersonic generator
        digitalWrite(mosfetPin, LOW);
      }

      // Respond to DISABLE request
      generatorEnabled = false; // Keep track of new state
      Slave.write("TRUE\r");
      Serial.println("Disabled\r");    
    }

    commandReceived = false;  // Reset response trigger
  }
}
