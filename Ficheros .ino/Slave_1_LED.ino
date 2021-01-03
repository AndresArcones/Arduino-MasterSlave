/* SLAVE_1 */

//a binario

#include <Wire.h>

#define clockPin 6
#define dataPin 4
#define latchPin 5

int orden = LSBFIRST; //orden de escritura en el registro del binario
byte dato = B00000000; //binario a mostrar en los leds

void setup() {
  Wire.begin(40); //seteamos el id del esclavo
  //esperamos un evento del maestro y lanzamos la funcion receiveEvent()
  Serial.begin(9600);
  
  writeReg();//escribimos todos los leds a 0
}

void loop() {
   Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany){ //recibe los datos del maestro
  int x = Wire.read();//recojemos el valor del maestro
  Serial.println(x); //lo muestra por serial
  decimalBinario(x); //lo pasa a binario
  writeReg(); //lo escribe en el registro
  
}

void writeReg(){ //funcion que escribe en el registro los datos y da la orden de sacarlos
  digitalWrite(latchPin,0); //el registro no hace nada
  shiftOut(dataPin, clockPin, orden, dato); //cargamos el registro
  digitalWrite(latchPin,1); //abrimos compuertas del registro para mostrar los datos por las salidas
}

void decimalBinario(int decimal){ //convierte decimal a binario de 8 bits
  int i = 0;
  while(i<=8){ //8 bits
    if(decimal%2 == 1){ //si devuelve uno
      bitSet(dato,i); //cambiamos ese bit a 1
    }else bitClear(dato,i); //si no lo cambiamos a 0
    i++; //nos movemos en los bits
    decimal = decimal/2; //actualizamos valor de decimal
  }
  if(decimal == 1)bitSet(dato,i); //si decimal tiene resto 1, asignamos el bit de mayor peso a 1
  
}
