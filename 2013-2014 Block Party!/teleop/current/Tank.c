#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop)

//Teleop program for high-speed demo bot

#include <JoystickDriver.c>

task main()
{
	const int t = 8;
	const float standardDriveScale = 0.79
	while (1)
	{
		getJoystickSettings(joystick);
		motor [leftDrive] = (abs(joystick.joy1_y1) > t) ? joystick.joy1_y1 * standardDriveScale : 0;
		motor [rightDrive] = (abs(joystick.joy1_y2) > t) ? joystick.joy1_y2 * standardDriveScale: 0;
	}
}
