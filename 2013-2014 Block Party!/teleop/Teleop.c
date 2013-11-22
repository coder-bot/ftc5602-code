#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTSPB,          sensorCustom9V)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     flagArm,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     grabberArm,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    grabber,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    latchOne,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    latchTwo,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

#include <JoystickDriver.c>
#include <drivers/hitechnic-sensormux.h>
#include <drivers/hitechnic-superpro.h>
#include <drivers/lego-touch.h>
#include <drivers/lego-ultrasound.h>
#include <drivers/lego-light.h>
#include <drivers/hitechnic-irseeker-v2.h>

const int threshold = 12;
const int wristLowTarget = 0;
const int wristHighTarget = 255;
int wristTarget = 0;
const int wristIncrement = 1;
int grabberLowTarget = 0;
int grabberHighTarget = 255;
int grabberTarget = 0;
const int grabberIncrement = 2;
//int lastOutput = 0x00;
//void setGrabber (float grabberSetting);
//void setWrist (float wristSetting);

const tMUXSensor sonarSensor = msensor_S3_1;
//const tMUXSensor irSensor = msensor_S3_2;
const tMUXSensor lineFollower = msensor_S3_3;


void setWrist (float wristSetting)
{
	servo [wrist] = wristHighTarget + ((wristLowTarget - wristHighTarget) * wristSetting);
	servo [wrist] = wristHighTarget + ((wristHighTarget - wristLowTarget) * wristSetting);
}

void setGrabber (float wristSetting)
{
	servo [grabber] = wristHighTarget + ((wristLowTarget - wristHighTarget) * wristSetting);
	servo [grabber] = wristHighTarget + ((wristHighTarget - wristLowTarget) * wristSetting);
}

void initializeRobot()
{
	servo [wrist] = 100;
	servo [grabber] = 100;
}

task main ()
{
	int grabberTarget = 0;
	int wristTarget = 0;
	initializeRobot();
	while (1)
	{
		getJoystickSettings(joystick);
	motor [leftDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y1 : 0;
	motor [rightDrive] = abs(joystick.joy1_y2) > threshold ? joystick.joy1_y2 : 0;
		if (joy2Btn(5) == 1) {
			motor [grabberArm] = 80;
		}
		else if (joy2Btn(7) == 1) {
			motor [grabberArm] = -80;
			} else {
			motor [grabberArm] = 0;
		}

		if (joy2Btn(6) == 1) {
			motor [lift] = 100;
			servo [latchOne] = 255;
			servo [latchTwo] = 255;
		}
#if 0
		else if (joy2Btn(8) == 1) {
			motor [lift] = -100;
			} else {
			motor [lift] = 0;
		}
#endif
		if (joystick.joy2_y1 > 110) {
			/*(joy2Btn (2) == 1)*/
			if (wristTarget > 0)
			{
				wristTarget -= wristIncrement;
				setWrist (wristTarget/1000.0);
			}
		}
		if (joystick.joy2_y1 <-110) {
			/*(joy2Btn (4) == 1)*/
			if (wristTarget <1000)
			{
				wristTarget += wristIncrement;
				setWrist (wristTarget/1000.0);
			}
		}

		if (joystick.joy2_y2 >110) {
			/*(joy2Btn (2) == 1)*/
			if (grabberTarget >0)
			{
				grabberTarget -= grabberIncrement;
				setGrabber(grabberTarget/1000.0);
			}
		}
		if (joystick.joy2_y2 <-110) {
			/*(joy2Btn (4) == 1)*/
			if (grabberTarget <1000)
			{
				grabberTarget += grabberIncrement;
				setGrabber(grabberTarget/1000.0);
			}
		}
#if 0
		if (joy2Btn(6) == 1) {
			servo [wrist] = 100;
		}
		else if (joy2Btn(8) == 1) {
			servo [wrist] = 25;
		}
		if (joy2Btn(5) == 1) {
			servo [grabber] = 150;
		}
		else if (joy2Btn(7) == 1) {
			servo [grabber] = 0;
		}
#endif
#if 0
		if (joy2Btn(5) == 1) {
			if (wristTarget < 1000) {
				wristTarget += wristIncrement;
				servo [wrist] = wristTarget;
			}
		}
		else if (joy2Btn(7) == 1) {
			if (wristTarget > 0) {
				wristTarget -= wristIncrement;
				servo [wrist] = wristTarget;
			}
		}
		if (joy2Btn(6) == 1) {
			if (grabberTarget > 0) {
				grabberTarget -= grabberIncrement;
				setGrabber(grabberTarget/1000.0);
			}
		}
		else if (joy2Btn(8) == 1) {
			if (grabberTarget < 1000)	{
				grabberTarget += grabberIncrement;
				setGrabber(grabberTarget/1000.0);
			}
		}
#endif
#if 0
		if (joy2Btn(2) == 1) {
			motor [flagArm] = 50;
		}
		else if (joy2Btn(3) == 1) {
			motor [flagArm] = -50;
			} else {
			motor [flagArm] = 0;
		}
#endif
	}
}
