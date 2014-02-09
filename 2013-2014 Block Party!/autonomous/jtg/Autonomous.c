#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     lineFollower,   sensorLightActive)
#pragma config(Sensor, S4,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     grabberArm,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     spinnerArm,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    grabber,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    leftLatch,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)

//#include <JoystickDriver.c>
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
#define BLOCK_CRATE_UNDEFINED 0
#define FIRST_CRATE_DIST  1167
#define SECOND_CRATE_DIST 2333
#define THIRD_CRATE_DIST 3500
#define FOURTH_CRATE_DIST 4667
#define WHITE 45

int startingSide = RIGHT_SIDE;
int blockCrate;
int crateDistance;

void initializeRobot ()
{
	servo [leftLatch] = 255;
	servo [rightLatch] = 0;
	servo [wrist] = 230;
	servo [grabber] = 255;
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

void placeBlock ()
{
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
			timedRightPointTurn(100, 1000);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(75, 75);
			}
			allStop();
			timedLeftPointTurn(100, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (75, 80);
			}
			wait1Msec(150);
			allStop();
			timedLeftPointTurn(100, 600);
			driveOntoBridge();
		}
		else if (blockCrate == 3 || blockCrate == 4) {
			timedLeftPointTurn(100, 1000);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(80, 80);
			}
			allStop();
			timedRightPointTurn(60, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (75, 80);
			}
			wait1Msec(150);
			allStop();
			timedRightPointTurn(100, 600);
			//drives onto bridge and stops
			timedDrive(100, 100, 1750);
		}
	}
	else if (blockCrate == BLOCK_CRATE_UNDEFINED) {
		return;
	}
	if (startingSide == LEFT_SIDE)
	{
		if (blockCrate == 1 || blockCrate == 2) {
			timedRightPointTurn(100, 1000);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(80, 80);
			}
			allStop();
			timedLeftPointTurn(100, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (75, 80);
			}
			wait1Msec(150);
			allStop();
			timedLeftPointTurn(100, 600);
			driveOntoBridge();
		}
		else if (blockCrate == 3 || blockCrate == 4) {
			timedLeftPointTurn(50, 1000);
			while (SensorValue [sonarSensor] < 10)
			{
				drive(80, 80);
			}
			allStop();
			timedRightPointTurn(60, 625);
			while (SensorValue [lineFollower] < WHITE)
			{
				drive (75, 80);
			}
			wait1Msec(150);
			allStop();
			timedRightPointTurn(100, 600);
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
	driveToBeacon(50);
	wait1Msec(1000);
	parkOnBridge();
}
