int datapin = 5; 
int clockpin = 4;
int latchpin = 3;

int address = 1;
byte data = 0;
boolean cmd = false;
boolean sendByte = false;

void HTSPB()
{
   if(cmd == false)
   {
     cmd = true;
   }
   else
   {
     cmd = false;
   }
   sendByte = true;
}

void setup()
{
  attachInterrupt(0 , HTSPB, CHANGE);
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
}
void loop()
{
  if (sendByte == true)
  {
    if(cmd == false)
    {
      digitalWrite(latchpin, HIGH);
      digitalWrite(latchpin, LOW);
      data = random(256);
      Serial.println(data);
      shiftOut(datapin, clockpin, MSBFIRST, data);
    }
    else
    { 
      digitalWrite(latchpin, HIGH);
      digitalWrite(latchpin, LOW);  
      address = random(1, 3);
      Serial.println(address);
      shiftOut(datapin, clockpin, MSBFIRST, address);
    }
    sendByte = false;
  }
}

/*


1. htpb polls register
2. arduino sends next byte
*/
