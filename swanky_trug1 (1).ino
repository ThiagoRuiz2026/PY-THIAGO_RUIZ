#define R 3
#define A 5
#define V 6

int valorluz;
int valortemp;
int realvalorluz;

float voltaje;
float celsius;

void setup()
{
  Serial.begin(9600);

  pinMode(R, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(V, OUTPUT);
}

void loop()
{
  valorluz = analogRead(A1);
  valortemp = analogRead(A0);

  realvalorluz = map(valorluz, 0, 1023, 0, 100);

  voltaje = valortemp * (5.0 / 1023.0);
  celsius = (voltaje - 0.5) * 100;

  Serial.print("El nivel de luz actual es: ");
  Serial.println(realvalorluz);

  Serial.print("Y la temperatura actual es: ");
  Serial.println(celsius);

  if (realvalorluz > 30 && realvalorluz < 70)
  {
    if (celsius > 30)
    {
      analogWrite(R, 255);
    }
    else if (celsius <= 18)
    {
      analogWrite(A, 255);
    }
    else
    {
      analogWrite(V, 255);
    }
  }

  delay(1000);

  analogWrite(R, 0);
  analogWrite(A, 0);
  analogWrite(V, 0);
}
