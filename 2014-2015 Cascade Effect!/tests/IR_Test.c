#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rearRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    guiderDrop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    cover,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <JoystickDriver.c>
#include "Cascade_Functions.h"

task failSafe()
{
	ClearTimer(T1);
	while(1)
	{
		if (time1 [T1] > 3500)
		{
			StopAllTasks();
		}
	}
}

task main()
{
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
	if (SensorValue [ir] == 5)
	{
		//while (nMotorEncoder [frontRight] > -(driveCycles * driveEncoderCycle))
		//{
		//	drive(0, 25, 0);
		//}
		while (SensorValue [sonar] > 45)
		{
			drive(0, 100, 0);
		}
		allStop();
		//begin precision rotate cycle
		while (SensorValue [ir] > 4)
		{
			drive(0, 0, 60);
		}
		allStop();
		ClearTimer(T2);
		while (SensorValue [ir] < 6)
		{
			drive(0, 0, -60);
		}
		int spinTime = time1[T2];
		allStop();
		ClearTimer(T2);
		while (time1[T2] < spinTime)
		{
			drive(0, 0, 60);
		}
		allStop();
	}
}
//end precision rotate cycle

/*
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
wait1Msec(250);
motor [lift] = 100;
wait1Msec(950);
motor [lift] = 0;
wait1Msec(500);
motor [arm] = -100;
wait1Msec(2250);
motor [arm] = 0;
wait1Msec(500);
servo [cover] = 12;
wait1Msec(750);
servo [cover] = 160;
wait1Msec(250);
motor [arm] = 100;
wait1Msec(2000);
motor [arm] = 0;
wait1Msec(250);
motor [lift] = -100;
wait1Msec(800);
motor [lift] = 0;
wait1Msec(500);
drive(0, 0, -100);
wait1Msec(1500);
allStop();
wait1Msec(250);
drive(-100, 0, 0);
wait1Msec(1700);
drive(0, -100, 0);
wait1Msec(4500);
allStop();
//wait1Msec(250);
//drive(100, 0, 0);
//wait1Msec(2500);
//allStop();
}
*/