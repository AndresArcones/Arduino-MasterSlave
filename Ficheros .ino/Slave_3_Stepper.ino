/* SLAVE_3 */

//step motor -> L293D + Stepper

#include <Wire.h>
#include <Stepper.h>

const int steps = 200;
Stepper motor(steps, 8, 9, 10, 11); //creamos el objeto stepper para nuestro motor


void setup() {
  Wire.begin(60); //seteamos el id del esclavo
  Wire.onReceive(receiveEvent); //esperamos un evento del maestro y lanzamos la funcion receiveEvent()
  Serial.begin(9600);
}

void loop() {
  
  motor.step(30); //se mueve de por vida, porque esta en un loop (pongo 30 por poner algo)
  
  
  
}

void receiveEvent(int howMany){
  int velocidad = Wire.read(); //recojemos el valor del maestro
  Serial.println(velocidad); //lo pintamos
  motor.setSpeed(velocidad); //cambiamos la velocidad del motor
  
}
  
