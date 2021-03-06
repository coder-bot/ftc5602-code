#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTSMUX,  sensorI2CCustom)
#pragma config(Sensor, S3,     HTSPB,   sensorI2CCustom9V)
#pragma config(Sensor, S4,     irSeeker,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     linearSlides,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     grabberMount,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     rearRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    wristMain,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    seekerPivot,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    rampLatch,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/lego-touch.h"

//const int rampLatchOpen=0;
const int rampLatchClosed=175;

const int seekerUp=255;
//const int seekerDown=20;

const int lineGray = 29;
const int lineBlack = 25;
const int lineWhite = 40;

const int speed= 65;

const tMUXSensor lineFollower = msensor_S2_1;
const tMUXSensor liftDownSensor = msensor_S2_2;
const tMUXSensor liftUpSensor = msensor_S2_3;
const tMUXSensor ultrasound = msensor_S2_4;


//int wristTarget = 0;
//const int wristIncrement = 1;
//These are the constant integers used for setting the high and low values for the wrist servos.
const int wristLowTarget = 0;
const int wristHighTarget = 255;

const float driveScale = 0.8;


void drive(int x1, int y1, int x2)
{
	motor[frontLeft] = (y1 + x2 + x1) * driveScale;
	motor[frontRight] = (y1 - x2 - x1) * driveScale;
	motor[rearLeft] = (y1 + x2 - x1) * driveScale;
	motor[rearRight] = (y1 - x2 + x1) * driveScale;
}

void raiseElevator ( )
{
	while (!TSreadState (liftUpSensor))
		motor [linearSlides]=100;
	motor [linearSlides]=0;
}

void rotateToBeacon ( )
{

	while (true){
		if (HTIRS2readACDir(irSeeker)< 5)
			drive (0,0, -speed);
		else if (HTIRS2readACDir(irSeeker)> 5)
			drive (0, 0, speed);
		else
		{
			drive (0,0,0);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void setWrist (float wristSetting)
{
	servo [wristMain] = wristHighTarget + ((wristLowTarget - wristHighTarget) * wristSetting);
	servo [wristMain] = wristHighTarget - ((wristHighTarget - wristLowTarget) * wristSetting);
}

void initializeRobot()
{
	LSsetActive(lineFollower);
	setWrist (.95);
	while (!TSreadState (liftDownSensor))
		motor [linearSlides]=-100;
	motor [linearSlides]=0;
	servo [rampLatch] = rampLatchClosed;
	servo [seekerPivot]= seekerUp;
	HTIRS2setDSPMode(irSeeker, DSP_1200);
	wait1Msec (500);


	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////




task main()
{
	initializeRobot();
	waitForStart(); // Wait for the beginning of autonomous phase.


	/*	while ( LSvalNorm(lineFollower) > 27 && LSvalNorm(lineFollower) < 35 ) {
	drive(0,speed,0);
	wait1Msec(20);
	}
	wait1Msec (800);
	drive(0,0,0); */
	//drive onto platform.
	drive (0, speed, 0);
	wait1Msec (300);
	while (LSvalNorm (lineFollower) > lineBlack) {
		drive (0, 0, 0);
		rotateToBeacon ( );
		drive (0, speed, 0);
		wait1Msec (200);
	}
	drive (0,speed,0);
	wait1Msec (200);
	drive (0,0,0);

	//find line

	while ((LSvalNorm (lineFollower) < lineWhite) && (LSvalNorm (lineFollower) > lineGray))
	{
		if (HTIRS2readACDir(irSeeker)< 5)
			drive (speed,0,0);
		else if (HTIRS2readACDir(irSeeker)> 5)
			drive (-speed, 0, 0);
	wait1Msec (200);
	}

drive (0,0,0);

setWrist (.6);

	/*motor [linearSlides]=100;
	wait1Msec (3300); //BOTTOM ROW
	motor [linearSlides]= 0;*/


	while (true)
	{}
}
