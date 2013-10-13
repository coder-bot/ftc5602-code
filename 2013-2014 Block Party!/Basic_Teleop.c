#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     harvesterMover, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//comment
// even more comments
#include <JoystickDriver.c>
int threshold = 12;

task main()
{
	while (1)
	{
		getJoystickSettings(joystick);
	motor [leftDrive] = abs(joystick.joy1_y2) > threshold ? joystick.joy1_y1 : 0;
	motor [rightDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y2 : 0;
#if 0
	if (joy1Btn(7) == 1) {
			motor [harvesterMover] = (joy1Btn(5) == 1 || joy1Btn(6) == 1) ? 50 : 25;
		}
		else if (joy1Btn(8) == 1) {
			motor [harvesterMover] = (joy1Btn(5) == 1 || joy1Btn(6) == 1) ? -50 : -25;
			} else {
			motor [harvesterMover] = 0;
		}
#endif
	}
}
