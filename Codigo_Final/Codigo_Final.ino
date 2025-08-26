#include <OneWire.h>
#include <Wire.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define pinHumedad A1
#define pinLum 12
#define pinBomba A0
#define pinBuzzer A2
#define sensorH 9
#define sensorL 8
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define buttonRight 3
#define buttonLeft 6
#define buttonEnter 4
#define DHTPin 10
const int antiTime =10;
int stateButton;
int stateButtonAnt;

int reading; 

LiquidCrystal_I2C lcd (0x27,2,1,0,4,5,6,7,3,POSITIVE);
DHT dht(DHTPin,DHTTYPE);

uint8_t second, minute, hour, wday, day, month, year, ctrl;
int buttons[3] = {buttonRight,buttonLeft,buttonEnter};
String plantas[3] = {"1.-Crisantemo","2.-Rosa de alabastro","3.-Petunia"};
float tempMinimas[3] = {10.0,15.0,0.0}; //En grados Celsuis
float tempMaximas[3] = {32.0,27.0,35.0};
int humMinimas[3] = {65,40,40};       //En porcentaje
int humMaximas[3] = {70,50,60};
int inicioFotoperiodo[3] = {7,7,7};
int finFotoperiodo[3] = {18,17,18};
float temp = 0;
int hum = 0;
String tanque = "";
String lum = "";
float tempAnt = 0;
int humAnt = 0;
String tanqueAnt = "";
String lumAnt = "";
uint8_t secondAnt,minuteAnt,hourAnt,dayAnt,wdayAnt,monthAnt,yearAnt;
int menu = 0;
int plantaSelec = 0;
String stringDay = "";
int stateTanque;
int stateRiego = 0;
int stateLuminosidad = 0;  
int modoSilencioso = 0;
int activacionManual = 0;
int desactivacionManual = 0;
int stateTemp = 0;
int stateHum = 0;
void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Wire.begin();
  pinMode(pinBomba,OUTPUT);
  pinMode(sensorL,INPUT);
  pinMode(sensorH,INPUT);
  pinMode(pinLum,OUTPUT);
  pinMode(pinBomba,OUTPUT);
  pinMode(pinBuzzer,OUTPUT);
  digitalWrite(pinBuzzer,LOW);
  digitalWrite(pinLum,HIGH);
  digitalWrite(pinBomba,HIGH);
 
  int i = 0;
  for(i = 0;i < 2;i++){
    pinMode(buttons[i],INPUT);
    }
  lcd.begin(20,4);
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // terminamos con el backlight on
  lcd.setCursor(6,1);
  lcd.print("MACETA");
  lcd.setCursor(4,2);
  lcd.print("INTELIGENTE");
  delay(3000);
  lcd.clear();
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // terminamos con el backlight on

  while(1)
  {
  lcd.setCursor(0,0);
  lcd.print("Seleccionar planta");
  lcd.setCursor(0,1);
  lcd.print(plantas[0]);
  lcd.setCursor(0,2);
  lcd.print(plantas[1]);
  lcd.setCursor(0,3);
  lcd.print(plantas[2]);
  reading = digitalRead(buttonLeft);
  if(reading)
  {
    plantaSelec = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Planta seleccionada: ");
    lcd.setCursor(0,1);
    lcd.print("Crisantemo");
    delay(2000);
    break;
    }
  reading = digitalRead(buttonEnter);
  if(reading)
  {
    plantaSelec = 2;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Planta seleccionada: ");
    lcd.setCursor(0,1);
    lcd.print("Rosa de Alabastro");
    delay(2000);
    break;
    }
  reading = digitalRead(buttonRight);
  if(reading)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Planta seleccionada: ");
    lcd.setCursor(0,1);
    lcd.print("Petunia");
    delay(2000);
    plantaSelec = 3;
    break;
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  adquisicion:
  read_ds1307();
  float temp = dht.readTemperature();
  float hum = analogRead(pinHumedad);
  hum = map(hum,1024,0,0,100);
  if(digitalRead(sensorL) == LOW and digitalRead(sensorH) == LOW)
  {
    tanque = "Vacio";
    stateTanque = 0;
    }
  else if (digitalRead(sensorH) == LOW and digitalRead(sensorL) ==  HIGH)
  {
    tanque = "Con reserva";
    stateTanque = 1;
  }
  else if(digitalRead(sensorH) == HIGH and digitalRead(sensorL) == HIGH) 
  {
    tanque = "Lleno";
    stateTanque = 1;
  }

  if(stateLuminosidad == 1) lum = "ON";
  else lum = "OFF";

  //Alarma de temperatura
  if(temp < tempMinimas[plantaSelec - 1] and stateTemp == 0)
  {
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("Ayuda!!");
    lcd.setCursor(2,2);
    lcd.print("Hace mucho frio");
    if(modoSilencioso == 0){
      while(1){    
        digitalWrite(pinBuzzer,HIGH);
        delay(1000);
        digitalWrite(pinBuzzer,LOW);
        reading = digitalRead(buttonEnter);
        if(reading){
          stateTemp = 1;
          break;
          }
        }
      }
    }
  else if(temp > tempMaximas[plantaSelec -1] and stateTemp == 0)
  {
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("Uff!!");
    lcd.setCursor(2,2);
    lcd.print("Que calor hace");
    if(modoSilencioso == 0){
      while(1){
        digitalWrite(pinBuzzer,HIGH);
        delay(1000);
        digitalWrite(pinBuzzer,LOW);
        reading = digitalRead(buttonEnter);
        if(reading)
        {
          stateTemp = 1;
          break;
          }
      }
    }
  }
  else if(hum < humMinimas[plantaSelec -1] and stateHum == 0)
  {
    lcd.clear();
    lcd.setCursor(2,2);
    lcd.print("Me estoy secando :(");
    if(modoSilencioso == 0){
        digitalWrite(pinBuzzer,HIGH);
        delay(1000);
        digitalWrite(pinBuzzer,LOW);
    }
    if(stateRiego == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Regando....");
      delay(1000);
      lcd.noBacklight();
      delay(1000);
      digitalWrite(pinBomba,LOW);
      delay(1000);
      digitalWrite(pinBomba,HIGH);
      delay(1000);
      lcd.backlight();
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Riego terminado");
      stateRiego = 1;
      delay(2000);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llenar Tanque!!!");
      if(modoSilencioso == 0){
        digitalWrite(pinBuzzer,HIGH);
        delay(1000);
        digitalWrite(pinBuzzer,LOW);}
      goto adquisicion;
      }
      stateHum = 1;
  }
  else if(hum > humMaximas[plantaSelec-1] and stateHum == 0)
  {
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("Socorro");
    lcd.setCursor(4,2);
    lcd.print("Me ahogo!!!");
    if(modoSilencioso == 0){
    while(1){
      digitalWrite(pinBuzzer,HIGH);
      delay(1000);
      digitalWrite(pinBuzzer,LOW);
      reading = digitalRead(buttonEnter);
      if(reading){
        stateHum = 1;
        break;
        }
    }
  }
}
  if(hour >= inicioFotoperiodo[plantaSelec-1] and hour <= finFotoperiodo[plantaSelec -1] and desactivacionManual == 0)
  {
    digitalWrite(pinLum,LOW);
    stateLuminosidad = 1;
    }
  else{
    if(hour < inicioFotoperiodo[plantaSelec-1] and hour > finFotoperiodo[plantaSelec -1]) desactivacionManual = 0;
    if(activacionManual == 1 and desactivacionManual == 0){
      digitalWrite(pinLum,LOW);
      stateLuminosidad = 1;}
    else{
      digitalWrite(pinLum,HIGH);
      stateLuminosidad = 0;
      }
    }
    
  if(minute == 0 or minute == 15 or minute == 30 or minute == 45 and second == 0){
    stateTemp = 0;
    stateHum = 0;
    stateRiego = 0;
    }
  
  stateButton = digitalRead(buttonRight);
  
  if(stateButton != stateButtonAnt)
  {
    if(antireboot(buttonRight))
    {
      lcd.clear();
      if(menu < 5) menu++;
      else menu = 5;
      }
    }
  stateButton = digitalRead(buttonLeft);
  
  if(stateButton != stateButtonAnt)
  {
    if(antireboot(buttonLeft))
    {
      lcd.clear();
      if(menu > 0) menu--;
      else menu = 0;
      }
    }
  
  switch(menu){
    case 0:
      if(secondAnt != second) lcd.clear();
      if(minuteAnt != minute) lcd.clear();
      if(hourAnt != hour) lcd.clear();
      if(wdayAnt != wday) lcd.clear();
      if(dayAnt != day) lcd.clear();
      if(monthAnt != month) lcd.clear();
      if(yearAnt != year) lcd.clear();
      switch(wday)
      {
        case 1:
          stringDay = "Lunes";
          break;
        case 2:
          stringDay = "Martes";
          break;
        case 3:
          stringDay = "Miercoles";
          break;
        case 4:
          stringDay = "Jueves";
          break;
        case 5:
          stringDay = "Viernes";
          break;
        case 6:
          stringDay = "Sábado";
          break;
        case 7:
          stringDay = "Domingo";
          break;
        }
      lcd.setCursor(4,0);
      lcd.print(stringDay);
      lcd.setCursor(3,1);
      lcd.print("Fecha: ");
      lcd.print(day);
      lcd.print('/');
      lcd.print(month);
      lcd.print('/');
      lcd.print(year);
      lcd.setCursor(1,2);
      lcd.print("  Hora: ");
      lcd.print(hour);
      lcd.print(':');
      lcd.print(minute);
      lcd.print(':');
      lcd.print(second);
      break;
    case 1:
      if(temp != tempAnt) lcd.clear();
      if(hum != humAnt) lcd.clear();
      if(tanque != tanqueAnt) lcd.clear();
      if(lum != lumAnt) lcd.clear(); 
      
      lcd.setCursor(0,0);
      lcd.print("Temperatura: ");lcd.print(temp);
      lcd.setCursor(0,1);
      lcd.print("Humedad. ");lcd.print(hum);
      lcd.setCursor(0,2);
      lcd.print("Tanque: ");lcd.print(tanque);
      lcd.setCursor(0,3);
      lcd.print("Luminosidad:");lcd.print(lum);
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Temp Min: ");lcd.print(tempMinimas[plantaSelec-1]);lcd.write(167);
      lcd.setCursor(0,1);
      lcd.print("Temp Max: ");lcd.print(tempMaximas[plantaSelec-1]);lcd.write(167);
      lcd.setCursor(0,2);
      lcd.print("Humedad Min: ");lcd.print(humMinimas[plantaSelec-1]);lcd.print("%");
      lcd.setCursor(0,3);
      lcd.print("Humedad Max: ");lcd.print(humMaximas[plantaSelec-1]);lcd.print("%");
      break;
    case 3:
      if(plantaSelec == 1)
      {
        lcd.setCursor(0,0);
        lcd.print("Sustrato:");
        lcd.setCursor(0,1);
        lcd.print("2/3 tierra jardin");
        lcd.setCursor(0,2);
        lcd.print("1/3 composta");
        }
      if(plantaSelec == 2)
      {
        lcd.setCursor(0,0);
        lcd.print("Sustrato:");
        lcd.setCursor(0,1);
        lcd.print("25% tierra hoja");
        lcd.setCursor(0,2);
        lcd.print("25% tierra negra");
        lcd.setCursor(0,3);
        lcd.print("50% tepojal");
        }
      if(plantaSelec == 3)
      {
        lcd.setCursor(0,0);
        lcd.print("Sustrato:");
        lcd.setCursor(0,1);
        lcd.print("60% tierra hoja");
        lcd.setCursor(0,2);
        lcd.print("20% Peat Moss");
        lcd.setCursor(0,3);
        lcd.print("20% tepojal");
        }
      break;
    case 4:
      lcd.setCursor(0,0);
      if(stateLuminosidad == 0){
        lcd.print("Luminosidad: OFF");
        lcd.setCursor(0,1);
        lcd.print("Desea encender?");
        stateButton = digitalRead(buttonEnter);
        if(stateButton != stateButtonAnt)
        {
          if(antireboot(buttonEnter))
            {
              activacionManual = 1;
              desactivacionManual = 0;
              stateLuminosidad = 1;
              digitalWrite(pinLum,LOW);
              lcd.clear();
              lcd.print("Luz activada");
              delay(2000);
              menu = 0;
            }
        }
      }
      else{
        lcd.print("Luminosidad: ON");
        lcd.setCursor(0,1);
        lcd.print("Desea apagar?");
        stateButton = digitalRead(buttonEnter);
        if(stateButton != stateButtonAnt)
        {
          if(antireboot(buttonEnter))
            {
              activacionManual = 0;
              desactivacionManual = 1;
              stateLuminosidad = 0;
              digitalWrite(pinLum,HIGH);
              lcd.clear();
              lcd.print("Luz Desactivada");
              delay(2000);
              menu = 0;
            }
        }
        }
        break;
     case 5:
      lcd.setCursor(0,0);
      if(modoSilencioso == 0){
        lcd.print("Silecio: OFF");
        lcd.setCursor(0,1);
        lcd.print("Desea silenciar?");
        stateButton = digitalRead(buttonEnter);
        if(stateButton != stateButtonAnt)
        {
          if(antireboot(buttonEnter))
            {
              modoSilencioso = 1;
              lcd.clear();
              lcd.print("Silecio Activado");
              delay(2000);
              menu = 0;
            }
        }
      
     }
     else{
        lcd.print("Silecio: OFF");
        lcd.setCursor(0,1);
        lcd.print("Desea desactivar?");
        stateButton = digitalRead(buttonEnter);
        if(stateButton != stateButtonAnt)
        {
          if(antireboot(buttonEnter))
            {
              modoSilencioso = 0;
              lcd.clear();
              lcd.print("Silecio Desctivado");
              delay(2000);
              menu = 0;
            }
        }
  }
    break;
}
  tempAnt = temp;
  humAnt = hum;
  tanqueAnt = tanque;
  lumAnt = lum;
  secondAnt = second;
  minuteAnt = minute;
  hourAnt = hour;
  wdayAnt = wday;
  dayAnt = day;
  monthAnt = month;
  yearAnt = year;

}
bool read_ds1307()
{
  // Iniciar el intercambio de información con el DS1307 (0xD0)
  Wire.beginTransmission(0x68);

  // Escribir la dirección del segundero
  Wire.write(0x00);

  // Terminamos la escritura y verificamos si el DS1307 respondio
  // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  if (Wire.endTransmission() != 0)
    return false;

  // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  Wire.requestFrom(0x68, 8);

  // Recibimos el byte del registro 0x00 y lo convertimos a binario
  second = bcd2bin(Wire.read());
  minute = bcd2bin(Wire.read()); // Continuamos recibiendo cada uno de los registros
  hour = bcd2bin(Wire.read());
  wday = bcd2bin(Wire.read());
  day = bcd2bin(Wire.read());
  month = bcd2bin(Wire.read());
  year = bcd2bin(Wire.read());

  // Recibir los datos del registro de control en la dirección 0x07
  ctrl = Wire.read();

  // Operacion satisfactoria, retornamos verdadero
  return true;
}

/**
   Esta función convierte un número BCD a binario. Al dividir el número guardado
   en el parametro BCD entre 16 y multiplicar por 10 se convierten las decenas
   y al obtener el módulo 16 obtenemos las unidades. Ambas cantidades se suman
   para obtener el valor binario.
*/
uint8_t bcd2bin(uint8_t bcd)
{
  // Convertir decenas y luego unidades a un numero binario
  return (bcd / 16 * 10) + (bcd % 16);
}

boolean antireboot  (int pin) {
  int  cont =0;
  boolean state;            // guarda el estado del boton 
  boolean stateAnt;    // guarda el ultimo estado del boton 

  do {
    state = digitalRead (pin);
    if (state != stateAnt){  // comparamos el estado actual 
      cont = 0;                   // reiniciamos el contador 
      stateAnt = state;
    }
    else{
      cont += 1;      // aumentamos el contador en 1
    }
    delay (1);
  }
  while (cont < antiTime);
  return state;
}
