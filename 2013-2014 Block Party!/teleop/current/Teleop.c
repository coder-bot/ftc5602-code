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
#pragma config(Servo,  srvo_S2_C1_1,    spinnerLift,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    rightLatch,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

//Main teleop program with holonomic drive and mechanism controls

#include <JoystickDriver.c>
#define DRIVE_MODE_STD 1
#define DRIVE_MODE_EG 2
#define MECH_MODE_STD 1
#define MECH_MODE_INVERTED 2

int driveMode, mechMode;

void switchDriveMode(int driveModeToSwitchTo)
{
	while (joy1Btn(1) == 1 && joy1Btn(2) == 1 && joy1Btn(3) == 1 && joy1Btn(4) == 1)
	{
	}
	driveMode = driveModeToSwitchTo;
}

void switchMechMode(int mechModeToSwitchTo)
{
	while (joy2Btn(10) == 1)
	{
	}
	mechMode = mechModeToSwitchTo;
}

void initializeRobot()
{
	switchDriveMode(DRIVE_MODE_STD);
	switchMechMode(MECH_MODE_INVERTED);
}

task main ()
{
	initializeRobot();
	waitForStart();
	while (1)
	{
		getJoystickSettings(joystick);

		//Holonomic Drive Variables
		const int t = 8;
		const float standardDriveScale = 0.79;
		const float precisionDriveScale = 0.15;

	int	x1 = (abs(joystick.joy1_x1) > t) ? joystick.joy1_x1 : 0;
	int	y1 = (abs(joystick.joy1_y1) > t) ? joystick.joy1_y1 : 0;
	int	x2 = (abs(joystick.joy1_x2) > t) ? joystick.joy1_x2 : 0;
		//int y2 = (abs(joystick.joy1_y2) > t) ? joystick.joy1_y2 : 0;

		int stdFrontLeftMotorSetting = (- x1 - y1 + x2);
		int stdFrontRightMotorSetting = (x1 - y1 - x2);
		int stdRearLeftMotorSetting = (x1 - y1 + x2);
		int stdRearRightMotorSetting = (- x1 - y1 - x2);

		int egFrontLeftMotorSetting = x2;
		int egFrontRightMotorSetting = y1;
		int egRearLeftMotorSetting = y1;
		int egRearRightMotorSetting = x2;

		//Standard holonomic
		if (driveMode == DRIVE_MODE_STD) {
		motor [frontLeft] = ((joy1Btn (5) == 1) || (joy1Btn (6) == 1) || (joy1Btn (7) == 1) || (joy1Btn (8) == 1)) ? stdFrontLeftMotorSetting * precisionDriveScale : stdFrontLeftMotorSetting * standardDriveScale;
		motor [frontRight] = ((joy1Btn (5) == 1) || (joy1Btn (6) == 1) || (joy1Btn (7) == 1) || (joy1Btn (8) == 1)) ? stdFrontRightMotorSetting * precisionDriveScale : stdFrontRightMotorSetting * standardDriveScale;
		motor [rearLeft] = ((joy1Btn (5) == 1) || (joy1Btn (6) == 1) || (joy1Btn (7) == 1) || (joy1Btn (8) == 1)) ? stdRearLeftMotorSetting * precisionDriveScale : stdRearLeftMotorSetting * standardDriveScale;
		motor [rearRight] = ((joy1Btn (5) == 1) || (joy1Btn (6) == 1) || (joy1Btn (7) == 1) || (joy1Btn (8) == 1)) ? stdRearRightMotorSetting * precisionDriveScale : stdRearRightMotorSetting * standardDriveScale;
		}
		else if (driveMode == DRIVE_MODE_EG) {
		motor [frontLeft] = (egFrontLeftMotorSetting * precisionDriveScale - ((joy1Btn(1) == 1) ? 20 : (joy1Btn(3) == 1) ? -20 : 0));
		motor [frontRight] = (egFrontRightMotorSetting * precisionDriveScale + ((joy1Btn(1) == 1) ? 20 : (joy1Btn(3) == 1) ? -20 : 0));
		motor [rearLeft] = (egRearLeftMotorSetting * precisionDriveScale - ((joy1Btn(1) == 1) ? 20 : (joy1Btn(3) == 1) ? -20 : 0));
		motor [rearRight] = (egRearRightMotorSetting * precisionDriveScale + ((joy1Btn(1) == 1) ? 20 : (joy1Btn(3) == 1) ? -20 : 0));
		}

		if (joy1Btn(1) == 1 && joy1Btn(2) == 1 && joy1Btn(3) == 1 && joy1Btn(4) == 1) {
			if (driveMode == DRIVE_MODE_STD) {
				switchDriveMode(DRIVE_MODE_EG);
			}
			else if (driveMode == DRIVE_MODE_EG) {
				switchDriveMode(DRIVE_MODE_STD);
			}
		}

		if (joy2Btn(10) == 1) {
			if (mechMode == MECH_MODE_STD) {
				switchMechMode(MECH_MODE_INVERTED);
			}
			else if (mechMode == MECH_MODE_INVERTED) {
				switchMechMode(MECH_MODE_STD);
			}
		}
		if (mechMode == MECH_MODE_STD) {
			if (joy2Btn(7) == 1) {
				motor [grabberArm] = -100;
			}
			else if (joy2Btn(5) == 1) {
				motor [grabberArm] = 100;
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
		}
		else if (mechMode == MECH_MODE_INVERTED) {
			if (joy2Btn(7) == 1) {
				motor [grabberArm] = 100;
			}
			else if (joy2Btn(5) == 1) {
				motor [grabberArm] = -100;
				} else {
				motor [grabberArm] = 0;
			}

			if (joy2Btn(6) == 1) {
				motor [leftLift] = -100;
				motor [rightLift] = -100;
			}
			else if (joy2Btn(8) == 1) {
				motor [leftLift] = 100;
				motor [rightLift] = 100;
				} else {
				motor [leftLift] = 0;
				motor [rightLift] = 0;
			}
		}

		if (joy2Btn(6) != 1 && joy2Btn(8) != 1) {
		motor [leftLift] = abs(joystick.joy2_y1) > t ? joystick.joy2_y1 * standardDriveScale : 0;
		motor [rightLift] = abs(joystick.joy2_y2) > t ? joystick.joy2_y2 * standardDriveScale : 0;
		}

		if (joystick.joy2_TopHat == 4) {
			servo [leftLatch] = 0;
			servo [rightLatch] = 235;
		}
		else if (joystick.joy2_TopHat == 0) {
			servo [leftLatch] = 218;
			servo [rightLatch] = 30;
		}

		if (joy2Btn(1) == 1) {
			motor [flagSpinner] = -100;
		}
		else if (joy2Btn(3) == 1) {
			motor [flagSpinner] = 100;
			} else {
			motor [flagSpinner] = 0;
		}

		if (joy2Btn(2) == 1) {
			servo [spinnerLift] = 255;
		}
		else if (joy2Btn(4) == 1) {
			servo [spinnerLift] = 0;
			} else {
			servo [spinnerLift] = 127;
		}
	}
}