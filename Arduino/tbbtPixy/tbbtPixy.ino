//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

/* 
   06.04.2014 v0.1.3 John Leimon
     + Now using pixy.init() to initialize Pixy in setup().
*/

#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

int datapin = 5; 
int clockpin = 4;
int latchpin = 3;

byte address = 1;
byte data = 0;
boolean cmd = false;
boolean sendByte = false;

void intterupt()
{
   if(cmd == false)
   {
     cmd = true;
   }
   else
   {
     cmd = false;
   }
   
   if (!sendByte)
   {
     sendByte = true;
   }
}

void setup()
{
  attachInterrupt(0 , intterupt, RISING);
  pinMode(2, INPUT);
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
  pixy.setServos(0,1000);
}

void shift(int packet, char letter)
{
 digitalWrite(latchpin, HIGH);
 digitalWrite(latchpin, LOW);
 shiftOut(datapin, clockpin, MSBFIRST, packet); 
}

void loop()
{ 
  uint16_t blocks;  
  blocks = pixy.getBlocks();
  if(blocks);
  {
    shift(pixy.blocks[0].x, 'x');
  }
}
