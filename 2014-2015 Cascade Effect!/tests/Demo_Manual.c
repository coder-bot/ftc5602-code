#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rearRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    guiderDrop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    cover,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int resetDriveEncoders()
{
	nMotorEncoder [frontLeft] = 0;
	nMotorEncoder [frontRight] = 0;
	nMotorEncoder [rearLeft] = 0;
	nMotorEncoder [rearRight] = 0;
	return 0;
}

void initializeRobot()
{
	nxtDisplayCenteredTextLine(3, "Initializaing");
	nxtDisplayCenteredTextLine(4, "servos...");
	servo [cover] = 160;
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

task main()
{
	initializeRobot();
	nxtDisplayCenteredTextLine(3, "Left: Lift");
	nxtDisplayCenteredTextLine(4, "Right: Arm");
	while (1)
	{
		if (nNxtButtonPressed == 2)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			eraseDisplay();
			nxtDisplayCenteredBigTextLine(3, "Lift");
			while (1)
			{
				if (nNxtButtonPressed == 1)
					motor [lift] = 100;
				else if (nNxtButtonPressed == 2)
					motor [lift] = -25;
				else
					motor [lift] = 0;
				if (nNxtButtonPressed == 3)
				{
					while (nNxtButtonPressed != -1)
					{
					}
					eraseDisplay();
					nxtDisplayCenteredTextLine(3, "Left: Lift");
					nxtDisplayCenteredTextLine(4, "Right: Arm");
					break;
				}
			}
		}
		else if (nNxtButtonPressed == 1)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			eraseDisplay();
			nxtDisplayCenteredBigTextLine(3, "Arm");
			while (1)
			{
				if (nNxtButtonPressed == 1)
					motor [arm] = -50;
				else if (nNxtButtonPressed == 2)
					motor [arm] = 50;
				else
					motor [arm] = 0;
				if (nNxtButtonPressed == 3)
				{
					while (nNxtButtonPressed != -1)
					{
					}
					eraseDisplay();
					nxtDisplayCenteredTextLine(3, "Left: Lift");
					nxtDisplayCenteredTextLine(4, "Right: Arm");
					break;
				}
			}
		}
	}
}
