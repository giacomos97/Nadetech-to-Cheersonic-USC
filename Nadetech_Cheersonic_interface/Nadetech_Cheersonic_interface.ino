#include <SoftwareSerial.h>

SoftwareSerial Slave(11, 10); // Pin assignement

char val;
char inputBuffer[20]; // Buffer for incoming commands
int inputIndex = 0;
bool commandReceived = false;
bool generatorEnabled = false;

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
  
  //Serial monitor
  Serial.begin(9600);
  Serial.println("Serial intialised");
  
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
      inputBuffer[inputIndex] = '\0'; // Null-terminate the string
      commandReceived = true;
      inputIndex = 0;
    } else {
      inputBuffer[inputIndex++] = val;
    }
  }

  // Process command if received
  if (commandReceived) {
    delay(3); // "Allow 2.5 ms between commands"

    if (strcmp(inputBuffer, "getSTATE") == 0) {
      
      // Send dummy 80-byte response
      if (generatorEnabled){
        Slave.write(dummyResponseEnabled, 80); // Return working enabled
        Serial.println("Working enabled\r");
      }else{
        Slave.write(dummyResponseDisabled, 80); // Return working disabled
        Serial.println("Working disabled\r");
      }

    } else if (strcmp(inputBuffer, "ENABLE") == 0) { // ENABLE command
      generatorEnabled = true;
      Slave.write("TRUE\r");
      Serial.println("Enabled\r");
      
    } else if (strcmp(inputBuffer, "DISABLE") == 0) { // DISABLE command
      generatorEnabled = false;
      Slave.write("TRUE\r");
      Serial.println("Disabled\r");    
    }

    commandReceived = false;
  }
}
