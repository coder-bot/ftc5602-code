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
	servo [leftLatch] = 218 /*255, 210 originally*/;
	servo [rightLatch] = 30;
	servo [wrist] = 190;
	servo [grabber] = 200;
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

//ir scanning, aligning and driving code
void rightScanForBeacon ()
{
	//right side version
	if (SensorValue [irSensor] == 9)
	{
		while (SensorValue [irSensor] > 6)
		{
			leftPointTurn(70);
		}
		allStop();
		} else {
		while (SensorValue [irSensor] != 9)
		{
			drive(100, 100);
		}
		allStop();
	}
}

void leftScanForBeacon ()
{
	//left side version
	if (SensorValue [irSensor] == 1)
	{
		while (SensorValue [irSensor] < 4)
		{
			leftPointTurn(70);
		}
		allStop();
		} else {
		while (SensorValue [irSensor] != 1)
		{
			drive(100, 100);
		}
		allStop();
	}
}

void alignWithBeacon ()
{
	while (SensorValue [irSensor] !=5)
	{
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(70);
		}
		else if (SensorValue [irSensor] < 5) {
			leftPointTurn(70);
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

//routine to place block in crate
void placeBlock ()
{
	ClearTimer(T1);
	while (time1 [T1] < 1400)
	{
		motor [grabberArm] = 100;
	}
	motor [grabberArm] = 0;
	servo [grabber] = 10;
	ClearTimer(T1);
	while (time1 [T1] < 1250)
	{
		motor [grabberArm] = -100;
	}
	motor [grabberArm] = 0;
	//drives away from block crates
	while (SensorValue [sonarSensor] < 75)
	{
		drive(-100, -100);
	}
	drive(0, 0);
}

//function for driving onto ramp after placing the block
void driveOntoRamp ()
{
	while (SensorValue [sonarSensor] < 35)
	{
		drive(-100, -100);
	}
	allStop();
	if (STARTING_SIDE == RIGHT_SIDE) {
		while (SensorValue [irSensor] != 2)
		{
			rightPointTurn(100);
		}
		allStop();
	}
	else if (STARTING_SIDE == LEFT_SIDE) {
		while (SensorValue [irSensor] != 8)
		{
			leftPointTurn(100);
		}
		allStop();
	}

	while (SensorValue [sonarSensor] > 55)
	{
		drive (80, 80);
	}
	allStop();
	if (STARTING_SIDE == RIGHT_SIDE) {
		timedLeftPointTurn(100, 850);
	}
	else if (STARTING_SIDE == LEFT_SIDE)
	{
		timedRightPointTurn(100, 850);
	}

	while (SensorValue [lineFollower] > ACTIVE_WHITE)
	{
		drive (75, 75);
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
