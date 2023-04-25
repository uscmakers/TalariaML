/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
// #include <Fitness_App_inferencing.h>
// #include <Arduino_LSM9DS1.h> //Click here to get the library: http://librarymanager/All#Arduino_LSM9DS1
// #include <Arduino_LPS22HB.h> //Click here to get the library: http://librarymanager/All#Arduino_LPS22HB
// #include <Arduino_HTS221.h> //Click here to get the library: http://librarymanager/All#Arduino_HTS221
// #include <Arduino_APDS9960.h> //Click here to get the library: http://librarymanager/All#Arduino_APDS9960
#include <ArduinoBLE.h>



/* Constant defines -------------------------------------------------------- */
#define CONVERT_G_TO_MS2    9.80665f
#define MAX_ACCEPTED_RANGE  2.0f        // starting 03/2022, models are generated setting range to +-2,
                                        // but this example use Arudino library which set range to +-4g. 
                                        // If you are using an older model, ignore this value and use 4.0f instead
/** Number sensor axes used */
// #define N_SENSORS     18

/* Forward declarations ------------------------------------------------------- */


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

    //Karakteristike
    
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
        //Serial.println("Started");
        start.setValue(0);
    }
    if(pause.value()) 
    {
         flag = false;
         //Serial.println("Stopped");
         pause.setValue(0);
    }


  // flag = true;

    if(flag == true) {
        if(true)
        {
                 if(true)
                 {
                    // IDK what to do with this code?

                    // Label = String(result.classification[ix].label);
                     //Serial.println(String(result.classification[ix].label));
                    //  if (String(result.classification[ix].label) == "Step")
                    //  {
                       if (central.connected()) exercise.writeValue(0);
                       //Serial.println("Data sent");
                     //}
                    //  else if (String(result.classification[ix].label) == "Squats")
                    //  {
                        if (central.connected()) exercise.writeValue(1);
                        //Serial.println("Data sent");
                    // }
                    //  else if (String(result.classification[ix].label) == "Pushup")
                    //  {
                        if (central.connected()) exercise.writeValue(2);
                        // Serial.println("Data sent");
                    // }
        
                  }
               //}
      
         }
    }
         
// #endif
    }


