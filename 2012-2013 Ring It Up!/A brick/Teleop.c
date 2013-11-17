#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTSMUX,  sensorI2CCustom)
#pragma config(Sensor, S3,     HTSPB,   sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     linearSlides,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     grabberMount,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     rearRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    wristMain,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    grabberRight,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    grabberLeft,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    irPivot,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    rampLatch,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*Welcome to the world of robotics. Once upon a time, there was a robot named Geary Cathoirmore, which lived with FTC Team #5602,
the Bionic Gaels. Here is the story and life instructions for Geary, written in the wonderful programming language of C. */

/* This is the Bionic Gaels' (FTC Team #5602) teleop program for Ring It Up (FTC 2012).
The holonomic drive was programmed by our mentor, Mr. Higham. The grabber apparatus and linear slides were programmed by Max,
with help from Mr. Higham in writing the equations found below the initial comments. */

/* Robot Summary */

/* Our robot contains a holonomic drive system with eight 4-inch omni wheels in total (two on each corner), and
four TETRIX motors.
It also has four linear slides, staggered in pairs of two, that lift the ring grabber apparatus up to the second
and third peg level. These are powered by a TETRIX motor connected to gears, a chain, and a rope.
The ring grabber apparatus consists of a motorized arm (two TETRIX channels connected by gears and attatched
to a motor), the wrist (two servos working in unison to raise and lower the grabber; the wrist is mounted on the arm),
and the grabber itself consists of two servo motors each moving a curved piece of aluminum with rubber secured to it.
This grasps the rings securly. Update: We are no longer using the servo-operated grabber because the passive system
seems to work much better. However, the servo-operated system is our backup plan if the passive system fails. */

/* Skylar is currently working on a bagel-slicer type gripper design. We will work on implementing this passive system
soon. Update: We are now using this system and it works quite well. */

//Go Bionic Gaels!
#include "JoystickDriver.c";
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-touch.h"


const tMUXSensor liftUpSensor = msensor_S2_3;
const tMUXSensor liftDownSensor = msensor_S2_2;

//These are the integers for setting the values for the wrist's servo motors.
int wristTarget = 950;
const int wristIncrement = 1;
//These are the constant integers used for setting the high and low values for the wrist servos.
const int wristLowTarget = 0;
const int wristHighTarget = 255;
//These are the integers for setting the values for the grabber's servo motors.
int grabberTarget = 0;
const int grabberIncrement = 2;
//These are the constant integers used for setting the opened and closed values for the grabber servos.
const int rightOpen = 255;
const int rightClose = 127;
const int leftOpen = 0;
const int leftClose = 127;
//These are the integers used for setting the values of the ramp deployment servos.
const int rampLatchOpen=0;
const int rampLatchClosed=175;

void setGrabber (float grabberSetting)
{

	servo [grabberLeft] = leftOpen + ((leftClose - leftOpen) * grabberSetting) ;
	servo [grabberRight] = rightOpen - ((rightOpen - rightClose) * grabberSetting);


}

void setWrist (float wristSetting)
{
	servo [wristMain] = wristHighTarget + ((wristLowTarget - wristHighTarget) * wristSetting);
	servo [wristMain] = wristHighTarget - ((wristHighTarget - wristLowTarget) * wristSetting);
}


/*void deployRamp (int latchSetting)

{
servo [rampLatch] = latchSetting;
} */

void initializeRobot ()

{
	setGrabber (grabberTarget/100.0);
	setWrist (wristTarget/1000.0);
	/* If the wrist is moving too quickly try changing the divisor in the setWrist equation from 1000.0 to 10000.0;
	this will not make a huge difference, but it's worth a try. */
	servo [rampLatch] = rampLatchClosed;
}

task main()
{
	//Holonomic Drive Integers
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	const int t = 8;
	const float driveScale = 0.7;

	initializeRobot ();

	while ( true ) {

		getJoystickSettings(joystick);

		//Holonomic Drive

	x1 = ( abs( joystick.joy1_x1 ) > t ) ? joystick.joy1_x1 : 0;
	y1 = ( abs( joystick.joy1_y1 ) > t ) ? joystick.joy1_y1 : 0;
	x2 = ( abs( joystick.joy1_x2 ) > t ) ? joystick.joy1_x2 : 0;

		motor[frontLeft] = (y1 + x2 + x1) * driveScale;
		motor[frontRight] = (y1 - x2 - x1) * driveScale;
		motor[rearLeft] = (y1 + x2 - x1) * driveScale;
		motor[rearRight] = (y1 - x2 + x1) * driveScale;


		//This is the code for controlling the motorized linear slides that the ring grabber appparatus is mounted on.
		//Up

		if ((joy2Btn (5) == 1) && (TSreadState(liftUpSensor) == 0))
		{
			motor [linearSlides] = 100;

		}

		//Down; after the button statement is the sensor value statement so the lift doesn't go too far down.
		else if ((joy2Btn (7) == 1) && (TSreadState(liftDownSensor) == 0 ))   {
			motor [linearSlides] = -100;
		}
		else motor [linearSlides] = 0;

		//The following is the code for controlling the ring grabber apparatus.
		//This is the code for controlling the arm that the grabber is mounted on.

		if (joy2Btn (6) == 1 ) {
			motor [grabberMount] = 50;
		}

		else if (joy2Btn (8) == 1) {
			motor [grabberMount] = -50;
		}

		else motor [grabberMount] = 0;

		/* The following is the other arm code; this allows the arm to be controlled with the joysticks (in addition to
		the buttons. */


		//motor [grabberMount] = (-(abs( joystick.joy2_y2 ) > t ) ? joystick.joy2_y2 : 0 );


		//This is the code for controlling the grabber itself. It is 'commented' out because we currently do not use the 'active' grabber.

		/*
		if (joystick.joy2_x2 >110)
		/*(joy2Btn (1) == 1)*/
		/*	if (grabberTarget >0)
		{
		grabberTarget -= grabberIncrement;
		setGrabber (grabberTarget/100.0);
		}

		if (joystick.joy2_x2 <-110)
		/*(joy2Btn (3) == 1)*/
		/*	if (grabberTarget <100)
		{
		grabberTarget += grabberIncrement;
		setGrabber (grabberTarget/100.0);
		} */

		//This is the code for controlling the wrist, which the grabber is attatched to.

		if (joystick.joy2_y1 >110)
			/*(joy2Btn (2) == 1)*/
		if (wristTarget >0)
		{
			wristTarget -= wristIncrement;
			setWrist (wristTarget/1000.0);
		}
		if (joystick.joy2_y1 <-110)
			/*(joy2Btn (4) == 1)*/
		if (wristTarget <1000)
		{
			wristTarget += wristIncrement;
			setWrist (wristTarget/1000.0);
		}

		//Insert code for LED weight sensor behavior.

		/* Perhaps we will switch to this function system at the next meeting or possible time. Uncomment below,
		the 'deployRamp' function above, and the latchSetting varible declaration. */

		/* if ((joy1Btn (10) == 1) && (joy2Btn (10) == 1))

		{
		deployRamp (180);
		} */



		/*This conditional statement releases the ramp latch for the end game. Both 'start' buttons must be
		pressed to release the ramp latch. The button combination that must be pressed is intentionally awkward
		so that the ramp is not deployed by accident during the first 90 seconds of the teleop phase. */

		/* Also, below there is (commented out) the or operator and an additional button combination in which
		both drivers press all four colored buttons on the right side of the joysticks to deploy the ramp;
		this is not currently implemented because it has not been tested and proven to work. */


		if /*(*/((joy1Btn (10) == 1) && (joy2Btn (10) == 1)) /* || ((joy1Btn (1) == 1) && (joy1Btn (2) == 1) &&
			(joy1Btn (3) == 1) && (joy1Btn (4) == 1) && (joy2Btn (1) == 1) && (joy2Btn (2) == 1) &&
		(joy2Btn (3) == 1) && (joy2Btn (4) == 1))) */

		{
			servo [rampLatch] = rampLatchOpen;
		}

	}
}

//And Geary Cathoirmore lived happily ever after.
//The end.
