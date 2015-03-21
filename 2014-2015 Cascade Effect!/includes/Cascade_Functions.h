int driveEncoderCycle = 1120;
int driveCycles;
int humor;
int xDrive, yDrive, rotation;
int phase;
int driveMode;
#define AUTO 0
#define TELEOP 1
#define DRIVE_MODE_STD 1
#define DRIVE_MODE_EG 2
//int goalHeight;

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

task failSafe()
{
	ClearTimer(T1);
	while(1)
	{
		if (time1 [T1] > 3500)
		{
			StopAllTasks();
		}
	}
}

void drive(int x1, int y1, int x2)
{
	xDrive = x1;
	yDrive = y1;
	rotation = x2;
	motor [frontLeft] = (y1 + x2 + x1);
	motor [frontRight] = (y1 - x2 - x1);
	motor [rearLeft] = (y1 + x2 - x1);
	motor [rearRight] = (y1 - x2 + x1);
}

void allStop()
{
	while (abs(xDrive) > 0 || abs(yDrive) > 0 || abs(rotation) > 0)
	{
		if (abs(xDrive) > 20)
		{
			if (xDrive > 0)
			{
				xDrive -= 20;
			}
			else if (xDrive < 0)
			{
				xDrive += 20;
			}
		}
		else
		{
			xDrive = 0;
		}

		if (abs(yDrive) > 20)
		{
			if (yDrive > 0)
			{
				yDrive -= 20;
			}
			else if (yDrive < 0)
			{
				yDrive += 20;
			}
		}
		else
		{
			yDrive = 0;
		}

		if (abs(rotation) > 20)
		{
			if (rotation > 0)
			{
				rotation -= 20;
			}
			else if (rotation < 0)
			{
				rotation += 20;
			}
		}
		else
		{
			rotation = 0;
		}
		drive(xDrive, yDrive, rotation);
		wait1Msec(100);
	}
	drive(0, 0, 0);
}

void score(int height)
{
	if (height == 30)
	{
		allStop();
		if (phase == AUTO)
		{
			servo [doors] = 122;
			wait1Msec(200);
			servo [doors] = 90;
			wait1Msec(200);
			servo [doors] = 69;
			wait1Msec(200);
			servo [doors] = 30;
			wait1Msec(200);
			servo [doors] = 0;
			wait1Msec(250);
			servo [doors] = 122;
			wait1Msec(50);
		}
	}

	else if (height == 60)
	{
		allStop();
		ClearTimer(T3);
		motor [lift] = 100;
		if (phase == TELEOP)
		{
			wait1Msec(1500);
		}
		motor [arm] = -100;
		servo [pivot] = 128;
		while (time1[T3] < 1250)
		{
		}
		if (phase == TELEOP)
		{
			wait1Msec(500);
		}
		motor [lift] = 0;
		if (phase == TELEOP)
		{
			while (time1[T3] < 3875)
			{
			}
			motor [arm] = 0;
		}
		else if (phase == AUTO)
		{
			while (time1[T3] < 4050 - 1600)
			{
			}
			motor [arm] = 0;
			wait1Msec(50);
		}
	}

	else if (height == 90)
	{
		allStop();
		if (phase == TELEOP)
		{
			ClearTimer(T3);
			motor [lift] = 100;
			wait1Msec(1500);
			motor [arm] = -100;
			servo [pivot] = 128;
			while (time1[T3] < 3500)
			{
			}
			motor [lift] = 0;
			while (time1[T3] < 3875)
			{
			}
			motor [arm] = 0;
		}
		else if (phase == AUTO)
		{
			motor [lift] = 100;
			wait1Msec(2100);
			motor [lift] = 0;
			wait1Msec(50);
		}
	}

	else if (height == 120)
	{
		allStop();
		ClearTimer(T3);
		motor [lift] = 100;
		wait1Msec(1500);
		motor [arm] = -100;
		servo [pivot] = 66;
		while (time1[T3] < 3500)
		{
		}
		motor [arm] = 0;
		while (time1[T3] < 3600)
		{
		}
		motor [lift] = 0;
		wait1Msec(50);
	}
}

int killSwitch()
{
	getJoystickSettings(joystick);
	if (joy1Btn(10) == 1)
		return 1;
	else
		return 0;
}

void scoreWithKill(int height)
{
	if (height == 30)
	{
		allStop();
		if (phase == AUTO)
		{
			servo [doors] = 122;
			wait1Msec(200);
			servo [doors] = 90;
			wait1Msec(200);
			servo [doors] = 69;
			wait1Msec(200);
			servo [doors] = 30;
			wait1Msec(200);
			servo [doors] = 0;
			wait1Msec(250);
			servo [doors] = 122;
			wait1Msec(50);
		}
	}

	else if (height == 60)
	{
		allStop();
		ClearTimer(T3);
		motor [lift] = 100;
		if (phase == TELEOP)
		{
			wait1Msec(1500);
		}
		motor [arm] = -100;
		servo [pivot] = 128;
		while (time1[T3] < 1750)
		{
			if (killSwitch())
			{
				servo [pivot] = 245;
				return;
			}
		}
		motor [lift] = 0;
		if (phase == TELEOP)
		{
			while (time1[T3] < 3875)
			{
				if (killSwitch())
				{
					servo [pivot] = 245;
					return;
				}
			}
			motor [arm] = 0;
		}
		else if (phase == AUTO)
		{
			while (time1[T3] < 4050 - 1600)
			{
			}
			motor [arm] = 0;
			wait1Msec(50);
		}
	}

	else if (height == 90)
	{
		allStop();
		if (phase == TELEOP)
		{
			ClearTimer(T3);
			motor [lift] = 100;
			wait1Msec(1500);
			motor [arm] = -100;
			servo [pivot] = 128;
			while (time1[T3] < 3500)
			{
				if (killSwitch())
				{
					servo [pivot] = 245;
					return;
				}
			}
			motor [lift] = 0;
			while (time1[T3] < 3875)
			{
				if (killSwitch())
				{
					servo [pivot] = 245;
					return;
				}
			}
			motor [arm] = 0;
		}
		else if (phase == AUTO)
		{
			motor [lift] = 100;
			wait1Msec(2100);
			motor [lift] = 0;
			wait1Msec(50);
		}
	}

	else if (height == 120)
	{
		allStop();
		ClearTimer(T3);
		motor [lift] = 100;
		wait1Msec(1500);
		motor [arm] = -100;
		servo [pivot] = 66;
		while (time1[T3] < 3500)
		{
			if (killSwitch())
			{
				servo [pivot] = 245;
				return;
			}
		}
		motor [arm] = 0;
		while (time1[T3] < 3600)
		{
			if (killSwitch())
			{
				servo [pivot] = 245;
				return;
			}
		}
		motor [lift] = 0;
		wait1Msec(50);
	}
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

void switchDriveMode(int driveModeToSwitchTo)
{
	while (joy1Btn(9) == 1 && joy1Btn(10) == 1)
	{
	}
	driveMode = driveModeToSwitchTo;
}

void initializeRobot()
{
	nxtDisplayCenteredTextLine(3, "Initializaing");
	nxtDisplayCenteredTextLine(4, "servos...");
	servo [pivot] = 245;
	servo [doors] = 122;
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
		eraseDisplay();
	}
	if (phase == TELEOP)
	{
		switchDriveMode(DRIVE_MODE_STD);
		nxtDisplayCenteredTextLine(3, "Drive mode:");
		nxtDisplayCenteredTextLine(4, "standard.");
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
			//if (humor >= 120)
			//{
			//	nxtDisplayCenteredTextLine(3, "POP THIS!");
			//	wait1Msec(1000);
			//}
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
