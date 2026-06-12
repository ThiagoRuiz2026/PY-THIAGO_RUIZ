#include <Servo.h>

Servo servo1;
Servo servo2;

const int pinBoton = 3;
const int pinPIR = 4;
const int pinTemp = A2;

int posicion = 90;
unsigned long ultimoCambio = 0;

bool enMovimientoDetectado = false;
unsigned long tiempoMovimiento = 0;

void setup() {
  servo1.attach(A0);
  servo2.attach(A1);

  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(pinPIR, INPUT);

  servo1.write(45);
  servo2.write(45);

  Serial.begin(9600);
}

void loop() {

  // Leer temperatura TMP36
  int lectura = analogRead(pinTemp);
  float voltaje = lectura * 5.0 / 1023.0;
  float temperatura = (voltaje - 0.5) * 100.0;

  bool botonPresionado = digitalRead(pinBoton) == LOW;

  // Si NO está presionado el botón → 45°
  if (!botonPresionado) {
    servo1.write(45);
    servo2.write(45);
    return;
  }

  // Si supera 35°C → congelar posición actual
  if (temperatura > 35.0) {
    return;
  }

  // Si detecta movimiento
  if (digitalRead(pinPIR) == HIGH && !enMovimientoDetectado) {
    servo1.write(0);
    servo2.write(0);

    enMovimientoDetectado = true;
    tiempoMovimiento = millis();
  }

  // Mantener 0° durante 6 segundos
  if (enMovimientoDetectado) {
    if (millis() - tiempoMovimiento < 6000) {
      return;
    } else {
      enMovimientoDetectado = false;
      ultimoCambio = millis();
    }
  }

  // Movimiento normal entre 90° y 180° cada 3 segundos
  if (millis() - ultimoCambio >= 3000) {

    if (posicion == 90) {
      posicion = 180;
    } else {
      posicion = 90;
    }

    servo1.write(posicion);
    servo2.write(posicion);

    ultimoCambio = millis();
  }
}

