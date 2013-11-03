#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     lineFollower,   sensorCOLORFULL)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop)

#include <JoystickDriver.c>
#include <drivers/hitechnic-irseeker-v2.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1

int startingSide = RIGHT_SIDE;

void initializeRobot ()
{
}

void allStop ()
{
	motor [rightDrive] = 0;
	motor [leftDrive] = 0;
}

void drive (int rightSpeed, int leftSpeed)
{
	motor [rightDrive] = rightSpeed;
	motor [leftDrive] = leftSpeed;
}

void rightPointTurn (int turnSpeed)
{
	drive(turnSpeed, -1 * turnSpeed);
}

void leftPointTurn (int turnSpeed)
{
	drive(-1 * turnSpeed, turnSpeed);
}

void rightScanForBeacon ()
{
	//right side version
	while (SensorValue [irSensor] != 9)
	{
		drive(35, 35);
	}
	allStop();
}

void leftScanForBeacon ()
{
	//left side version
	while (SensorValue [irSensor] != 1)
	{
		drive(35, 35);
	}
	allStop();
}

void alignWithBeacon ()
{
	while (SensorValue [irSensor] !=5)
	{
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(15);
		}
		else if (SensorValue [irSensor] < 5) {
			leftPointTurn(15);
			} else {
			allStop();
		}
	}
}

void driveToBeacon (int distanceFromBeacon)
{
	while (SensorValue [sonarSensor] > distanceFromBeacon)
	{
		drive(75, 75);
	}
	allStop();
}

task main()
{
	initializeRobot();

	if (startingSide == LEFT_SIDE) {
		leftScanForBeacon();
	}
	else if (startingSide == RIGHT_SIDE) {
		rightScanForBeacon();
	}

	alignWithBeacon();
	driveToBeacon(30);
}
