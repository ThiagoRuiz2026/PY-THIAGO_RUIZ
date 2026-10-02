#include <Servo.h>

Servo servo1;
Servo servo2;

int botonAvanzar = 2;
int botonRetroceder = 9;

int posicion = 90;

void setup() {

  servo1.attach(A0);
  servo2.attach(A1);

  pinMode(botonAvanzar, INPUT_PULLUP);
  pinMode(botonRetroceder, INPUT_PULLUP);

  servo1.write(posicion);
  servo2.write(posicion);
}

void loop() {

  // AVANZAR
  if (digitalRead(botonAvanzar) == LOW) {

    if (posicion < 180) {

      posicion = posicion + 10;

      servo1.write(posicion);
      servo2.write(posicion);

      delay(200);
    }
  }

  // RETROCEDER
  if (digitalRead(botonRetroceder) == LOW) {

    if (posicion > 0) {

      posicion = posicion - 10;

      servo1.write(posicion);
      servo2.write(posicion);

      delay(200);
    }
  }
}
