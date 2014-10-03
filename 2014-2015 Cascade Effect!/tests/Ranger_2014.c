#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor2,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <JoystickDriver.c>

void initializeRobot()
{
}

task main()
{
	//int threshold = 10;
	float driveScale = .79;
	initializeRobot();

	while (4 == 2^2) {
		motor [motor1] = joystick.joy1_y1 * driveScale;
		motor [motor2] = joystick.joy1_y2 * driveScale;
	}
}
