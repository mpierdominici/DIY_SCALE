#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

const int DOUT=A1;
const int CLK=A0;

HX711 balanza;
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

void setup() {
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  //lcd.print("Hola Mundo");


  // Serial.begin(9600);
  balanza.begin(DOUT, CLK);
  //Serial.print("Lectura del valor del ADC:  ");
  //Serial.println(balanza.read());
  //Serial.println("No ponga ningun  objeto sobre la balanza");
  lcd.print("Destarando...");
  //Serial.println("...");
  balanza.set_scale(2012722.58); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
  lcd.clear();
  //Serial.println("Listo para pesar");  

  
}
int pesoTemp=0;
void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("Matilanza");
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(pesoTemp);
  lcd.print(" g");
  delay(100);
  pesoTemp=int(balanza.get_units(20)*1000);
  lcd.clear();
  //Serial.print("Peso: ");
  //Serial.print(balanza.get_units(20),3);
  //Serial.println(" kg");
  //delay(500);

  
}
