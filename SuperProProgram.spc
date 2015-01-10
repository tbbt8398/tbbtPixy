#pragma autostart

task main()
{
 char address = 0xFF;
 char new = 0x00;
 char lastIn = 0xFF;
 bool cmd = false;
 while(true)
 {
   new = DigitalIn;
	 if(lastIn != new && new != 0xFF)
	 {
	 	if(cmd == true)
	 	{
		 if(new <= 0x03)
		 {
		  address = new;
		  cmd = false;
		 }
		 else
		 {
		 	cmd = true;
 		 }
	 }
	 else	if(cmd == false)
	 	{
		 cmd = true;
			if(address == 0x01)
			{
			 SharedMem01 = new;
			}
			else if(address == 0x03)
			{
			 SharedMem03 = new;
      }
		}
   lastIn = new;
 	 }
	}
}
