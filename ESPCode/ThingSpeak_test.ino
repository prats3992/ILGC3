/**
* Code to test ThingSpeak API
*/

// ------style guard ----

#ifdef __cplusplus

extern "C"

{

  #endif

  uint8_t temprature_sens_read();

  #ifdef __cplusplus

}

#endif

uint8_t temprature_sens_read();

// ------header files----

#include <WiFi.h>

#include "ThingSpeak.h"

// -----netwrok credentials

const char * ssid = "Smart Devices"; // your network SSID (name)

const char * password = "Devices@2023"; // your network password

WiFiClient client;

// -----ThingSpeak channel details

unsigned long myChannelNumber = 1;

const char * myWriteAPIKey = "8IZGBOUN0CQP64MV";

// ----- Timer variables

unsigned long lastTime = 0;

unsigned long timerDelay = 1000;

void setup() {

  Serial.begin(115200); // Initialize serial

  WiFi.mode(WIFI_STA);

  if (WiFi.status() != WL_CONNECTED)

  {

    Serial.print("Attempting to connect");

    while (WiFi.status() != WL_CONNECTED)

    {

      WiFi.begin(ssid, password);
      Serial.print("Trying to connect... (");
      Serial.print(ssid);
      Serial.print(")(");
      Serial.print(password);
      Serial.println(")");

      delay(1000);

    }

    Serial.println("\nConnected. ");

  }

  ThingSpeak.begin(client); // Initialize ThingSpeak

}

void loop() {

  if ((millis() - lastTime) > timerDelay)

  {

    int hall_value = 0;

    float temperature = 0;

    hall_value = hallRead();

    // Get a new temperature reading

    temperature = ((temprature_sens_read() - 32) / 1.8);

    Serial.print("Temperature (ºC): ");

    Serial.print(temperature);

    Serial.println("ºC");

    Serial.print("Hall value:");

    Serial.println(hall_value);

    ThingSpeak.setField(1, temperature);

    ThingSpeak.setField(2, hall_value);

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different

    // pieces of information in a channel. Here, we write to field 1.

    int x = ThingSpeak.writeFields(myChannelNumber,

      myWriteAPIKey);

    if (x == 200)

    {

      Serial.println("Channel update successful.");

    } else

    {

      Serial.println("Problem updating channel. HTTP error code " + String(x));

    }

    lastTime = millis();

  }
  delay(3000);
}
