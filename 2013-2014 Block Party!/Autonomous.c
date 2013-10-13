#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop, reversed)

#include <JoystickDriver.c>
#include <drivers/hitechnic-irseeker-v2.h>
void initializeRobot ()
{
}

void allStop ()
{
	motor [leftDrive] = 0;
	motor [rightDrive] = 0;
}

void drive (int leftSpeed, int rightSpeed, int driveTime)
{
	ClearTimer(T2);
	while (time1 [T2] < driveTime) {
		motor [leftDrive] = leftSpeed;
		motor [rightDrive] = rightSpeed;
	}
	allStop();
}

void rightPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T3);
	while (time1 [T3] < turnTime) {
		motor [rightDrive] = -1 * turnSpeed;
		motor [leftDrive] = turnSpeed;
	}
	allStop();
}

void leftPointTurn (int turnSpeed, int turnTime)
{
	ClearTimer(T4);
	while (time1 [T4] < turnTime) {
		motor [rightDrive] = turnSpeed;
		motor [leftDrive] = -1 * turnSpeed;
	}
	allStop();
}


task main()
{
#if 0
	initializeRobot();
	waitForStart();
	drive(100, 100, 2500);
	rightPointTurn (50, 1100);
	drive(100, 100, 3000);
#endif

//ir stuff here

}
