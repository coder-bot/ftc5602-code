int driveEncoderCycle = 1120;
int driveCycles;
int humor;

task humorWarning()
{
	while (1)
	{
		while(humor > 100)
		{
			nxtDisplayCenteredTextLine(5, "WARNING:");
			nxtDisplayCenteredTextLine(6, "Humor overload!");
			wait1Msec(825);
			nxtDisplayCenteredTextLine(5, "");
			nxtDisplayCenteredTextLine(6, "");
			wait1Msec(825);
		}
	}
}

void drive(int x1, int y1, int x2)
{
	motor [frontLeft] = (y1 + x2 + x1);
	motor [frontRight] = (y1 - x2 - x1);
	motor [rearLeft] = (y1 + x2 - x1);
	motor [rearRight] = (y1 - x2 + x1);
}

void allStop()
{
	drive(0, 0, 0);
}

int resetDriveEncoders()
{
	nMotorEncoder [frontLeft] = 0;
	nMotorEncoder [frontRight] = 0;
	nMotorEncoder [rearLeft] = 0;
	nMotorEncoder [rearRight] = 0;
	return 0;
}

void updateDriveCyclesDisplay()
{
	nxtDisplayCenteredTextLine(3, "Rotations: %d", driveCycles);
}

void updateHumorDisplay()
{
	nxtDisplayCenteredTextLine(3, "Set humor: %d%%", humor);
}

void initializeRobot()
{
	nxtDisplayCenteredTextLine(3, "Initializaing");
	nxtDisplayCenteredTextLine(4, "servos...");
	servo [cover] = 140;
	servo [leftHook] = 35;
	servo [rightHook] = 140;
	wait1Msec(1000);
	eraseDisplay();
	if (resetDriveEncoders() == 0)
	{
		nxtDisplayCenteredTextLine(3, "Encoders");
		nxtDisplayCenteredTextLine(4, "successfully");
		nxtDisplayCenteredTextLine(5, "reset.");
		wait1Msec(1000);
	}
	eraseDisplay();
}

void autonomousGUI()
{
	updateDriveCyclesDisplay();
	while (1)
	{
		if (nNxtButtonPressed == 1)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			driveCycles ++;
			updateDriveCyclesDisplay();
		}
		else if (nNxtButtonPressed == 2)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			driveCycles --;
			updateDriveCyclesDisplay();
		}
		if (nNxtButtonPressed == 3)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			eraseDisplay();
			if (driveCycles > 1)
				nxtDisplayCenteredTextLine(3, "%d rotations", driveCycles);
			else if (driveCycles == 1)
				nxtDisplayCenteredTextLine(3, "%d rotation", driveCycles);
			wait1Msec(800);
			break;
		}
		if (driveCycles < 0)
		{
			driveCycles = 0;
			updateDriveCyclesDisplay();
		}
	}
	StartTask(humorWarning);
	updateHumorDisplay();
	while (1)
	{
		if (nNxtButtonPressed == 1)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			humor += 10;
			updateHumorDisplay();
		}
		else if (nNxtButtonPressed == 2)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			humor -= 10;
			updateHumorDisplay();
		}
		if (nNxtButtonPressed == 3)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			StopTask(humorWarning);
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "%d%% humor", humor);
			wait1Msec(800);
			break;
		}
		if (humor < 0)
		{
			humor = 0;
			updateHumorDisplay();
		}
		//if (humor > 100)
		//{
		//	humor = 100;
		//	updateHumorDisplay();
		//}
	}
}

void initializeAutonomous()
{
	initializeRobot();
	autonomousGUI();
}
