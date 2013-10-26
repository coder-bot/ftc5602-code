#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     lineFollower,   sensorCOLORFULL)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop)

#include <JoystickDriver.c>
#include <drivers/hitechnic-irseeker-v2.h>

void initializeRobot ()
{
}

void allStop ()
{
	motor [rightDrive] = 0;
	motor [leftDrive] = 0;
	//return;
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

void drive (int rightSpeed, int leftSpeed)
{
	motor [rightDrive] = rightSpeed;
	motor [leftDrive] = leftSpeed;
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

void rightPointTurn (int turnSpeed)
{
	drive(turnSpeed, -1 * turnSpeed);
}

void leftPointTurn (int turnSpeed)
{
	drive(-1 * turnSpeed, turnSpeed);
}

void alignWithBeacon ()
{
	while (SensorValue [irSensor] !=5)
	{
		nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSensor]);
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(25);
		}
		else if (SensorValue [irSensor] < 5) {
			leftPointTurn(25);
			} else {
			allStop();
			return;
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

	alignWithBeacon();
	driveToBeacon(45);
}
