#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     sweeper,       tmotorTetrix, openLoop)
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

task main()
{
	phase = AUTO;
	driveCycles = 6;
	humor = 80;
	bDisplayDiagnostics = false;
	initializeAutonomous();
	bDisplayDiagnostics = true;
	waitForStart();
	motor [lift] = 100;
	wait1Msec(750);
	motor [lift] = 0;
	wait1Msec(250);
	while (nMotorEncoder [frontRight] > -(driveCycles * driveEncoderCycle))
	{
		drive(0, -25, 0);
	}
	while (SensorValue [sonar] > 50)
	{
		drive(0, 0, 25);
	}
	wait1Msec(550);
	allStop();
	StartTask(failSafe);
	while (SensorValue [sonar] > 20)
	{
		drive(0, -20, 0);
	}
	StopTask(failSafe);
	wait1Msec(500);
	allStop();
	servo [leftHook] = 168;
	servo [rightHook] = 16;
	wait1Msec(50);
	score(60);
	wait1Msec(200);

	drive(0, 0, -100);
	motor [arm] = 100;
	servo [pivot] = 245;
	wait1Msec(1000);
	motor [arm] = 0;
	wait1Msec(500);
	allStop();
	wait1Msec(50);
	drive(-100, 0, 0);
	wait1Msec(1700);
	drive(0, -100, 0);
	wait1Msec(4500);
	allStop();
}
