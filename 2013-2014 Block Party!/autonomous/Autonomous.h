#include <JoystickDriver.c>
//#include <drivers/hitechnic-sensormux.h>
//#include <drivers/hitechnic-superpro.h>
//#include <drivers/lego-touch.h>
//#include <drivers/lego-ultrasound.h>
//#include <drivers/lego-light.h>
//#include <drivers/hitechnic-irseeker-v2.h>

//const tMUXSensor sonarSensor = msensor_S3_1;
//const tMUXSensor irSensor = msensor_S3_1;
//const tMUXSensor lineFollower = msensor_S3_2;

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define ACTIVE_WHITE 30
//#define BLOCK_CRATE_UNDEFINED 0
//#define FIRST_CRATE_DIST  1167
//#define SECOND_CRATE_DIST 2333
//#define THIRD_CRATE_DIST 3500
//#define FOURTH_CRATE_DIST 4667
//#define WHITE 45

//int startingSide = RIGHT_SIDE;
//int blockCrate;
//int crateDistance;

//initialize routine
void initializeRobot ()
{
	servo [leftLatch] = 225 /*255, 210 originally*/;
	servo [rightLatch] = 0;
	servo [wrist] = 230;
	servo [grabber] = 210 /*255, 210 originally*/;
}

//drive functions
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
	drive(-1 * turnSpeed, turnSpeed);
}

void leftPointTurn (int turnSpeed)
{
	drive(turnSpeed, -1 * turnSpeed);
}

void timedRightPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T3);
	while (time1 [T3] < turnTime)
	{
		drive(-1 * turnSpeed, turnSpeed);
	}
	allStop();
}

void timedLeftPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T4);
	while (time1 [T4] < turnTime)
	{
		drive(turnSpeed, -1 * turnSpeed);
	}
	allStop();
}

//for use with programs solely driving onto the ramp
void basicDriveOntoRamp ()
{
	while (SensorValue [lineFollower] < ACTIVE_WHITE)
	{
		drive(100, 100);
	}
	wait1Msec(275);
	allStop();

	if (STARTING_SIDE == LEFT_SIDE) {
		timedRightPointTurn(100, 1100);
	} else if (STARTING_SIDE == RIGHT_SIDE)
	{
		timedLeftPointTurn(100, 1000);
	}

	allStop();
	timedDrive(100, 100, 2220);
}

void rightScanForBeacon ()
{
	//right side version
	while (SensorValue [irSensor] != 9)
	{
		drive(100, 100);
	}
	allStop();
}

void leftScanForBeacon ()
{
	//left side version
	while (SensorValue [irSensor] != 1)
	{
		drive(100, 100);
	}
	allStop();
}

void alignWithBeacon ()
{
	while (SensorValue [irSensor] !=5)
	{
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(100);
		}
		else if (SensorValue [irSensor] < 5) {
			leftPointTurn(100);
			} else {
			allStop();
		}
	}
}

void driveToBeacon (int distanceFromBeacon)
{
	while (SensorValue [sonarSensor] > distanceFromBeacon)
	{
		drive(100, 100);
	}
	allStop();
}

void driveOntoRamp ()
{
	while (SensorValue [sonarSensor] < 70)
	{
		drive(-100, -100);
	}
	allStop();
	if (STARTING_SIDE == RIGHT_SIDE) {
		while (SensorValue [irSensor] != 1)
		{
			rightPointTurn(100);
		}
		allStop();
	}
	else if (STARTING_SIDE == LEFT_SIDE) {
		while (SensorValue [irSensor] != 9)
		{
			leftPointTurn(100);
		}
		allStop();
	}
	while (SensorValue [sonarSensor] < 35)
	{
		drive (100, 100);
	}
	allStop();
	if (STARTING_SIDE == RIGHT_SIDE) {
		timedLeftPointTurn(100, 800);
	}
	else if (STARTING_SIDE == LEFT_SIDE)
	{
		timedRightPointTurn(100, 800);
	}
	while (SensorValue [lineFollower] > ACTIVE_WHITE)
	{
		drive (100, 100);
	}
	allStop();
	if (STARTING_SIDE == RIGHT_SIDE) {
		timedLeftPointTurn(100, 900);
	}
	else if (STARTING_SIDE == LEFT_SIDE) {
		timedRightPointTurn(100, 900);
	}
	timedDrive(100, 100, 1500);
}

//routine to place block in crate
void placeBlock ()
{
}
