#pragma config(Sensor, S3,     HTPB,                sensorI2CCustom9V)
task main()
{
	clearDebugStream();
	//for(int j = 100; j < 150; j++)
	//{5
	int const replySize = 1;
	char packet[1];
	char send[3] = {2, 0x10, 128};
	char send2[3] = {2, 0x10, 136};
	while(true)
	{
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				sendI2CMsg(HTPB, send, replySize);
				while (nI2CStatus[HTPB] == STAT_COMM_PENDING);
				readI2CReply(HTPB, packet, replySize);
				writeDebugStreamLine("x_memory: %d is %d", 132, packet[0]);
			}
		else
			{
				sendI2CMsg(HTPB, send2, replySize);
				wait1Msec(200);
				readI2CReply(HTPB, packet, replySize);
				writeDebugStreamLine("y_memory: %d is %d", 128, packet[0]);
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
