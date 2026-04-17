// LED 1
int R1 = 3;
int G1 = 9;

// LED 2
int R2 = 2;
int G2 = 10;
int B2 = 4;

// LED 3
int R3 = 11;
int G3 = 5;
int B3 = 6;

void setup() {
  pinMode(R1, OUTPUT); pinMode(G1, OUTPUT);
  pinMode(R2, OUTPUT); pinMode(G2, OUTPUT); pinMode(B2, OUTPUT);
  pinMode(R3, OUTPUT); pinMode(G3, OUTPUT); pinMode(B3, OUTPUT);
}

void apagarTodo() {
  analogWrite(R1, 0); analogWrite(G1, 0);

  digitalWrite(R2, LOW); digitalWrite(G2, LOW); digitalWrite(B2, LOW);

  analogWrite(R3, 0); analogWrite(G3, 0); analogWrite(B3, 0);
}

//  NARANJA 
void parpadeoNaranja() {
  for(int i = 0; i < 4; i++) {

    // LED 1
    analogWrite(R1, 255);
    analogWrite(G1, 120);

    // LED 2
    digitalWrite(R2, HIGH);
    digitalWrite(G2, HIGH);

    // LED 3
    analogWrite(R3, 255);
    analogWrite(G3, 120);

    delay(100);

    apagarTodo();
    delay(100);
  }
}

void loop() {

  //  LED 1
  analogWrite(R1, 255);
  delay(1000);
  apagarTodo();
  delay(200);

  parpadeoNaranja();

  //  LED 2 (magenta)
  digitalWrite(R2, HIGH);
  digitalWrite(B2, HIGH);
  delay(1000);
  apagarTodo();
  delay(200);

  parpadeoNaranja();

  //  LED 3 (cian tenue)
  analogWrite(G3, 25);
  analogWrite(B3, 25);
  delay(1000);
  apagarTodo();
  delay(200);

  parpadeoNaranja();
}
