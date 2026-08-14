
// TP9 - Arduino UNO + Buzzer + 3 botones
// Buzzer en pin ~9
// Botones en pines 2, 3 y 4

const int buzzer = 9;
const int boton1 = 2;
const int boton2 = 3;
const int boton3 = 4;

// ===== Notas =====
#define Gb4 415
#define Fb4 370
#define D4 294
#define F4 349
#define Cb4 277
#define A3 220
#define C4 262
#define Ab3 233
#define A4 440
#define G4 392
#define Db4 311

#define E3 165
#define B3 247
#define F3 175
#define G3 196

#define A6 1760
#define E6 1319
#define Cb6 1109
#define Gb5 831
#define Fb5 740
#define A5 880
#define B5 988
#define G6 1568
#define C6 1047
#define G5 784

// ===== Melodia 1 =====
const int melodia1[][3] = {
  {Gb4,136,0},
  {Fb4,136,136},
  {D4,136,273},
  {F4,136,0},
  {Cb4,136,0},
  {Fb4,136,0},
  {A3,136,409},
  {C4,136,0},
  {Gb4,136,136},
  {Ab3,136,273},
  {A4,136,273},
  {Gb4,136,136},
  {G4,136,0},
  {F4,136,0},
  {Db4,136,0}
};

const int tam1 = sizeof(melodia1) / sizeof(melodia1[0]);

// ===== Melodia 2 =====
const int melodia2[][3] = {
  {Ab3,136,273},
  {C4,136,273},
  {A3,136,0},
  {E3,136,136},
  {F4,136,273},
  {B3,136,136},
  {E3,136,136},
  {Db4,136,0},
  {F3,136,136},
  {G3,136,273},
  {Fb4,136,0},
  {G3,136,273},
  {Cb4,136,0},
  {G3,136,0},
  {F4,136,0}
};

const int tam2 = sizeof(melodia2) / sizeof(melodia2[0]);

// ===== Melodia 3 =====
const int melodia3[][3] = {
  {A6,136,0},
  {E6,136,0},
  {Cb6,136,0},
  {Gb5,136,136},
  {Fb5,136,0},
  {A5,136,0},
  {B5,136,136},
  {Cb6,136,0},
  {G6,136,0},
  {C6,136,136},
  {Fb5,136,0},
  {Cb6,136,136},
  {A5,136,0},
  {E6,136,0},
  {G5,136,0},
  {Cb6,136,0}
};

const int tam3 = sizeof(melodia3) / sizeof(melodia3[0]);

// ===== Funcion para reproducir =====
void reproducir(const int notas[][3], int cantidad) {
  for (int i = 0; i < cantidad; i++) {
    tone(buzzer, notas[i][0]);
    delay(notas[i][1]);
    noTone(buzzer);
    delay(notas[i][2]);
  }
}

// Estados anteriores de los botones
bool estadoAnt1 = HIGH;
bool estadoAnt2 = HIGH;
bool estadoAnt3 = HIGH;

void setup() {
  pinMode(buzzer, OUTPUT);

  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);

  noTone(buzzer);
}

void loop() {

  bool estado1 = digitalRead(boton1);
  bool estado2 = digitalRead(boton2);
  bool estado3 = digitalRead(boton3);

  // Boton 1
  if (estadoAnt1 == HIGH && estado1 == LOW) {
    reproducir(melodia1, tam1);
  }

  // Boton 2
  if (estadoAnt2 == HIGH && estado2 == LOW) {
    reproducir(melodia2, tam2);
  }

  // Boton 3
  if (estadoAnt3 == HIGH && estado3 == LOW) {
    reproducir(melodia3, tam3);
  }

  // Guardar estados
  estadoAnt1 = estado1;
  estadoAnt2 = estado2;
  estadoAnt3 = estado3;

  delay(20);
}
