#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
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
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    flagLift,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

//Timer Usage (Important):
//T1 - RESERVED - fail-safe timer that shuts down program if it is taking too long e.g. motors are burning out from ramming another robot unintentionally
//T2 - RESERVED - time taken for arm to move to place block AND time taken for robot to align into proper position for bridge-parking
//T3 - RESERVED - time taken for robot to make parallel movement onto bridge
//T4 - AVAILIBLE

#pragma once
#include "Autonomous-Scraps.h"

//deterimine the maximum time it should take to accomplish these function-driven tasks
#define BEACON_ALIGNMENT_MAX 5000
#define BLOCK_PLACEMENT_MAX 5000

task main()
{
	waitForStart();
	ClearTimer(T1);
	alignWithBeacon();
	if (time1[T1] > BEACON_ALIGNMENT_MAX) {
		return;
	}
	ClearTimer(T1);
	placeBlock();
	if (time1[T1] > BLOCK_PLACEMENT_MAX) {
		return;
	}
	parkOnBridge();
}
