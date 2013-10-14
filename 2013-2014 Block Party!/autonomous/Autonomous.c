#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     lineFollower,   sensorCOLORFULL)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop, reversed)

#include <JoystickDriver.c>
#include <drivers/hitechnic-irseeker-v2.h>
void initializeRobot ()
{
}

void allStop ()
{
	motor [leftDrive] = 0;
	motor [rightDrive] = 0;
	//return;
}

void timedDrive (int leftSpeed, int rightSpeed, int driveTime)
{
	ClearTimer(T2);
	while (time1 [T2] < driveTime) {
		motor [leftDrive] = leftSpeed;
		motor [rightDrive] = rightSpeed;
	}
	allStop();
}

void drive (int leftSpeed, int rightSpeed)
{
	motor [leftDrive] = -1 * leftSpeed;
	motor [rightDrive] = -1 * rightSpeed;
}

void timedRightPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T3);
	while (time1 [T3] < turnTime) {
		//motor [rightDrive] = -1 * turnSpeed;
		//motor [leftDrive] = turnSpeed;
	//simplified code below
		drive(turnSpeed, -1 * turnSpeed);
	}
	allStop();
}

void timedLeftPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T4);
	while (time1 [T4] < turnTime) {
		//motor [rightDrive] = turnSpeed;
		//motor [leftDrive] = -1 * turnSpeed;
		//simplified code below
		drive(-1 * turnSpeed, turnSpeed);
	}
	allStop();
}

void rightPointTurn (int turnSpeed)
{
	//motor [rightDrive] = -1 * turnSpeed;
	//motor [leftDrive] = turnSpeed;
	//simplified code below
	drive(turnSpeed, -1 * turnSpeed);
}

void leftPointTurn (int turnSpeed)
{
	//motor [rightDrive] = turnSpeed;
	//motor [leftDrive] = -1 * turnSpeed;
//simplified code below
		drive(-1 * turnSpeed, turnSpeed);
}

void alignWithBeacon ()
{
		while (SensorValue [irSeeker] !=5)
	{
		nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSeeker]);
		if (SensorValue [irSeeker] > 5) {
			rightPointTurn(50);
		}
		if (SensorValue [irSeeker] < 5) {
			leftPointTurn(50);
		}
		if (SensorValue [irSeeker] == 5) {
			allStop();
		}
	}
	allStop();
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

#if 0
	while (SensorValue [irSeeker] !=5)
	{
		nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSeeker]);
		if (SensorValue [irSeeker] > 5) {
			rightPointTurn(50);
		}
		if (SensorValue [irSeeker] < 5) {
			leftPointTurn(50);
		}
		if (SensorValue [irSeeker] == 5) {
			allStop();
		}
	}
	allStop();
#elif 0
	nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSeeker]);
	if (SensorValue [irSeeker] > 5) {
		motor [rightDrive] = 50;
		motor [leftDrive] = -50;
	}
	if (SensorValue [irSeeker] < 5) {
		motor [rightDrive] = -50;
		motor [leftDrive] = 50;
	}
	if (SensorValue [irSeeker] == 5) {
		motor [leftDrive] = 0;
		motor [rightDrive] = 0;
	}
#endif

//basic driving

#if 0
	waitForStart();
	timedDrive(100, 100, 2500);
	timedRightPointTurn (50, 1100);
	timedDrive(100, 100, 3000);
#endif

}
