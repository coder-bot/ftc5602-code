#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     rightLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_1,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C3_2,     rearRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    scoopCover,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    spinnerLift,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    leftLatch,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

//to test proper timed values for detecting if IR beacon is at the left or right pair of crates
#include "New_Auto_Header.h"

task main()
{
	waitForStart();
	ClearTimer(T3);
	while (SensorValue[irSensor] != 4)
	{
		if (SensorValue(sonarSensor) > blockPlacementDist) {
			drive(35, 35, 0);
		}
		else if (SensorValue(sonarSensor) < blockPlacementDist) {
			drive(35, -35, 0);
		}
		else if (SensorValue(sonarSensor) == blockPlacementDist) {
			drive(35, 0, 0);
		}
	}
	allStop();
	long time = time1[T3];
	bDisplayDiagnostics = false;
	nxtDisplayCenteredTextLine(3, "%d", time);
	wait1Msec(20000);

}
