/*  MASTER  */

#include <Wire.h>

#define boton A1
#define poten A0

byte device[3]; //tenemos solo 3 dispositivos
int valor;

void setup() {
  
  pinMode(boton, INPUT); //boton
  pinMode(poten, INPUT); //potenciometro
  
  Serial.begin(9600);
  Serial.println ("Escaneando dispositivos I2C: ");
  byte count = 0; //numero de dispositivos encontrados
 
  Wire.begin();
  for(byte i = 1; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Encontrado dispositivo en la direccion: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      if(i<16) Serial.print("0");
      Serial.print(i, HEX);
      Serial.println(")");
      delay (1);
      device[count] = i; //añade todos los dispositibos encontrados para su posterior uso en un array
      count++;
    } 
  }
  Serial.print ("Encontrados ");
  Serial.print (count, DEC);
  Serial.println (" dispositivo(s).");
}

void SeleccionarValorPoten(){ //obtiene el valor del potenciometro al pulsar el boton
  if(!digitalRead(boton)){ //si el boto ha sido pulsado
    valor = analogRead(poten); //recojge el valor del potenciomentro
    valor = map(valor, 0, 1023, 0, 255); //lo mapea de 0 a 255
  }
}

void loop() {
  
  SeleccionarValorPoten(); //obtiene valor del potenciometro mapeado
  
  for(int i =0; i<sizeof(device); i++){ //manda a todos los dispostivios el valor del potenciometro
  	Wire.beginTransmission(device[i]); //se conecta al dispositivo
  	Wire.write(valor); //lo manda
  	Wire.endTransmission(); //se desconecta
  }
  
  
}