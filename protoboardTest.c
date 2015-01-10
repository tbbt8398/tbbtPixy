#pragma config(Sensor, S3,     HTPB,                sensorI2CCustom9V)
#include "hitechnic-protoboard.h"

task main()
{
	HTPBsetupIO(HTPB, 0x00);
	while(true)
	{
		eraseDisplay();
		displayTextLine(1, "input: %x", HTPBreadCustom(HTPB));
		wait1Msec(100);
	}
}
