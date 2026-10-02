#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

#define PIR_ENTRADA 4
#define PIR_SALIDA 7
#define BUZZER 9
#define FAROL 12
#define FOTORESISTENCIA A1

#define SERVO1 A2
#define SERVO2 A3

#define ANGULO_CERRADO 0
#define ANGULO_ABIERTO 45

#define LIMITE_LUZ 500

Servo puerta1;
Servo puerta2;

Adafruit_LiquidCrystal lcd1(0);

bool puertasAbiertas = false;

#define B4 494
#define Ab4 466
#define A4 440
#define Gb4 415
#define G4 392

const int musicaEntrada[5][2] = {
  {B4, 136},
  {Ab4, 136},
  {A4, 136},
  {Gb4, 136},
  {G4, 136}
};

#define A6 1760
#define Gb6 1661
#define G6 1568
#define Fb6 1480
#define F6 1397

const int musicaSalida[5][2] = {
  {A6, 136},
  {Gb6, 136},
  {G6, 136},
  {Fb6, 136},
  {F6, 136}
};

void reproducirMusica(const int notas[][2], int cantidad)
{
  for (int i = 0; i < cantidad; i++)
  {
    tone(BUZZER, notas[i][0]);
    delay(notas[i][1]);
    noTone(BUZZER);
  }
}

bool detectarMovimiento(int sensor)
{
  return digitalRead(sensor) == HIGH;
}

void abrirPuertas(int angulo)
{
  puerta1.write(angulo);
  puerta2.write(angulo);
}

void cerrarPuertas(int angulo)
{
  puerta1.write(angulo);
  puerta2.write(angulo);
}

void controlarLuz(int sensor, int salida, int limite)
{
  int valor = analogRead(sensor);

  if (valor < limite)
  {
    digitalWrite(salida, HIGH);
  }
  else
  {
    digitalWrite(salida, LOW);
  }
}

void encenderLCD()
{
  lcd1.setBacklight(1);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("BIENVENIDOS");
}

void apagarLCD()
{
  lcd1.clear();
  lcd1.setBacklight(0);
}

void setup()
{
  pinMode(PIR_ENTRADA, INPUT);
  pinMode(PIR_SALIDA, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(FAROL, OUTPUT);

  puerta1.attach(SERVO1);
  puerta2.attach(SERVO2);

  cerrarPuertas(ANGULO_CERRADO);

  digitalWrite(BUZZER, LOW);
  digitalWrite(FAROL, LOW);

  lcd1.begin(16, 2);
  lcd1.clear();
  lcd1.setBacklight(0);

  puertasAbiertas = false;
}

void loop()
{
  controlarLuz(FOTORESISTENCIA, FAROL, LIMITE_LUZ);

  if (!puertasAbiertas && detectarMovimiento(PIR_ENTRADA))
  {
    abrirPuertas(ANGULO_ABIERTO);

    reproducirMusica(musicaEntrada, 5);

    encenderLCD();

    puertasAbiertas = true;

    delay(500);
  }

  if (puertasAbiertas && detectarMovimiento(PIR_SALIDA))
  {
    cerrarPuertas(ANGULO_CERRADO);

    reproducirMusica(musicaSalida, 5);

    apagarLCD();

    puertasAbiertas = false;

    delay(500);
  }
}
