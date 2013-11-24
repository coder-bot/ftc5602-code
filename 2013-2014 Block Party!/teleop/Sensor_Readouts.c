#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTSPB,          sensorCustom9V)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
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

#include <drivers/hitechnic-sensormux.h>
#include <drivers/hitechnic-superpro.h>
#include <drivers/lego-touch.h>
#include <drivers/lego-ultrasound.h>
#include <drivers/lego-light.h>
#include <drivers/hitechnic-irseeker-v2.h>

const tMUXSensor lineFollower = msensor_S3_3;

task main ()
{
	while (1)
	{
		//nxtDisplayCenteredBigTextLine(3, "%d", SensorValue [irSensor]);
		nxtDisplayCenteredBigTextLine(3, "%d", LSvalNorm(lineFollower));
		nxtDisplayCenteredBigTextLine(3, "%d",
	}
}
