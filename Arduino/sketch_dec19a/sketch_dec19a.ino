int foo = 0;

void setup()
{
  attachInterrupt(0 , HTSPB, RISING);
  Serial.begin(9600);
}

void loop()
{
  Serial.println("new");
  Serial.println(foo);
  Serial.println(analogRead(2));
}

void HTSPB()
{
   if(foo == 0)
    {
     foo = 1;
   }
   else
   {
     foo = 0;
   }
}
