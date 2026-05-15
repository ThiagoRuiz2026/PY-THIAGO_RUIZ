

int pir = 2;

int rojo = 6;
int verde = 5;
int azul = 3;

int buzzer = 7;

void setup()
{
  pinMode(pir, INPUT);

  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int movimiento = digitalRead(pir);

  // SIN MOVIMIENTO
  if(movimiento == LOW)
  {
    // VERDE
    analogWrite(rojo, 0);
    analogWrite(verde, 255);
    analogWrite(azul, 0);

    noTone(buzzer);

    Serial.println("Area segura");
  }

  // CON MOVIMIENTO
  else
  {
    // ROJO
    analogWrite(rojo, 255);
    analogWrite(verde, 0);
    analogWrite(azul, 0);

    tone(buzzer, 1000);

    Serial.println("Movimiento detectado");
  }

  delay(200);
}
