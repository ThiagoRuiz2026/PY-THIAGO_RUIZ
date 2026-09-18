

#include <Servo.h>
#include <LiquidCrystal.h>


const int boton = 2;

const int ledRojo = 3;
const int ledVerde = 4;
const int ledAzul = 5;

const int buzzer = 8;
const int servoPin = 9;

const int sensorTemperatura = A0;
const int potenciometro = A1;

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 7, 6, A2, A3);

Servo servo;


#define Gb3 208
#define C4 262
#define F3 175
#define A3 220

const int melodia[10][3] = {
  {Gb3, 115, 0},
  {C4,  115, 0},
  {Gb3, 115, 0},
  {F3,  115, 0},
  {A3,  115, 115},
  {Gb3, 115, 0},
  {C4,  115, 0},
  {Gb3, 115, 0},
  {F3,  115, 0},
  {A3,  115, 0}
};


void controlarTemperatura() {

  int lectura = analogRead(sensorTemperatura);

  float voltaje = lectura * 5.0 / 1023.0;

  float temperatura = (voltaje - 0.5) * 100.0;

  if (temperatura > 40) {

    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAzul, LOW);

  } else {

    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAzul, HIGH);
  }
}


void tocarMelodia() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Melodia");

  digitalWrite(ledVerde, HIGH);

  for (int i = 0; i < 10; i++) {

    tone(buzzer, melodia[i][0]);

    delay(melodia[i][1]);

    noTone(buzzer);

    delay(melodia[i][2]);
  }

  digitalWrite(ledVerde, LOW);
}


void setup() {

  pinMode(boton, INPUT_PULLUP);

  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  pinMode(buzzer, OUTPUT);

  servo.attach(servoPin);

  servo.write(0);

  lcd.begin(16, 2);

  lcd.clear();

  controlarTemperatura();
}


void loop() {

  controlarTemperatura();

  if (digitalRead(boton) == LOW) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo moviendose");

    // Leer el potenciometro
    int valorPot = analogRead(potenciometro);

    int tiempoEspera;

    // Menos del 25%
    if (valorPot < 256) {

      tiempoEspera = 2000;
    }

    // Entre 25% y 50%
    else if (valorPot <= 512) {

      tiempoEspera = 5000;
    }

    // Más del 50%
    else {

      tiempoEspera = 8000;
    }


    for (int i = 0; i < 10; i++) {

      servo.write(90);
      delay(tiempoEspera);

      controlarTemperatura();

      servo.write(0);
      delay(tiempoEspera);

      controlarTemperatura();
    }


    tocarMelodia();

    controlarTemperatura();

    lcd.clear();

    // Esperar a que se suelte el botón
    while (digitalRead(boton) == LOW) {
      delay(10);
    }
  }
}