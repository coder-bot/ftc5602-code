#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rearRight,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     frontRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    guiderDrop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    pivot,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    spinner,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <JoystickDriver.c>

int driveEncoderCycle = 1120;
float autoDriveScale = 0.7777;
//int pivotTarget = 1000;
//const int pivotIncrement = 1;

//void setPivot(float pivotSetting)
//{
//	servo [pivot] = 255 * pivotSetting;
//}

int resetDriveEncoders()
{
	nMotorEncoder [frontLeft] = 0;
	nMotorEncoder [frontRight] = 0;
	nMotorEncoder [rearLeft] = 0;
	nMotorEncoder [rearRight] = 0;
	return 1;
}

void initializeRobot()
{
	bDisplayDiagnostics = false;
	nxtDisplayCenteredTextLine(3, "Initializaing");
	nxtDisplayCenteredTextLine(4, "servos...");
	servo [pivot] = 0;
	servo [spinner] = 128;
	servo [guiderDrop] = 255;
	servo [leftHook] = 22;
	servo [rightHook] = 209;
	wait1Msec(1000);
	eraseDisplay();
	if (resetDriveEncoders() == 1)
	{
		nxtDisplayCenteredTextLine(3, "Encoders");
		nxtDisplayCenteredTextLine(4, "successfully");
		nxtDisplayCenteredTextLine(5, "reset.");
		wait1Msec(1000);
	}
	eraseDisplay();
	bDisplayDiagnostics = true;
}

task main ()
{
	initializeRobot();
	waitForStart();

}
