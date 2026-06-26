int rojo = 6;
int azul = 5;
int verde = 3;

int potenciometro = A0;

void setup()
{
  Serial.begin(9600);

  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);

  randomSeed(analogRead(A1));
}

void loop()
{
  int lectura = analogRead(potenciometro);
  int porcentaje = map(lectura, 0, 1023, 0, 100);

  // EJERCICIO 1
  if(porcentaje >= 0 && porcentaje < 20)
  {
    int valores[5] = {1,2,3,4,5};
    int valores2[5];

    int largoVector = sizeof(valores)/sizeof(valores[0]);

    for(int x = 0; x < largoVector; x++)
    {
      valores2[x] = valores[x] * 3;

      Serial.println(valores2[x]);

      analogWrite(rojo, valores2[x]);
      analogWrite(verde, valores2[x]);
      analogWrite(azul, valores2[x]);

      delay(1000);

      analogWrite(rojo,0);
      analogWrite(verde,0);
      analogWrite(azul,0);

      delay(1000);
    }
  }

  // EJERCICIO 2
  else if(porcentaje >= 20 && porcentaje < 40)
  {
    int notas[10] = {8,7,6,9,10,5,8,7,6,9};

    int suma = 0;

    int largoVector = sizeof(notas)/sizeof(notas[0]);

    for(int x = 0; x < largoVector; x++)
    {
      suma = suma + notas[x];
    }

    float promedio = suma / 10.0;

    Serial.print("Promedio: ");
    Serial.println(promedio);

    if(promedio >= 1 && promedio <= 5)
    {
      analogWrite(rojo,255);
      analogWrite(verde,0);
      analogWrite(azul,0);
    }
    else if(promedio >= 6 && promedio <= 8)
    {
      analogWrite(rojo,0);
      analogWrite(verde,255);
      analogWrite(azul,0);
    }
    else
    {
      analogWrite(rojo,0);
      analogWrite(verde,255);
      analogWrite(azul,255);
    }

    delay(3000);
  }

  // EJERCICIO 3
  else if(porcentaje >= 40 && porcentaje < 60)
  {
    int numeros[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    int largoVector = sizeof(numeros)/sizeof(numeros[0]);

    for(int x = 0; x < largoVector; x++)
    {
      Serial.println(numeros[x]);

      if(numeros[x] % 2 == 0)
      {
        analogWrite(rojo,0);
        analogWrite(verde,255);
        analogWrite(azul,0);
      }
      else
      {
        analogWrite(rojo,255);
        analogWrite(verde,0);
        analogWrite(azul,0);
      }

      delay(1000);
    }
  }

  // EJERCICIO 4
  else if(porcentaje >= 60 && porcentaje < 80)
  {
    int numeros[30];

    for(int x = 0; x < 30; x++)
    {
      numeros[x] = random(0,256);
    }

    int mayor1 = 0;
    int mayor2 = 0;
    int mayor3 = 0;

    for(int x = 0; x < 30; x++)
    {
      if(numeros[x] > mayor1)
      {
        mayor3 = mayor2;
        mayor2 = mayor1;
        mayor1 = numeros[x];
      }
      else if(numeros[x] > mayor2)
      {
        mayor3 = mayor2;
        mayor2 = numeros[x];
      }
      else if(numeros[x] > mayor3)
      {
        mayor3 = numeros[x];
      }
    }

    Serial.print("Mayor: ");
    Serial.println(mayor1);
    Serial.print("Segundo: ");
    Serial.println(mayor2);
    Serial.print("Tercero: ");
    Serial.println(mayor3);

    analogWrite(rojo, mayor1);
    analogWrite(verde, mayor2);
    analogWrite(azul, mayor3);

    delay(3000);
  }

  // EJERCICIO 5
  else
  {
    int numeros[30];

    for(int x = 0; x < 30; x++)
    {
      numeros[x] = random(0,256);
    }

    int menor1 = 255;
    int menor2 = 255;
    int menor3 = 255;

    for(int x = 0; x < 30; x++)
    {
      if(numeros[x] < menor1)
      {
        menor3 = menor2;
        menor2 = menor1;
        menor1 = numeros[x];
      }
      else if(numeros[x] < menor2)
      {
        menor3 = menor2;
        menor2 = numeros[x];
      }
      else if(numeros[x] < menor3)
      {
        menor3 = numeros[x];
      }
    }

    Serial.print("Menor: ");
    Serial.println(menor1);
    Serial.print("Segundo: ");
    Serial.println(menor2);
    Serial.print("Tercero: ");
    Serial.println(menor3);

    analogWrite(rojo, menor1);
    analogWrite(verde, menor2);
    analogWrite(azul, menor3);

    delay(3000);
  }
}
