#include <Arduino.h>
#include <Wire.h>
#include <SSD1306.h>
#include <SparkFun_APDS9960.h>
#include <DHTesp.h>
#include <Adafruit_Sensor.h>

///////////////////////////////////LAB2/////////////////////////////////////

SSD1306       display(0x3c, 4, 5, GEOMETRY_128_32);

const int RELAY = 15;
uint8_t proximity_data = 0;
int a = 0;

///////////////////////////////////LAB3/////////////////////////////////////
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;



void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  ///////////////////////////////////LAB3/////////////////////////////////////
  Serial.begin(115200);
  pinMode(RELAY,OUTPUT);
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
}
 
void loop() {
  
  // Read the proximity value
  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    if(proximity_data >= 20){
        Serial.print("Proximity: ");
        Serial.println(proximity_data);
        digitalWrite(RELAY,HIGH);
        delay(500);
        digitalWrite(RELAY,LOW);
        delay(500);
    }
    
  }
}