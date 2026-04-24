
const int boton = 2;

const int pinRojo = 9;
const int pinVerde = 10;
const int pinAzul = 11;

const int potRojo = A0;
const int potVerde = A1;
const int potAzul = A2;

bool activo = false;

void setup() {
  pinMode(boton, INPUT_PULLUP);

  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);

  Serial.begin(9600);
}

void loop() {

 
  if (digitalRead(boton) == LOW && !activo) {
    activo = true;

    Serial.println ("tenes 10 segundo para configurar el led");

    delay(10000);

 
    int r = analogRead(potRojo);
    int g = analogRead(potVerde);
    int b = analogRead(potAzul);

   
    r = map(r, 0, 1023, 0, 255);
    g = map(g, 0, 1023, 0, 255);
    b = map(b, 0, 1023, 0, 255);

   
    analogWrite(pinRojo, r);
    analogWrite(pinVerde, g);
    analogWrite(pinAzul, b);

    Serial.print("RGB: ");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.println(b);

  delay(10000);
  delay(0);
   
    analogWrite(pinRojo, 0);
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 0);

    activo = false;
  }
}
