#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     lineFollower,   sensorLightActive)
#pragma config(Sensor, S4,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     grabberArm,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     spinnerArm,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    grabber,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    leftLatch,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)

#define STARTING_SIDE LEFT_SIDE

#include "Autonomous.h"

task main ()
{
	initializeRobot();
	waitForStart();

	if (STARTING_SIDE == LEFT_SIDE) {
		leftScanForBeacon();
	}
	else if (STARTING_SIDE == RIGHT_SIDE) {
		rightScanForBeacon();
	}
	alignWithBeacon();
	driveToBeacon(36);
	placeBlock();
#if 0
	driveOntoRamp();
#endif
}
