#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     lineFollower,   sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop)

#include <JoystickDriver.c>
#include <drivers/hitechnic-irseeker-v2.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define BLOCK_CRATE_UNDEFINED 0

int startingSide = RIGHT_SIDE;
int blockCrate;
int crateDistance;
int firstCrateDist = 200;
int secondCrateDist = 1000;
int thirdCrateDist = 1500;
int fourthCrateDist = 2500;
int white = 45;

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
void timedDrive (int rightSpeed, int leftSpeed, int driveTime)
{
	ClearTimer(T2);
	while (time1 [T2] < driveTime)
	{
		motor [rightDrive] = rightSpeed;
		motor [leftDrive] = leftSpeed;
	}
	allStop();
}

void rightPointTurn (int turnSpeed)
{
	drive(turnSpeed, -1 * turnSpeed);
}

void leftPointTurn (int turnSpeed)
{
	drive(-1 * turnSpeed, turnSpeed);
}

void timedRightPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T3);
	while (time1 [T3] < turnTime)
	{
		drive(turnSpeed, -1 * turnSpeed);
	}
	allStop();
}

void timedLeftPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T4);
	while (time1 [T4] < turnTime)
	{
		drive(-1 * turnSpeed, turnSpeed);
	}
	allStop();
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

void driveOntoBridge()
{
	timedDrive(100, 100, 1750);
}

void setCrate ()
{
	if (time1 [T1] <= firstCrateDist) {
		blockCrate = 1;
		crateDistance = firstCrateDist;
	}
	else if (time1 [T1] <= secondCrateDist) {
		blockCrate = 2;
		crateDistance = secondCrateDist;
	}
	else if (time1 [T1] <= thirdCrateDist) {
		blockCrate = 3;
		crateDistance = thirdCrateDist;
	}
	else if (time1 [T1] >= fourthCrateDist) {
		blockCrate = 4;
		crateDistance = fourthCrateDist;
		} else {
		blockCrate = BLOCK_CRATE_UNDEFINED;
		crateDistance = 0;
	}
}

void parkOnBridge ()
{

	timedDrive(-50, -50, 280);
	if (startingSide == RIGHT_SIDE)
	{
		if (blockCrate == 1 || blockCrate == 2) {
			timedRightPointTurn(50, 600);
			ClearTimer(T2);
			timedDrive(50, 50, crateDistance + 150);
			timedLeftPointTurn(60, 625);
			while (SensorValue [lineFollower] < white)
			{
				drive (50, 55);
			}
			wait1Msec(150);
			allStop();
			timedLeftPointTurn(50, 600);
			driveOntoBridge();
		}
	}
}

task main()
{
	initializeRobot();
	ClearTimer(T1);
	if (startingSide == LEFT_SIDE) {
		leftScanForBeacon();
	}
	else if (startingSide == RIGHT_SIDE) {
		rightScanForBeacon();
	}
	setCrate();
	alignWithBeacon();
	driveToBeacon(30);
	wait1Msec(1000);
	parkOnBridge();
}
