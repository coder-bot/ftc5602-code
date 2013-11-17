#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     lineFollower,   sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)

#include <JoystickDriver.c>

const int threshold = 12;

void initializeRobot()
{
	return;
}

task main()
{
	initializeRobot();
	while (1)
	{
		getJoystickSettings(joystick);
	motor [leftDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y1 : 0;
	motor [rightDrive] = abs(joystick.joy1_y2) > threshold ? joystick.joy1_y2 : 0;
	}
}
