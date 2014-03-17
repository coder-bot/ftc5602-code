//holonomic autonomous for block party - header file containing functions for core/mech operations as well as bridge park procedure and initial configuration/map generation via the NXT screen and buttons

//Timer Usage (Important):
//T1 - RESERVED - fail-safe timer that shuts down program if it is taking too long e.g. motors are burning out from ramming another robot unintentionally
//T2 - RESERVED - time taken for arm to move to place block
//T3 - RESERVED - time taken for robot to execute movements to park on the bridge
//T4 - RESERVED - timer used to precisely set IR beacon alignment

#include <JoystickDriver.c>
#include <drivers/hitechnic-sensormux.h>
#include <drivers/lego-light.h>
#include <drivers/lego-ultrasound.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define PLACE_BLOCK_NO 0
#define PLACE_BLOCK_YES 1

int armMovementTime = 2250;
int blockPlacementDist = 38;
int cratesPassedDist = 100;
int bridgeMovementInitialDist = 45;
int bridgeAlignmentTime = 1500;
int bridgeParkTime = 2000;
int clearPendulumDelay = 350;
int startingSide, bridgeSide, placeBlockQuery, delayTime, reconfigure;

const tMUXSensor sonarSensor = msensor_S3_1;
//const tMUXSensor lightSensor = msensor_S3_2;

task masterTimer()
{
	ClearTimer(T1);
	while (1)
	{
		if (time1[T1] >= 25000) {
			StopAllTasks();
		}
	}
}

void initializeAutonomous();
void updateDelayTimeDisplay();
void generateAutonomousMap();

void initializeRobot()
{
	initializeAutonomous();
	servo [scoopCover] = 198;
}

void initializeAutonomous()
{
	eraseDisplay();
	delayTime = 0;
	nxtDisplayTextLine(2, "Block & bridge?");
	nxtDisplayTextLine(3, "Orange: both");
	nxtDisplayTextLine(4, "Arrow: bridge");
	while (1)
	{
		if (nNxtButtonPressed == 3) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			placeBlockQuery = PLACE_BLOCK_YES;
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "Both");
			wait1Msec(800);
			break;
		}
		else if (nNxtButtonPressed == 1 || nNxtButtonPressed == 2) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			placeBlockQuery = PLACE_BLOCK_NO;
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "Bridge only");
			wait1Msec(800);
			break;
		}
	}
	eraseDisplay();
	nxtDisplayCenteredTextLine(3, "Starting Side?");
	while (1)
	{
		if (nNxtButtonPressed == 1) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			startingSide = RIGHT_SIDE;
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "Right");
			wait1Msec(800);
			break;
		}
		else if (nNxtButtonPressed == 2) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			startingSide = LEFT_SIDE;
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "Left");
			wait1Msec(800);
			break;
		}
	}
	eraseDisplay();
	nxtDisplayCenteredTextLine(3, "Bridge side?");
	while (1)
	{
		if (nNxtButtonPressed == 1) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			bridgeSide = RIGHT_SIDE;
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "Right");
			wait1Msec(800);
			break;
		}
		else if (nNxtButtonPressed == 2) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			bridgeSide = LEFT_SIDE;
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "Left");
			wait1Msec(800);
			break;
		}
	}
	eraseDisplay();
	updateDelayTimeDisplay();
	while (1)
	{
		if (nNxtButtonPressed == 1) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			delayTime ++;
			updateDelayTimeDisplay();
		}
		else if (nNxtButtonPressed == 2) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			delayTime --;
			updateDelayTimeDisplay();
		}
		if (nNxtButtonPressed == 3) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "%d s", delayTime);
			wait1Msec(800);
			break;
		}
	}
	eraseDisplay();
	nxtDisplayCenteredTextLine(2, "Confirm options:");
	wait1Msec(500);
	if (placeBlockQuery == PLACE_BLOCK_YES)
		nxtDisplayTextLine(4, "Block & bridge");
	else if (placeBlockQuery == PLACE_BLOCK_NO)
		nxtDisplayTextLine(4, "Bridge only");
	wait1Msec(500);
	if (startingSide == LEFT_SIDE)
		nxtDisplayTextLine(5, "Start: Left");
	else if (startingSide == RIGHT_SIDE)
		nxtDisplayTextLine(5, "Start: Right");
	wait1Msec(500);
	if (bridgeSide == LEFT_SIDE)
		nxtDisplayTextLine(6, "End: Left");
	else if (bridgeSide == RIGHT_SIDE)
		nxtDisplayTextLine(6, "End: Right");
	wait1Msec(500);
	nxtDisplayTextLine(7, "Delay: %d s", delayTime);
	while (1)
	{
		if (nNxtButtonPressed == 3) {
			while (nNxtButtonPressed != (-1))
			{
			}
			reconfigure = 0;
			break;
		}
		else if (nNxtButtonPressed == 1 || nNxtButtonPressed == 2) {
			while (nNxtButtonPressed != (-1))
			{
			}
			reconfigure = 1;
			break;
		}
	}
	if (reconfigure)
		initializeAutonomous();
	else if (!reconfigure)
		generateAutonomousMap();
}

void updateDelayTimeDisplay()
{
	nxtDisplayCenteredTextLine(3, "Delay time: %d", delayTime);
}

void generateAutonomousMap()
{
	eraseDisplay();
	nxtDisplayCenteredTextLine(3, "Generating map...");
	wait1Msec(1500);
	eraseDisplay();
	nxtDisplayCenteredTextLine(1, "Delay: %d s", delayTime);
	wait1Msec(1000);
	nxtDrawRect(0, 63, 99, 0);
	wait1Msec(500);

	if (startingSide == LEFT_SIDE) {
		if (placeBlockQuery == PLACE_BLOCK_YES || bridgeSide == RIGHT_SIDE) {
			nxtDrawLine(14, 9, 50, 9);
		}
		if (placeBlockQuery == PLACE_BLOCK_YES) {
			wait1Msec(500);
			for (int i = 0; i < 2; i++)
			{
				nxtDisplayTextLine(3, "*Block is placed*");
				wait1Msec(600);
				nxtDisplayTextLine(3, "");
				nxtDrawRect(0, 63, 99, 0);
				wait1Msec(600);
			}
		}
		wait1Msec(500);
		if (bridgeSide == RIGHT_SIDE) {
			nxtDrawLine(50, 9, 85, 9);
			wait1Msec(500);
			nxtDrawLine(85, 9, 85, 32);
			wait1Msec(500);
			nxtDrawLine(85, 32, 50, 32);
			wait1Msec(500);
		}
		else if (bridgeSide == LEFT_SIDE) {
			nxtDrawLine(14, 9, 14, 32);
			wait1Msec(500);
			nxtDrawLine(14, 32, 50, 32);
			wait1Msec(500);
		}
	}
	else if (startingSide == RIGHT_SIDE) {
		if (placeBlockQuery == PLACE_BLOCK_YES || bridgeSide == LEFT_SIDE) {
			nxtDrawLine(85, 9, 50, 9);
		}
		if (placeBlockQuery == PLACE_BLOCK_YES) {
			wait1Msec(500);
			for (int i = 0; i < 2; i++)
			{
				nxtDisplayTextLine(3, "*Block is placed*");
				wait1Msec(600);
				nxtDisplayTextLine(3, "");
				nxtDrawRect(0, 63, 99, 0);
				wait1Msec(600);
			}
		}
		wait1Msec(500);
		if (bridgeSide == LEFT_SIDE) {
			nxtDrawLine(50, 9, 14, 9);
			wait1Msec(500);
			nxtDrawLine(14, 9, 14, 32);
			wait1Msec(500);
			nxtDrawLine(14, 32, 50, 32);
			wait1Msec(500);
		}
		else if (bridgeSide == RIGHT_SIDE) {
			nxtDrawLine(85, 9, 85, 32);
			wait1Msec(500);
			nxtDrawLine(85, 32, 50, 32);
			wait1Msec(500);
		}
	}
	wait1Msec(2000);
	eraseDisplay();
}

void drive(int x1, int y1, int x2)
{
	motor[frontLeft] = (- x1 - y1 + x2);
	motor[frontRight] = (x1 - y1 - x2);
	motor[rearLeft] = (x1 - y1 + x2);
	motor[rearRight] = (- x1 - y1 - x2);
}

void allStop()
{
	drive(0, 0, 0);
}

void alignWithBeacon()
{
	if (startingSide == LEFT_SIDE) {
		while (SensorValue[irSensor] != 4)
		{
			if (USreadDist(sonarSensor) > blockPlacementDist) {
				drive(35, 20, 0);
			}
			else if (USreadDist(sonarSensor) < blockPlacementDist) {
				drive(35, -20, 0);
			}
			else if (USreadDist(sonarSensor) == blockPlacementDist) {
				drive(35, 0, 0);
			}
		}
		allStop();
		ClearTimer(T4);
		while (SensorValue[irSensor] != 6)
		{
			drive(-20, 0, 0);
		}
		int irTimeLeft = time1[T4];
		allStop();
		drive(20, 0, 0);
		wait1Msec(irTimeLeft/2);
		allStop();
	}
	else if (startingSide == RIGHT_SIDE)
	{
		while (SensorValue[irSensor] != 6)
		{
			drive(-35, 0, 0);
		}
		allStop();
		ClearTimer(T4);
		while(SensorValue[irSensor] != 4)
		{
			drive(20, 0, 0);
		}
		int irTimeRight = time1[T4];
		allStop();
		drive(-20, 0, 0);
		wait1Msec(irTimeRight/2);
		allStop();
	}
	if (USreadDist(sonarSensor) < blockPlacementDist) {
		while (USreadDist(sonarSensor) < blockPlacementDist)
		{
			drive(0, -40, 0);
		}
		allStop();
	}
	else if (USreadDist(sonarSensor) > blockPlacementDist) {
		while (USreadDist(sonarSensor) > blockPlacementDist)
		{
			drive(0, 40, 0);
		}
		allStop();
	}
	if (startingSide == LEFT_SIDE) {
		while (SensorValue[irSensor] != 4)
		{
			drive(0, 0, 20);
		}
		allStop();
		ClearTimer(T4);
		while (SensorValue[irSensor] != 6)
		{
			drive(0, 0, -20);
		}
		int irTimeRot = time1[T4];
		allStop();
		drive(0, 0, 20);
		wait1Msec((irTimeRot/2) + 150);
		allStop();
	}
	else if (startingSide == RIGHT_SIDE) {
		while (SensorValue[irSensor] != 6)
		{
			drive(0, 0, -20);
		}
		allStop();
		ClearTimer(T4);
		while (SensorValue[irSensor] != 4)
		{
			drive(0, 0, 20);
		}
		int irTimeRot = time1[T4];
		allStop();
		drive(0, 0, -20);
		wait1Msec((irTimeRot/2) + 150);
		allStop();
	}
}

void placeBlock()
{
	ClearTimer(T2);
	while (time1[T2] < armMovementTime)
	{
		motor [grabberArm] = 75;
	}
	motor [grabberArm] = 0;
	wait1Msec(500);
	ClearTimer(T2);
	while (time1[T2] < armMovementTime - (250))
	{
		motor [grabberArm] = -75;
	}
	motor [grabberArm] = 0;
	if (USreadDist(sonarSensor) < bridgeMovementInitialDist) {
		while (USreadDist(sonarSensor) < bridgeMovementInitialDist)
		{
			drive(0, -30, 0);
		}
		allStop();
	}
	else if (USreadDist(sonarSensor) > bridgeMovementInitialDist) {
		while (USreadDist(sonarSensor) > bridgeMovementInitialDist)
		{
			drive(0, 30, 0);
		}
		allStop();
	}
	if  (startingSide == LEFT_SIDE) {
		while (SensorValue[irSensor] != 4)
		{
			drive(0, 0, 20);
		}
		allStop();
		ClearTimer(T4);
		while (SensorValue[irSensor] != 6)
		{
			drive(0, 0, -20);
		}
		int irTimeRotLeft = time1[T4];
		allStop();
		drive(0, 0, 20);
		wait1Msec((irTimeRotLeft/2) + 50);
		allStop();
	}
	else if (startingSide == RIGHT_SIDE) {
		while (SensorValue[irSensor] != 6)
		{
			drive(0, 0, -20);
		}
		allStop();
		ClearTimer(T4);
		while (SensorValue[irSensor] != 4)
		{
			drive(0, 0, 20);
		}
		int irTimeRotRight = time1[T4];
		allStop();
		drive(0, 0, -20);
		wait1Msec((irTimeRotRight/2) + 100);
		allStop();
	}
}

void parkOnBridge()
{
	if (bridgeSide == RIGHT_SIDE) {
		drive(50, 0, 0);
		wait1Msec(100);
		while (USreadDist(sonarSensor) < cratesPassedDist)
		{
			drive(50, 0, 0);
		}
		wait1Msec(clearPendulumDelay);
		allStop();
	}
	else if (bridgeSide == LEFT_SIDE) {
		drive(-50, 0, 0);
		wait1Msec(100);
		while (USreadDist(sonarSensor) < cratesPassedDist)
		{
			drive(-50, 0, 0);
		}
		wait1Msec(clearPendulumDelay);
		allStop();
	}
	ClearTimer(T3);
	while (time1[T3] < bridgeAlignmentTime)
	{
		drive(0, 50, 0);
	}
	allStop();
	wait1Msec(500);
	if (bridgeSide == RIGHT_SIDE) {
		ClearTimer(T3);
		while (time1[T3] < bridgeParkTime)
		{
			drive(-75, 0, 0);
		}
		allStop();
	}
	else if (bridgeSide == LEFT_SIDE) {
		ClearTimer(T3);
		while (time1[T3] < bridgeParkTime)
		{
			drive(75, 0, 0);
		}
		allStop();
	}
}
