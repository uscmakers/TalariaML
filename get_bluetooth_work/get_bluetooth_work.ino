#include <ArduinoBLE.h>

bool flag = true;


BLEService fitness_service("e267751a-ae76-11eb-8529-0242ac130003");

BLEIntCharacteristic exercise("2A19", BLERead | BLENotify); 
BLEByteCharacteristic start("19b10012-e8f2-537e-4f6c-d104768a1214", BLERead | BLEWrite);
BLEByteCharacteristic pause("6995b940-b6f4-11eb-8529-0242ac130003", BLERead | BLEWrite);

BLEDevice central;


/**
* @brief      Arduino setup function
*/
void setup()
{
    //Connect to bluetooth
    if (!BLE.begin()) {
      //Serial.println("starting BLE failed!");
      while (1);
    }

    BLE.setLocalName("Talaria");
    BLE.setAdvertisedService(fitness_service);

    start.setValue(0);
    pause.setValue(0);
    
    fitness_service.addCharacteristic(exercise); 
    fitness_service.addCharacteristic(start);
    fitness_service.addCharacteristic(pause);

    BLE.addService(fitness_service);

    BLE.advertise();

    //Serial.println("Bluetooth device active, waiting for connections...");

    while(1) {
      central = BLE.central();
      // Serial.println("Trying to connect to central");
      //Serial.println(BLE.central());
      if (central) {
        //Serial.print("Connected to central: ");
        // print the central's BT address:
        //Serial.println(central.address());
        // turn on the LED to indicate the connection:
        digitalWrite(LED_BUILTIN, HIGH);

        break;
      }
    }

}

int i = 0;
/**
* @brief      Get data and run inferencing
*/
void loop()
{
    if (central.connected()) 
    {
        start.read();
        pause.read();
    }
    if (start.value()) 
    {
        flag = true;
        i = 0;
        start.setValue(0);
    }
    if(pause.value()) 
    {
         flag = false;
         i = 0;
         pause.setValue(0);
    }


    if(flag == true) {
        if(true)
        {
                 if(true)
                 {
                    if (central.connected()) exercise.writeValue(i);
                    i++;
                    delay(100);
                  }
               //}
      
         }
    }
         
// #endif
    }


