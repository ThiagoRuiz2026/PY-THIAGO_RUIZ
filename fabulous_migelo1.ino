#define LR 11 
#define LA 10
#define LV 9

void setup()
{
  pinMode(LR, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(LV, OUTPUT);
}

void loop()
{
  	for(int v = 0; v <= 255; v += 100)
  	{
      analogWrite(LV, v);

    	for(int a = 0; a <= 255; a += 100)
    	{
          analogWrite(LA, a);

      		for(int r = 0; r <= 255; r += 100)
  	  		{	
        		analogWrite(LR, r);
        		delay(300); 
            }
    	}	
  	}
}