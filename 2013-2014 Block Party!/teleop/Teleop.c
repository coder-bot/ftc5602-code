#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     rearRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     rightLift,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     grabberArm,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     leftLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_1,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_2,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    flagLift,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    leftLatch,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

//#pragma config(Sensor, S2,     HTSPB,   sensorI2CCustom9V)

#include <JoystickDriver.c>
#include <drivers/hitechnic-superpro.h>
//#include <drivers/hitechnic-sensormux.h>
//#include <drivers/lego-touch.h>
//#include <drivers/lego-ultrasound.h>
//#include <drivers/lego-light.h>
//#include <drivers/hitechnic-irseeker-v2.h>

const int threshold = 10;

//Holonomic Drive Variables
int x1, y1, x2;
const int t = 8;
const float standardDriveScale = 0.95;
const float precisionDriveScale = 0.28;
int frontLeftMotorSetting = (x1 + y1 + x2);
int frontRightMotorSetting = (- x1 + y1 - x2);
int rearLeftMotorSetting = (- x1 + y1 + x2);
int rearRightMotorSetting = (x1 + y1 - x2);

//wrist and grabber targets/limits
int wristTarget = 0;
const int wristLowTarget = 0;
const int wristHighTarget = 255;
const int wristIncrement = 1;

int grabberTarget = 0;
const int grabberLowTarget = 0;
const int grabberHighTarget = 255;
const int grabberIncrement = 2;
const int grabberHighLimit = 950;

//makes wrist parallel to ground
const int idealWristSetting = 65;

//for lifting hook servos
const int rightClose = 15;
const int leftClose = 218;
const int rightOpen = 235;
const int leftOpen = 0;

//int lastOutput = 0x00;
//void setGrabber (float grabberSetting);
//void setWrist (float wristSetting);

//const tMUXSensor sonarSensor = msensor_S3_1;
//const tMUXSensor lineFollower = msensor_S3_3;

#if 0
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
#endif
void initializeRobot()
{
	servo [leftLatch] = 218 /*255, 210 originally*/;
	servo [rightLatch] = 30;
#if 0
	wristTarget = 900;
	setWrist(wristTarget/1000.);
	grabberTarget = 800;
	setGrabber(grabberTarget/1000.);
	servo [grabber] = 210 /*255, 210 originally*/;
	//#else
	servo [wrist] = 190;
	servo [grabber] = 235;
#endif
}

task main ()
{
	initializeRobot();
	waitForStart();
	while (1)
	{
		getJoystickSettings(joystick);
		/*tank drive
		motor [leftDrive] = abs(joystick.joy1_y1) > threshold ? joystick.joy1_y1 : 0;
		motor [rightDrive] = abs(joystick.joy1_y2) > threshold ? joystick.joy1_y2 : 0;
		*/

		//Holonomic Drive
	x1 = ( abs( joystick.joy1_x1 ) > t ) ? joystick.joy1_x1 : 0;
	y1 = ( abs( joystick.joy1_y1 ) > t ) ? joystick.joy1_y1 : 0;
	x2 = ( abs( joystick.joy1_x2 ) > t ) ? joystick.joy1_x2 : 0;

		//Main holonomic
	motor [frontLeft] = ((joy1Btn (1) == 1) || (joy1Btn (2) == 1) || (joy1Btn (3) == 1) || (joy1Btn (4) == 1)) ? frontLeftMotorSetting * precisionDriveScale : frontLeftMotorSetting * standardDriveScale;
	motor [frontRight] = ((joy1Btn (1) == 1) || (joy1Btn (2) == 1) || (joy1Btn (3) == 1) || (joy1Btn (4) == 1)) ? frontRightMotorSetting * precisionDriveScale : frontRightMotorSetting * standardDriveScale;
	motor [rearLeft] = ((joy1Btn (1) == 1) || (joy1Btn (2) == 1) || (joy1Btn (3) == 1) || (joy1Btn (4) == 1)) ? rearLeftMotorSetting * precisionDriveScale : rearLeftMotorSetting * standardDriveScale;
	motor [rearRight] = ((joy1Btn (1) == 1) || (joy1Btn (2) == 1) || (joy1Btn (3) == 1) || (joy1Btn (4) == 1)) ? rearRightMotorSetting * precisionDriveScale : rearRightMotorSetting * standardDriveScale;

		//Optimized driver controls for positioning prior to flag raising
		if (joy1Btn(1) == 1) {
			motor [frontLeft] = 50;
			motor [rearRight] = 50;
		}
		else if (joy1Btn(2) == 1) {
			motor [frontRight] = 50;
			motor [rearLeft] = 50;
		}
		else if (joy1Btn(3) == 1) {
			motor [frontLeft] = -50;
			motor [rearRight] = -50;
		}
		else if (joy1Btn(4) == 1) {
			motor [frontRight] = -50;
			motor [rearLeft] = -50;
			} else {
			motor [frontLeft] = 0;
			motor [frontRight] = 0;
			motor [rearLeft] = 0;
			motor [rearRight] = 0;
		}

#if 1
		if (joy2Btn(7) == 1) {
			motor [grabberArm] = 50;
		}
		else if (joy2Btn(5) == 1) {
			motor [grabberArm] = -50;
			} else {
			motor [grabberArm] = 0;
		}

		if (joy2Btn(6) == 1) {
			motor [leftLift] = 100;
			motor [rightLift] = 100;
		}
		else if (joy2Btn(8) == 1) {
			motor [leftLift] = -100;
			motor [rightLift] = -100;
			} else {
			motor [leftLift] = 0;
			motor [rightLift] = 0;
		}

		if (joystick.joy2_TopHat == 4) {
			servo [leftLatch] = 0;
			servo [rightLatch] = 235;
		}
		else if (joystick.joy2_TopHat == 0) {
			servo [leftLatch] = 218;
			servo [rightLatch] = 30;
		}

#if 0
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
			if (wristTarget < 1000)
			{
				wristTarget += wristIncrement;
				if (wristTarget > 1000)
					wristTarget = 1000;
				setWrist (wristTarget/1000.0);
			}
		}

		if (joystick.joy2_x2 < -110) {
			/*(joy2Btn (2) == 1)*/
			if (grabberTarget > 0)
			{
				grabberTarget -= grabberIncrement;
				if (grabberTarget < 0)
					grabberTarget = 0;
				setGrabber(grabberTarget/1000.0);
			}
		}
		if (joystick.joy2_x2 > 110) {
			/*(joy2Btn (4) == 1)*/
			if (grabberTarget < 1000)
			{
				grabberTarget += grabberIncrement;
				if (grabberTarget > grabberHighLimit)
					grabberTarget = grabberHighLimit;
				setGrabber(grabberTarget/1000.0);
			}
		}
#endif
#endif
		//code for setting wrist servo to "ideal" position
#if 0
		if (joy2Btn(2) == 1) {
			servo [wrist] = idealWristSetting;
		}
#endif
		//potentiometer code follows
#if 0
		//max range of potentiometer
		const int rMax = 1023;
		//min range of potentiometer
		const int rMin = 407;
		//protoboard location
		int inputdata = HTSPBreadADC(HTSPB, 2, 10);
		if (joy2Btn(9) == 1)
		{
			//manual override dump control from ring it up
			servo [wrist] = 255;
		}
		else {
			float wrist = (inputdata - rMin);
			wrist /= (rMax - rMin);
			//change the 275 and manual override control if necessary
			servo [wrist] = (275 * wrist) + ( joystick.joy2_y1 / 3);
		}
#endif
#if 1
#if 0
		if (joystick.joy2_TopHat == 4) {
			motor [spinnerArm] = -30;
		}
		else if (joystick.joy2_TopHat == 0) {
			motor [spinnerArm] = 30;
			} else {
			motor [spinnerArm] = 0;
		}
#endif
		if (joy2Btn(1) == 1) {
			motor [flagSpinner] = 100;
		}
		else if (joy1Btn(3) == 1) {
			motor [flagSpinner] = -100;
			} else {
			motor [flagSpinner] = 0;
		}
		if (joy2Btn(2) == 1) {
			servo [flagLift] = 255;
		}
		else if (joy2Btn(4) == 1) {
			servo [flagLift] = 0;
			} else {
			servo [flagLift] = 127;
		}
#endif
	}
}
