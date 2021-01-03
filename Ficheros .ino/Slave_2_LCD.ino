
/* SLAVE_2 */

//lcd

#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int valorDecimal = 0;
byte dato = B00000000;


void setup() {
  Wire.begin(50); //seteamos el id del esclavo
  Wire.onReceive(receiveEvent); //esperamos un evento del maestro y lanzamos la funcion receiveEvent()
  
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void receiveEvent(int howMany){
  valorDecimal = Wire.read();//recojemos el valor del maestro
  Serial.println(valorDecimal);//lo pintamos
  
}

void pintarLcdNombre(String texto){ //pintamos el nombre del proceso de cambio de base
  lcd.setCursor(0,0);
  lcd.print(texto);  
}
void pintarLcdValor(int valor, String base){ //mostramos el valor en su base, 
  											//dependiendo de la base que se elija por paramtro
  lcd.setCursor(0,1);
  if(base.equals("DEC"))
  	lcd.print(valor,DEC);
  else if(base.equals("HEX"))
    lcd.print(valor,HEX);
  else if(base.equals("OCT"))
    lcd.print(valor,OCT);
  else if(base.equals("BIN"))
    lcd.print(valor,BIN);
}

void pintarLcd(String fila1, int fila2, String base){
  pintarLcdNombre(fila1); //pintamos el nombre
  pintarLcdValor(fila2,base); //pintamos el valor
  delay(100); //seria delay(1000) para un segundo, pero la simulacion de tinkercad es muy lenta
  lcd.clear();
  
}

void loop() {
  
  pintarLcd("Decimal", valorDecimal,"DEC"); //pintamos decimal
  pintarLcd("Hexadecimal", valorDecimal,"HEX");//pintamos hexadecimal
  pintarLcd("Octal", valorDecimal,"OCT"); //pintamos octal
  pintarLcd("Binario", valorDecimal, "BIN"); //pintamos binario
}
 