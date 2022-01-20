#include <EEPROM.h> // for tds
#include "GravityTDS.h"
#include <OneWire.h> // for temperature
#include <DallasTemperature.h>
#include <Wire.h>  //for lcd
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define ONE_WIRE_BUS 8
#define TdsSensorPin A1
 
OneWire oneWire(ONE_WIRE_BUS); 
GravityTDS gravityTds;
 
DallasTemperature sensors(&oneWire);
 float tdsValue = 0;
 
void setup()
{
    Serial.begin(115200);
    lcd.begin();
    sensors.begin();
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
}
 
void loop()
{
    sensors.requestTemperatures();
 
    gravityTds.setTemperature(sensors.getTempCByIndex(0));  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    Serial.print("Temperature is: "); 
    Serial.println(sensors.getTempCByIndex(0));
    
    lcd.setCursor(0, 0);
    lcd.print("TDS: ");
    lcd.print(tdsValue,0);
    lcd.print(" PPM");
 
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.print(" C");
    
    delay(1500);
    lcd.clear();

//    if(tdsValue < 900){
//      Serial.println("baik");
//      lcd.setCursor(0,0);
//      lcd.print("baik")
//      delay(1000);
//    }else{
//      Serial.println("tidak baik");
//      lcd.setCursor(0,0);
//      lcd.print("tidak baik")
//      delay(1000);
//    }
}
