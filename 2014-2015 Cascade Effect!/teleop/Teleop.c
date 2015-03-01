#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     sweeper,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rearRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    guiderDrop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    pivot,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    doors,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <JoystickDriver.c>
#include "Cascade_Functions.h"

float manualDriveScale = (0.7874);

task autoCover()
{
	while (1)
	{
		if (joy2Btn(8) == 1)
		{
			ClearTimer(T1);
			while (joy2Btn(8) == 1)
			{
				if (time1[T1] > 1000)
					servo [pivot] = 255;
			}
		}
	}
}

task main()
{
	bDisplayDiagnostics = false;
	initializeRobot();
	bDisplayDiagnostics = true;

	int x1, y1, x2;
	int threshold = 8;
	//int liftPrecisionFactor = 0;
	//int pivotSet = 0;

	waitForStart();
	StartTask(autoCover);

	/*
	Encoder demo
	while (nMotorEncoder [frontLeft] < driveEncoderCycle)
	{
	motor [frontLeft] = 12 * autoDriveScale;
	}
	motor [frontLeft] = 0 * autoDriveScale;
	*/

	//run loop
	while (1)
	{
		//joystick refresh
		getJoystickSettings(joystick);
#if 0
		//lift precision factor - manual control of value
		if (joy2Btn(1) == 1) {
			liftPrecisionFactor += 5;
			while (joy2Btn(1) != 0)
			{
			}
		}
		else if (joy2Btn(3) == 1) {
			liftPrecisionFactor -= 5;
			while (joy2Btn(3) != 0)
			{
			}
		}

		//lift precision factor - automatic control of bounds
		if (liftPrecisionFactor <= 0) {
			liftPrecisionFactor = 0;
		}
		else if (liftPrecisionFactor >= 100) {
			liftPrecisionFactor = 95;
		}
#endif
		//drive code
	x1 = (abs(joystick.joy1_x1) > threshold) ? ((joystick.joy1_x1 * manualDriveScale) * 0.75) : 0;
	y1 = (abs(joystick.joy1_y1) > threshold) ? ((joystick.joy1_y1 * manualDriveScale) * 0.75) : 0;
	x2 = (abs(joystick.joy1_x2) > threshold) ? ((joystick.joy1_x2 * manualDriveScale) * 0.75) : 0;

		motor [frontLeft] = y1 + x2 + x1;
		motor [frontRight] = y1 - x2 - x1;
		motor [rearLeft] = y1 + x2 - x1;
		motor [rearRight] = y1 - x2 + x1;
		//pivot control
		//if (joystick.joy2_y1 > 110 || joystick.joy2_y2 > 110)
		//	if (coverTarget < 1000)
		//{
		//	coverTarget += coverIncrement;
		//	setCover(coverTarget/1000.0);
		//}
		//if (joystick.joy2_y1 < -110 || joystick.joy2_y2 < -110)
		//	if (coverTarget > 0)
		//{
		//	coverTarget -= coverIncrement;
		//	setCover(coverTarget/1000.0);
		//}
		if (joystick.joy2_y1 > 110 || joystick.joy2_y2 > 110)
		{
			servo [pivot] = 66;
		}
		if (joystick.joy2_y1 < -110 || joystick.joy2_y2 < -110)
		{
			servo [pivot] = 248;
		}
		if (joystick.joy2_x1 < -110 || joystick.joy2_x1 > 110 || joystick.joy2_x2 < -110 || joystick.joy2_x2 > 110)
		{
			servo [pivot] = 125;
		}
		//arm control
		if (joy2Btn(5) == 1) {
			motor [lift] = 100 /*- liftPrecisionFactor*/;
		}
		else if (joy2Btn(7) == 1) {
			motor [lift] = -100 /*+ liftPrecisionFactor*/;
		}
		else {
			motor [lift] = 0;
		}
		if (joy2Btn(6) == 1)
		{
			motor [arm] = -50;
		}
		else if (joy2Btn(8) == 1)
		{
			motor [arm] = 50;
		}
		else
		{
			motor [arm] = 0;
		}
		if (joystick.joy2_TopHat == 6)
		{
			servo [leftHook] = 35;
			servo [rightHook] = 140;
		}
		else if (joystick.joy2_TopHat == 2)
		{
			servo [leftHook] = 168;
			servo [rightHook] = 16;
		}

		if (joy2Btn(1) == 1 || joy2Btn(3) == 1)
		{
			while (joy2Btn(1) == 1 || joy2Btn(3) == 1)
			{
			}
			score(90);
		}
		if (joy2Btn(4) == 1)
		{
			while (joy2Btn(4) == 1)
			{
			}
			score(120);
		}

		if (joystick.joy2_TopHat == 4)
		{
			motor [sweeper] = -40;
		}
		else if (joystick.joy2_TopHat == 0)
		{
			motor [sweeper] = 60;
		}
		else
		{
			motor [sweeper] = 0;
		}
		if (joy2Btn(9) == 1)
		{
			servo [doors] = 122;
		}
		else if (joy2Btn(10) == 1)
		{
			servo [doors] = 0;
		}
		if (joy2Btn(2) == 1)
		{
			servo [pivot] = 255;
		}
		if (joy2Btn(1) == 1 || joy2Btn(3) == 1)
		{
			servo [pivot] = 125;
		}
		if (joy2Btn(4) == 1)
		{
			servo [pivot] = 66;
		}
	}
}
