#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     grabberArm,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     rightLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_1,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C3_2,     rearRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    leftLatch,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    scoopCover,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    spinnerLift,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma once
#include "Autonomous-Scraps-SMUX-Beta.h"

task main()
{
	bDisplayDiagnostics = false;
	initializeRobot();
	bDisplayDiagnostics = true;
	waitForStart();
	StartTask(masterTimer);
	wait1Msec(delayTime * 1000);
	if (placeBlockQuery == PLACE_BLOCK_YES) {
		alignWithBeacon();
		placeBlock();
	}
	parkOnBridge();
}
