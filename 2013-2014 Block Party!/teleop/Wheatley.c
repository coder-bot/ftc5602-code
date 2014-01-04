#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     omniDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)

#include <JoystickDriver.c>

const int threshold = 8;

void initializeRobot ()
{
}

task main ()
{
	initializeRobot();
	waitForStart();
	while (1)
	{
	motor [leftDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y1 : 0;
	motor [rightDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y1 : 0;
	motor [omniDrive] = abs(joystick.joy1_x2) > threshold ? joystick.joy1_x2 : 0;
	}
}
