#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN A1 // pino ligado ao sensor DHT
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int pinFan = 14;//define o pino onde esta ligado o Fan

// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin(20,4);// configura o display lcd
 lcd.setBacklight(HIGH);// Ativa a luz do display lcd
 Serial.begin(9600);
 dht.begin();//Inicia o sensor de temperatura
 pinMode(pinFan, OUTPUT);//configura o pino do fan
}
 
void loop()
{
  float h = dht.readHumidity();// Lê a umidade relativa do ar através sensor
  float t = dht.readTemperature();// Lê a temperatura através do sensor

  if(t>30){
    digitalWrite(pinFan, HIGH);// Liga o Fan
  }else{
    digitalWrite(pinFan, LOW);// Desliga o Fan
  }

  // Exibe no display as informações
  if (isnan(t) || isnan(h)){
    lcd.clear();
    lcd.print("Falha ao ler o sensor DHT");
  }else{
    lcd.setCursor(0,0);
    lcd.print("Temperatura:");
    lcd.setCursor(0,1);
    lcd.print(t);
    lcd.print(" *C");
    lcd.setCursor(0,2);
    lcd.print("Umidade:");
    lcd.setCursor(0,3);
    lcd.print(h);
    lcd.print(" %");
  }
  delay(1000); 
}
