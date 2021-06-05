#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

#define SCALE_GAIN 2012722.58
#define I2C_LCD_ADRES 0x27

#define DOUT A1
#define CLK A0

#define NUMERO_DE_MUESTRAS_TARA 20
#define NUMERO_DE_MUESTRAS_PESO 3

#define PIN_TARA 8

HX711 balanza;
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(I2C_LCD_ADRES,16,2);  //
void printWeigth(void);
void setTara(void);
void setScale(void);
void setup() {
  lcd.init();
  lcd.backlight();
  balanza.begin(DOUT, CLK);
  setScale();
  setTara();
  pinMode(PIN_TARA,INPUT_PULLUP);
}

void loop() {
  printWeigth();
  delay(500);
  if(!digitalRead(PIN_TARA)){
      setTara();
  }
}

bool printWeigthOnce=false;
void printWeigth(void){
  static int pesoTemp=0;
  if(!printWeigthOnce){
    printWeigthOnce=!printWeigthOnce;
    lcd.clear();
    //Serial.println("Listo para pesar");  
    lcd.setCursor(0,0);
    lcd.print("Matilanza");
  }
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
 pesoTemp=int(balanza.get_units(NUMERO_DE_MUESTRAS_PESO)*1000);
 lcd.print(pesoTemp);
 lcd.print(" g    ");
 
}

void setTara(void){
  lcd.clear();
  lcd.print("Destarando...");
  balanza.tare(NUMERO_DE_MUESTRAS_TARA);  //El peso actual es considerado Tara.
  printWeigthOnce=false;
  lcd.clear();

}

void setScale(void){
   balanza.set_scale(SCALE_GAIN); // Establecemos la escala
}