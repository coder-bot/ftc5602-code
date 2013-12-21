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

const int threshold = 12;
const int wristLowTarget = 0;
const int wristHighTarget = 255;
int wristTarget = 0;
const int wristIncrement = 1;
int grabberLowTarget = 0;
int grabberHighTarget = 255;
int grabberTarget = 0;
const int grabberIncrement = 2;

const int spinnerArmSpeed = 40;

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

task main()
{
	initializeRobot();
	waitForStart();
	while (1)
	{
		//motor [spinnerArm] = abs(joystick.joy2_y1) > threshold ? joystick.joy2_y1 : 0;
		if (joystick.joy2_TopHat == 4) {
			motor [spinnerArm] = spinnerArmSpeed;
		}
		else if (joystick.joy2_TopHat == 0) {
			motor [spinnerArm] = -1 * spinnerArmSpeed;
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
	}
}
