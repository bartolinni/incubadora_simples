#include "DHT.h"
#define DHTPIN 2     // Pino digital sensor DHT

# define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definir o endereço do LCD para 0x27 para um display de 16 caracteres e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx teste!"));

  dht.begin();

  lcd.begin();

  pinMode(6, OUTPUT);
  analogWrite(6, 0);
}

void loop() {
  // Aguarde alguns segundos entre as medições.

  // delay(3000);

  // A leitura da temperatura ou umidade leva cerca de 250 milissegundos!
  // O sensor pode ter um atraso de até 2 segundos para a leitura
  
  float h = dht.readHumidity();
  // Temperature em Celsius (default)
  float t = dht.readTemperature();
  // Temperature em Fahrenheit (Fahrenheit = true)
  float f = dht.readTemperature(true);

  // Verifique se alguma leitura falhou e tenta novamente.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.print(F("Falha de leitura do sensor DHT!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setBacklight(HIGH);

  lcd.setCursor(0, 0);
  lcd.print(F("T = "));
  lcd.setCursor(4, 0);
  lcd.print(round(t));
  lcd.setCursor(7, 0);
  lcd.write(223);
  lcd.setCursor(8, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(F("H = "));
  lcd.setCursor(4, 1);
  lcd.print(round(h));
  lcd.setCursor(7, 1);
  lcd.print("%");

  if (t >= 27) {
    analogWrite(6, 3);
    delay(100);
    analogWrite(6, 0);
    delay(100);
    analogWrite(6, 3);
    delay(100);
    analogWrite(6, 0);
    delay(100);
    analogWrite(6, 3);
    delay(100);
    analogWrite(6, 0);
    
  }

  delay(2000);
  
}
