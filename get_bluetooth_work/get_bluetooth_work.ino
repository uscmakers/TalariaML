#include <ArduinoBLE.h>



BLEService fitness_service("e267751a-ae76-11eb-8529-0242ac130003");

BLEIntCharacteristic exercise("2A19", BLERead | BLENotify); 
BLEByteCharacteristic start("19b10012-e8f2-537e-4f6c-d104768a1214", BLERead | BLEWrite);
BLEByteCharacteristic pause("6995b940-b6f4-11eb-8529-0242ac130003", BLERead | BLEWrite);
// BLEByteCharacteristic mode("6995b940-b6f4-11eb-8529-0242ac130004", BLERead | BLEWrite); // 0 voltage, 1 steps

BLEDevice central;

/**
* @brief      Arduino setup function
*/
void setup()
{
  pinMode(sensoroutput, INPUT);   // this function is used to declare led connected pin as output

  //Connect to bluetooth
  if (!BLE.begin()) {
    while (1);
  }

  BLE.setLocalName("Talaria");
  BLE.setAdvertisedService(fitness_service);

  start.setValue(0);
  pause.setValue(0);
  // mode.setValue(0);
  
  fitness_service.addCharacteristic(exercise); 
  fitness_service.addCharacteristic(start);
  fitness_service.addCharacteristic(pause);
  // fitness_service.addCharacteristic(mode);

  BLE.addService(fitness_service);

  BLE.advertise();

  while(1) {
    central = BLE.central();
    if (central) {
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    }
  }

}

bool startCounting = true;
int sensoroutput = 3; // the analog pin connected to the sensor
int idleThreshold = 100;
int numSteps = 0;
bool startStep = false;
int currMode = 0;


void loop()
{
    if (central.connected()) 
    {
      start.read();
      pause.read();
      // mode.read();
    }
    if (start.value()) 
    {
      startCounting = true;
      startStep = false;
      numSteps = 0;
      start.setValue(0);
    }
    if(pause.value()) 
    {
      startCounting = false;
      startStep = false;
      numSteps = 0;
      numSteps = 0;
      pause.setValue(0);
    }
    // currMode = mode.value();

    if(startCounting) {
      int value = analogRead(sensoroutput);  // function to read analog voltage from sensor
      if (value >= idleThreshold && !startStep) {
        startStep = true;
      } else if (value < idleThreshold && startStep) {
        startStep = false;
        numSteps++;
      }

      if (currMode == 0) { // voltage
        if (central.connected())
          exercise.writeValue(value);          
      } else {
        if (central.connected())
          exercise.writeValue(numSteps);          
      }
      delay(100);
    }
}
