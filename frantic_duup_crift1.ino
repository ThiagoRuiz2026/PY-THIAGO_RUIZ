#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

#define Gb3 208
#define C4 262
#define F3 175
#define A3 220

const int midi1[10][3] = {
  {Gb3, 115, 0},
  {C4, 115, 0},
  {Gb3, 115, 0},
  {F3, 115, 0},
  {A3, 115, 115},
  {Gb3, 115, 0},
  {C4, 115, 0},
  {Gb3, 115, 0},
  {F3, 115, 0},
  {A3, 115, 0},
};

void playMidi(int pin, const int notes[][3], size_t len) {
  for (int i = 0; i < len; i++) {
    tone(pin, notes[i][0]);
    delay(notes[i][1]);
    noTone(pin);
    delay(notes[i][2]);
  }
}

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pir = 2;
int servoPin = 3;
int buzzer = 4;

int rojo = 5;
int verde = 6;
int azul = 7;

int potenciometro = A0;
int sensorTemperatura = A1;

int valorPot;
int temperatura;
int repeticiones;

bool iniciado = false;

void setup() {

  pinMode(pir, INPUT);

  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);

  pinMode(buzzer, OUTPUT);

  servo.attach(servoPin);
  servo.write(0);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Mover potenciometro");

  valorPot = analogRead(potenciometro);
}

void loop() {

  if (iniciado == false) {

    int nuevoValor = analogRead(potenciometro);

    if (abs(nuevoValor - valorPot) > 20) {
      iniciado = true;
      lcd.clear();
    }

    return;
  }

  int lectura = analogRead(sensorTemperatura);
  temperatura = lectura * 5.0 / 1023.0 * 100;

  if (temperatura > 40) {
    digitalWrite(rojo, HIGH);
    digitalWrite(verde, LOW);
    digitalWrite(azul, LOW);
  } else {
    digitalWrite(rojo, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(azul, HIGH);
  }

  if (digitalRead(pir) == HIGH) {

    valorPot = analogRead(potenciometro);

    if (valorPot < 102) {
      repeticiones = 8;
    }
    else if (valorPot < 716) {
      repeticiones = 2;
    }
    else {
      repeticiones = 5;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo moviendose");

    for (int i = 0; i < repeticiones; i++) {

      servo.write(90);
      delay(500);

      servo.write(0);
      delay(500);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Melodia");

    digitalWrite(rojo, LOW);
    digitalWrite(verde, HIGH);
    digitalWrite(azul, LOW);

    playMidi(buzzer, midi1, ARRAY_LEN(midi1));

    lectura = analogRead(sensorTemperatura);
    temperatura = lectura * 5.0 / 1023.0 * 100;

    if (temperatura > 40) {

      digitalWrite(rojo, HIGH);
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);

      lcd.clear();
      lcd.print("Rojo");
    }
    else {

      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(azul, HIGH);

      lcd.clear();
      lcd.print("Azul");
    }

    delay(1000);
  }
}
