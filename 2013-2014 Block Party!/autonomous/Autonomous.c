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
	while (SensorValue [irSensor] != 0)
	{
		drive(35, 35);
	}
	allStop();
}

void alignWithBeacon ()
{
	while (SensorValue [irSensor] !=5)
	{
		nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSensor]);
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(15);
		}
		else if (SensorValue [irSensor] < 5) {
			leftPointTurn(15);
			} else {
			allStop();
			/*try commenting and uncommenting this line*/ return;
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
	//change next line to either right or left depending on side
	leftScanForBeacon();
	alignWithBeacon();
	driveToBeacon(45);
}
