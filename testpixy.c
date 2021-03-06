#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTPB,           sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void getXY(int &Xbuf, int &Ybuf)
{
	int const replySize = 1;
	char send[3] = {2, 0x10, 128};
	char send2[3] = {2, 0x10, 136};
	char packet[1];
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			sendI2CMsg(HTPB, send, replySize);
			wait1Msec(200);
			readI2CReply(HTPB, packet, replySize);
			Ybuf = packet;
		}
		else
		{
			sendI2CMsg(HTPB, send2, replySize);
			wait1Msec(200);
			readI2CReply(HTPB, packet, replySize);
			Xbuf = packet;
		}
	}
}

task main()
{

	int Xpoint = 0, Ypoint = 0;
	int motorspd;

//#define state

#ifdef state
	//hogCPU();
	while(i2cStatusPending == nI2CStatus[HTPB]);
	const char packet[] = {7, 0x10, 0x52, 0x00, 0x00, 0x00, 0xFF, 0x02};
	sendI2CMsg(HTPB, packet, 0);
	sleep(100);
	//releaseCPU();

#else

	while(i2cStatusPending == nI2CStatus[HTPB]);
	const char packet[] = {7, 0x10, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00};
	sendI2CMsg(HTPB, packet, 0);
	sleep(100);

#endif

	while(true)
	{
		//turn to center goal
		getXY(Ypoint, Xpoint);
		eraseDisplay();
		displayTextLine(1, "%d", Xpoint);
		drawCircle(Xpoint/2.65625 - 2, Ypoint/7.0833 + 2, 4);
		motorspd = 2 * (Ypoint - 127);
		clearDebugStream();
		writeDebugStreamLine("x = %d", Xpoint);
		writeDebugStreamLine("y = %d", Ypoint);
		writeDebugStreamLine("turn = %d", motorspd);
	}
}
