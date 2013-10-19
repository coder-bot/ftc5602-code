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
	while (time1 [T2] < driveTime) {
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
	while (time1 [T3] < turnTime) {
		//motor [leftDrive] = -1 * turnSpeed;
		//motor [rightDrive] = turnSpeed;
	//simplified code below
		drive(-1 * turnSpeed, turnSpeed);
	}
	allStop();
}

void timedLeftPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T4);
	while (time1 [T4] < turnTime) {
		//motor [leftDrive] = turnSpeed;
		//motor [rightDrive] = -1 * turnSpeed;
		//simplified code below
		drive(turnSpeed, -1 * turnSpeed);
	}
	allStop();
}

void rightPointTurn (int turnSpeed)
{
	//motor [leftDrive] = -1 * turnSpeed;
	//motor [rightDrive] = turnSpeed;
	//simplified code below
	drive(turnSpeed, -1 * turnSpeed);
}

void leftPointTurn (int turnSpeed)
{
	//motor [leftDrive] = turnSpeed;
	//motor [rightDrive] = -1 * turnSpeed;
//simplified code below
		drive(-1 * turnSpeed, turnSpeed);
}

void alignWithBeacon ()
{
		while (SensorValue [irSensor] !=5)
	{
		nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSensor]);
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(50);
		}
		/*added else*/ else if (SensorValue [irSensor] < 5) {
			leftPointTurn(50);
		} else {
		/*removed if replaced with else*/ /*if (SensorValue [irSensor] == 5) {*/
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

	wait1Msec(2500);

	timedDrive(-75, -75, 1000);
	timedRightPointTurn(100, 450);
	//timedLeftPointTurn(100, 450);
	timedDrive(100, 100, 1500);
	allStop();

#if 0
	while (SensorValue [irSensor] !=5)
	{
		nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSensor]);
		if (SensorValue [irSensor] > 5) {
			rightPointTurn(50);
		}
		if (SensorValue [irSensor] < 5) {
			leftPointTurn(50);
		}
		if (SensorValue [irSensor] == 5) {
			allStop();
		}
	}
	allStop();
#elif 0
	nxtDisplayCenteredBigTextLine(4 ,"%d", SensorValue [irSensor]);
	if (SensorValue [irSensor] > 5) {
		motor [leftDrive] = -50;
		motor [rightDrive] = 50;
	}
	if (SensorValue [irSensor] < 5) {
		motor [leftDrive] = 50;
		motor [rightDrive] = -50;
	}
	if (SensorValue [irSensor] == 5) {
		motor [rightDrive] = 0;
		motor [leftDrive] = 0;
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
