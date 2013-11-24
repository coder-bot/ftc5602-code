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

#include <JoystickDriver.c>
//#include <drivers/hitechnic-sensormux.h>
//#include <drivers/hitechnic-superpro.h>
//#include <drivers/lego-touch.h>
//#include <drivers/lego-ultrasound.h>
//#include <drivers/lego-light.h>
//#include <drivers/hitechnic-irseeker-v2.h>

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

//const tMUXSensor sonarSensor = msensor_S3_1;
//const tMUXSensor lineFollower = msensor_S3_3;

void setWrist (float wristSetting)
{
	//servo [wrist] = wristHighTarget + ((wristLowTarget - wristHighTarget) * wristSetting);
	servo [wrist] = wristLowTarget + ((wristHighTarget - wristLowTarget) * wristSetting);
}

void setGrabber (float grabberSetting)
{
	//servo [grabber] = grabberHighTarget + ((grabberLowTarget - grabberHighTarget) * grabberSetting);
	servo [grabber] = grabberLowTarget + ((grabberHighTarget - grabberLowTarget) * grabberSetting);
}

void initializeRobot()
{
	servo [leftLatch] = 255;
	servo [rightLatch] = 0;
#if 1
	wristTarget = 900;
	setWrist(wristTarget/1000.);
	grabberTarget = 1000;
	setGrabber(grabberTarget/1000.);
#else
	servo [wrist] = 127;
	servo [grabber] = 127;
#endif
}

task main ()
{
	initializeRobot();

	while (1)
	{
#if 1
		getJoystickSettings(joystick);
	motor [leftDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y1 : 0;
	motor [rightDrive] = abs(joystick.joy1_y2) > threshold ? joystick.joy1_y2 : 0;
		if (joy2Btn(8) == 1) {
			motor [grabberArm] = 50;
		}
		else if (joy2Btn(6) == 1) {
			motor [grabberArm] = -50;
			} else {
			motor [grabberArm] = 0;
		}
		if (joy2Btn(5) == 1) {
			motor [lift] = 100;
		}
		else if (joy2Btn(7) == 1) {
			motor [lift] = -100;
			} else {
			motor [lift] = 0;
		}

		if (joy2Btn(3) == 1) {
			servo [leftLatch] = 0;
			servo [rightLatch] = 255;
		}
		else if (joy2Btn(1) == 1) {
			servo [leftLatch] = 255;
			servo [rightLatch] = 0;
		}

		if (joystick.joy2_y1 < -110) {
			/*(joy2Btn (2) == 1)*/
			if (wristTarget > 0)
			{
				wristTarget -= wristIncrement;
				if (wristTarget < 0)
					wristTarget = 0;
				setWrist (wristTarget/1000.0);
			}
		}
		if (joystick.joy2_y1 > 110) {
			/*(joy2Btn (4) == 1)*/
			if (wristTarget <1000)
			{
				wristTarget += wristIncrement;
				if (wristTarget > 1000)
					wristTarget = 1000;
				setWrist (wristTarget/1000.0);
			}
		}

		if (joystick.joy2_x2 > 110) {
			/*(joy2Btn (2) == 1)*/
			if (grabberTarget > 0)
			{
				grabberTarget -= grabberIncrement;
				if (grabberTarget < 0)
					grabberTarget = 0;
				setGrabber(grabberTarget/1000.0);
			}
		}
		if (joystick.joy2_x2 < -110) {
			/*(joy2Btn (4) == 1)*/
			if (grabberTarget < 1000)
			{
				grabberTarget += grabberIncrement;
				if (grabberTarget > 1000)
					grabberTarget = 1000;
				setGrabber(grabberTarget/1000.0);
			}
		}
#endif
#if 1
		if (joystick.joy2_TopHat == 0) {
			motor [spinnerArm] = 50;
		}
		else if (joystick.joy2_TopHat == 4) {
			motor [spinnerArm] = -50;
			} else {
			motor [spinnerArm] = 0;
		}
		if (joystick.joy2_TopHat == 2) {
			motor [flagSpinner] = 100;
		}
		else if (joystick.joy2_TopHat == 6) {
			motor [flagSpinner] = -100;
			} else {
			motor [flagSpinner] = 0;
		}
#endif
	}
}
