#pragma config(Sensor, S3,     HTPB,                sensorI2CCustom9V)
task main()
{
	clearDebugStream();
	char send[3] = {2, 0x10, 132};
	char packet[1] = {0};
	int const replySize = 1;
	while(true)
	{
		for (int j = 0; j <= 252; j++)
		{
			sendI2CMsg(HTPB, send, replySize);
			wait1Msec(100);
			readI2CReply(HTPB, packet, replySize);
			for (int i = 0; i < replySize; i++)
			{
				writeDebugStreamLine("memory: %d is %d", j, packet[0]);
			}
		}
	}
}

///////////////////mem map////////////////////////////
//SharedMem01 = 128
//SharedMem02 = 132
//SharedMem03 = 136
//SharedMem04 = 140
//SharedMem32 = 252
//each mem is 32 bit
//
//
