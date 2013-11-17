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
#define FIRST_CRATE_DIST  200
#define SECOND_CRATE_DIST 1000
#define THIRD_CRATE_DIST 1500
#define FOURTH_CRATE_DIST 2500
#define WHITE 45

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
	if (time1 [T1] <= FIRST_CRATE_DIST) {
		blockCrate = 1;
		crateDistance = FIRST_CRATE_DIST;
	}
	else if (time1 [T1] <= SECOND_CRATE_DIST) {
		blockCrate = 2;
		crateDistance = SECOND_CRATE_DIST;
	}
	else if (time1 [T1] <= THIRD_CRATE_DIST) {
		blockCrate = 3;
		crateDistance = THIRD_CRATE_DIST;
	}
	else if (time1 [T1] >= FOURTH_CRATE_DIST) {
		blockCrate = 4;
		crateDistance = FOURTH_CRATE_DIST;
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
			while (SensorValue [sonarSensor] < 10)
			{
				drive(50, 50);
			}
			allStop();
			timedLeftPointTurn(60, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (50, 55);
			}
			wait1Msec(150);
			allStop();
			timedLeftPointTurn(45, 600);
			driveOntoBridge();
		}
		else if (blockCrate == 3 || blockCrate == 4) {
			timedLeftPointTurn(50, 600);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(50, 50);
			}
			allStop();
			timedRightPointTurn(60, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (50, 55);
			}
			wait1Msec(150);
			allStop();
			timedRightPointTurn(45, 600);
			driveOntoBridge();
		}
	}
	else if (blockCrate == BLOCK_CRATE_UNDEFINED) {
		return;
	}
	if (startingSide == LEFT_SIDE)
	{
		if (blockCrate == 1 || blockCrate == 2) {
			timedRightPointTurn(50, 600);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(50, 50);
			}
			allStop();
			timedLeftPointTurn(60, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (50, 55);
			}
			wait1Msec(150);
			allStop();
			timedLeftPointTurn(45, 600);
			driveOntoBridge();
		}
		else if (blockCrate == 3 || blockCrate == 4) {
			timedLeftPointTurn(50, 600);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(50, 50);
			}
			allStop();
			timedRightPointTurn(60, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (50, 55);
			}
			wait1Msec(150);
			allStop();
			timedRightPointTurn(45, 600);
			driveOntoBridge();
		}
		else if (blockCrate == BLOCK_CRATE_UNDEFINED) {
			return;
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
