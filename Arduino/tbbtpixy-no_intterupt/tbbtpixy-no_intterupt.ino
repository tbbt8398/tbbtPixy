#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

bool twostate = false;
int datapin = 3;
int clockpin = 5;
int latchpin = 4;
//make sure these are the correct pins

//static int i = 0;
uint32_t waitTime = 500;
byte address = 1;
byte data = 0;
int xVal = 0;
int yVal = 0; 

void setup() 
{
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pixy.init();
  //Serial.begin(9600);
  pixy.setServos(650,1000);
}

void shift(int packet)
{
 shiftOut(datapin, clockpin, MSBFIRST, packet);
 digitalWrite(latchpin, HIGH);
 digitalWrite(latchpin, LOW);
 //Serial.println(packet);
}

void loop()
{ 
  uint16_t blocks;  
  blocks = pixy.getBlocks();
  //i++;  
  if (millis() > waitTime)
  {   
    //for(int j = 0; j < blocks; j++)
    //{
      //if(pixy.blocks[j].y < yVal && pixy.blocks[j].y > 0)
      //{
        yVal = pixy.blocks[0].y;
        xVal = pixy.blocks[0].x; 
        //Serial.println(j);      
      //}
    //}
    
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
  }/*
  else if(millis() > waitTime && blocks == 0)
  {
    //send error byte
    waitTime += 2000;
    shift(1);
    delay(250);
    shift(255);
  }*/
}
