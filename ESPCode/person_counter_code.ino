int LDR_out_Val = 0;
int LDR_in_Val = 0;
int sensor_out = 2;
int sensor_in = 5;
int occupancy = 0;

void setup() {
    Serial.begin(9600);
    /* Setting Both Sensors as Input Devices */
    pinMode(sensor_out, INPUT);
    pinMode(sensor_in, INPUT);
}

void loop() {
    /* Reading Output Value of LDRs */
    LDR_out_Val = analogRead(sensor_out);
    LDR_in_Val = analogRead(sensor_in);

    /* Printing Input Values to Serial Monitor */
    Serial.print("LDR_in: ");
    Serial.println(LDR_out_Val);
    Serial.print("LDR_out: ");
    Serial.println(LDR_out_Val);

    /* If Outside LDR is cut First while Inside LDR is Not Cut, Add Person */
    if (LDR_out_Val > 2000){
      if (LDR_in_Val < 2000) occupancy++;
    }

    /* If Inside LDR is cut First while Outside LDR is Not Cut, Subtract Person */
    if (LDR_in_Val > 2000){
      if (LDR_out_Val < 2000) occupancy--;
    }

    /* If Encountering Negative Values of Occupancy, Reset to 0 */
    if (occupancy < 0) occupancy = 0;

    /* Printing Occupancy Values to Serial Monitor */
    Serial.print("Occupancy: ");
    Serial.println(occupancy);
    
    delay(2000);
}
