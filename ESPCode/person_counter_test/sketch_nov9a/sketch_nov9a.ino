#include <ThingSpeak.h>

#include <WiFi.h>

// -----netwrok credentials

const char *ssid = "Smart Devices"; // your network SSID (name)

const char *password = "Devices@2023"; // your network password

WiFiClient client;

// -----ThingSpeak channel details

unsigned long myChannelNumber = 1;

const char *myWriteAPIKey = "8IZGBOUN0CQP64MV";

// ----- Timer variables

unsigned long lastTime = 0;

unsigned long timerDelay = 1000;

int LDR_out_Val = 0; /*Variable to store photoresistor value*/
int LDR_in_Val = 0;  /*Variable to store photoresistor value*/
int sensor_out = 34; /*Analogue Input for photoresistor*/
int sensor_in = 35;
int occupancy = 0;

void setup()
{
  Serial.begin(9600); /*Baud rate for serial communication*/
  pinMode(sensor_out, INPUT);
  pinMode(sensor_in, INPUT);

  // WiFi.mode(WIFI_STA);

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
void loop()
{
  LDR_out_Val = analogRead(sensor_out); /*Analog read LDR value*/
  LDR_in_Val = analogRead(sensor_in);   /*Analog read LDR value*/
  Serial.print("LDR_in: ");
  Serial.println(LDR_out_Val);
  Serial.print("LDR_out: ");
  Serial.println(LDR_in_Val);

  if (LDR_out_Val > 1500)
  {
    if (LDR_in_Val < 1500)
      occupancy++;
  }
  if (LDR_in_Val > 1500)
  {
    if (LDR_out_Val < 1500)
      occupancy--;
  }
  if (occupancy < 0)
    occupancy = 0;

  ThingSpeak.setField(1, occupancy);

  Serial.print("Occupancy: ");
  Serial.println(occupancy);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (x == 200)
    Serial.println("Channel update successful.");
  else
    Serial.println("Problem updating channel. HTTP error code " + String(x));

  delay(2000);
}