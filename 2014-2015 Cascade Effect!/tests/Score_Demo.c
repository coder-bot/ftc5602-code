#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     harvester,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rearRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    guiderDrop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    pivot,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    doors,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <JoystickDriver.c>
#include "Cascade_Functions.h"

int goalHeight = 60;

void updateGoalHeightDisplay()
{
	nxtDisplayCenteredTextLine(3, "Goal height: %d", goalHeight);
}

task main()
{
	phase = TELEOP; //defined as teleop since lift is not raised prior to scoring as assumed for autonomous
	bDisplayDiagnostics = false;
	initializeRobot();
	updateGoalHeightDisplay();
	while (1)
	{
		if (nNxtButtonPressed == 1)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			goalHeight += 30;
			updateGoalHeightDisplay();
		}
		else if (nNxtButtonPressed == 2)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			goalHeight -= 30;
			updateGoalHeightDisplay();
		}
		if (nNxtButtonPressed == 3)
		{
			while (nNxtButtonPressed != -1)
			{
			}
			eraseDisplay();
			break;
		}
		if (goalHeight < 60)
		{
			goalHeight = 60;
			updateGoalHeightDisplay();
		}
		if (goalHeight > 120)
		{
			goalHeight = 120;
			updateGoalHeightDisplay();
		}
	}
	bDisplayDiagnostics = true;
	if (goalHeight != 120)
	{
		servo [leftHook] = 168;
		servo [rightHook] = 16;
		wait1Msec(500);
	}
	score(goalHeight);
	wait1Msec(5000);
}
