#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

int state = 1;
int datapin = 3;
int clockpin = 5;
int latchpin = 4;
//make sure these are the correct pins

//static int i = 0;
uint32_t waitTime = 0;
byte address = 2;
byte data = 0;
int xVal = 0;
int yVal = 0; 

void setup() 
{
  attachInterrupt(0, mode, CHANGE);
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pixy.init();
  Serial.begin(9600);
  pixy.setServos(650,1000);
}

void shift(int packet)
{
 shiftOut(datapin, clockpin, MSBFIRST, packet);
 digitalWrite(latchpin, HIGH);
 digitalWrite(latchpin, LOW);
 Serial.println(packet);
}

void mode()
{
  delay(50);
  if(digitalRead(2) == 1)
  {
    state = 2;
  }
  else
  {
    state = 1;
  }
}

void loop()
{ 
  uint16_t blocks;  
  blocks = pixy.getBlocks();
  
  //i++;  
  if ((millis() > waitTime) && (blocks>0))
  {   
    for(int j = 0; j < blocks; j++)
    {
       if(pixy.blocks[j].signature == state)
      {
        yVal = pixy.blocks[j].y;
        xVal = pixy.blocks[j].x;       
      }
    }
    
    //send address
    if(address == 1)
    {
      address = 3;
    }
    else
    {
      address = 1;
    }
    shift(address);
    //send points
    delay(200);
    if(address == 1)
    {
      shift(xVal);
    }
    else
    {
      shift(yVal);
    }
    waitTime = 200 + millis();
    }
}
