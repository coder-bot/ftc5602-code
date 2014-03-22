//holonomic autonomous for block party - header file containing functions for core/mech operations as well as bridge park procedure and initial configuration/map generation via the NXT screen and buttons

//Timer Usage (Important):
//T1 - RESERVED - fail-safe timer that shuts down program if it is taking too long e.g. motors are burning out from ramming another robot unintentionally
//T2 - RESERVED - time taken for arm to move to place block
//T3 - RESERVED - time taken for robot to execute movements to park on the bridge
//T4 - RESERVED - timer used to precisely set IR beacon alignment

#include <JoystickDriver.c>
#include <drivers/hitechnic-sensormux.h>
//#include <drivers/lego-light.h>
#include <drivers/lego-ultrasound.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define PLACE_BLOCK_NO 0
#define PLACE_BLOCK_YES 1

int armMovementTime = 2250;
int blockPlacementDist = 39;
int cratesPassedDist = 100;
int bridgeMovementInitialDist = 45;
int bridgeAlignmentTime = 1650;
int bridgeParkTime = 2000;
int clearPendulumDelay = 325;
int startingSide, bridgeSide, placeBlockQuery, delayTime, reconfigure, failSafeTime;

const tMUXSensor sonarSensor = msensor_S3_1;
//const tMUXSensor lightSensor = msensor_S3_2;

task masterTimer()
{
	ClearTimer(T1);
	while (1)
	{
		if (time1[T1] >= failSafeTime * 1000) {
			StopAllTasks();
		}
	}
}

void initializeAutonomous();
void updateDelayTimeDisplay();
void updateFailSafeTimeDisplay();
void generateAutonomousMap();

void initializeRobot()
{
	initializeAutonomous();
	servo [scoopCover] = 220;
	servo [leftLatch] = 0;
	servo [rightLatch] = 255;
}

void initializeAutonomous()
{
	eraseDisplay();
	delayTime = 0;
	failSafeTime = 30;
	nxtDisplayTextLine(2, "Block/bridge?");
	nxtDisplayTextLine(4, "Orange: Both");
	nxtDisplayTextLine(5, "Arrow: Bridge");
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
	nxtDisplayCenteredTextLine(3, "Starting side?");
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
			nxtDisplayCenteredTextLine(3, "%ds", delayTime);
			wait1Msec(800);
			break;
		}
		if (delayTime < 0) {
			delayTime = 0;
			updateDelayTimeDisplay();
		}
		if (delayTime > 30) {
			delayTime = 30;
			updateDelayTimeDisplay();
		}
	}
	updateFailSafeTimeDisplay();
	while (1)
	{
		if (nNxtButtonPressed == 1) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			failSafeTime ++;
			updateFailSafeTimeDisplay();
		}
		else if (nNxtButtonPressed == 2) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			failSafeTime --;
			updateFailSafeTimeDisplay();
		}
		if (nNxtButtonPressed == 3) {
			while (nNxtButtonPressed !=(-1))
			{
			}
			eraseDisplay();
			nxtDisplayCenteredTextLine(3, "%ds", failSafeTime);
			wait1Msec(800);
			break;
		}
		if (failSafeTime < 0) {
			failSafeTime = 0;
			updateFailSafeTimeDisplay();
		}
		if (failSafeTime > 30) {
			failSafeTime = 30;
			updateFailSafeTimeDisplay();
		}
		if (failSafeTime <= delayTime) {
			failSafeTime = delayTime + 1;
			updateFailSafeTimeDisplay();
		}
	}
	eraseDisplay();
	nxtDisplayCenteredTextLine(1, "Confirm options:");
	wait1Msec(500);
	if (placeBlockQuery == PLACE_BLOCK_YES)
		nxtDisplayTextLine(3, "Block & bridge");
	else if (placeBlockQuery == PLACE_BLOCK_NO)
		nxtDisplayTextLine(3, "Bridge only");
	wait1Msec(500);
	if (startingSide == LEFT_SIDE)
		nxtDisplayTextLine(4, "Start: Left");
	else if (startingSide == RIGHT_SIDE)
		nxtDisplayTextLine(4, "Start: Right");
	wait1Msec(500);
	if (bridgeSide == LEFT_SIDE)
		nxtDisplayTextLine(5, "End: Left");
	else if (bridgeSide == RIGHT_SIDE)
		nxtDisplayTextLine(5, "End: Right");
	wait1Msec(500);
	nxtDisplayTextLine(6, "Delay: %ds", delayTime);
	wait1Msec(500);
	nxtDisplayTextLine(7, "Failsafe: %ds", failSafeTime);
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
	nxtDisplayCenteredTextLine(3, "Delay: %ds", delayTime);
}

void updateFailSafeTimeDisplay()
{
	nxtDisplayCenteredTextLine(3, "Failsafe: %ds", failSafeTime);
}

void generateAutonomousMap()
{
	eraseDisplay();
	nxtDisplayCenteredTextLine(3, "Generating map...");
	wait1Msec(1000);
	eraseDisplay();
	wait1Msec(500);
	nxtDisplayCenteredTextLine(1, "Delay: %ds", delayTime);
	wait1Msec(500);
	nxtDisplayCenteredTextLine(2, "Failsafe: %ds", failSafeTime);
	wait1Msec(750);
	nxtDrawRect(0, 63, 99, 0);
	wait1Msec(500);
	if (startingSide == LEFT_SIDE) {
		if (placeBlockQuery == PLACE_BLOCK_YES || bridgeSide == RIGHT_SIDE) {
			nxtDrawLine(14, 9, 50, 9);
			wait1Msec(500);
		}
		if (placeBlockQuery == PLACE_BLOCK_YES) {
			for (int i = 0; i < 2; i++)
			{
				nxtDisplayTextLine(4, "*Block is placed*");
				wait1Msec(600);
				nxtDisplayTextLine(4, "");
				nxtDrawRect(0, 63, 99, 0);
				wait1Msec(600);
			}
		}
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
			wait1Msec(500);
		}
		if (placeBlockQuery == PLACE_BLOCK_YES) {
			for (int i = 0; i < 2; i++)
			{
				nxtDisplayTextLine(4, "*Block is placed*");
				wait1Msec(600);
				nxtDisplayTextLine(4, "");
				nxtDrawRect(0, 63, 99, 0);
				wait1Msec(600);
			}
		}
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
				drive(35, 35, 0);
			}
			else if (USreadDist(sonarSensor) < blockPlacementDist) {
				drive(35, -35, 0);
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
			if (USreadDist(sonarSensor) > blockPlacementDist) {
				drive(-35, 20, 0);
			}
			else if (USreadDist(sonarSensor) < blockPlacementDist) {
				drive(-35, -20, 0);
			}
			else if (USreadDist(sonarSensor) == blockPlacementDist) {
				drive(-35, 0, 0);
			}
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
			drive(0, -20, 0);
		}
		allStop();
	}
	else if (USreadDist(sonarSensor) > blockPlacementDist) {
		while (USreadDist(sonarSensor) > blockPlacementDist)
		{
			drive(0, 20, 0);
		}
		allStop();
	}
	if (USreadDist(sonarSensor) > blockPlacementDist) {
		while (USreadDist(sonarSensor) > blockPlacementDist)
		{
			drive(0, 20, 0);
		}
		allStop();
	}
	else if (USreadDist(sonarSensor) < blockPlacementDist) {
		while (USreadDist(sonarSensor) < blockPlacementDist)
		{
			drive(0, -20, 0);
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
		wait1Msec((irTimeRot/2) + 125);
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
		wait1Msec((irTimeRot/2) + 125);
		allStop();
	}
}

void placeBlock()
{
	ClearTimer(T2);
	while (time1[T2] < armMovementTime)
	{
		motor [arm] = 75;
	}
	motor [arm] = 0;
	wait1Msec(500);
	ClearTimer(T2);
	while (time1[T2] < armMovementTime - (250))
	{
		motor [arm] = -75;
	}
	motor [arm] = 0;
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
		wait1Msec((irTimeRotLeft/2) + 100);
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
			if (USreadDist(sonarSensor) > bridgeMovementInitialDist) {
				drive(50, 20, 0);
			}
			else if (USreadDist(sonarSensor) < bridgeMovementInitialDist) {
				drive(50, -20, 0);
			}
			else if (USreadDist(sonarSensor) == bridgeMovementInitialDist) {
				drive(50, 0, 0);
			}
		}
		wait1Msec(clearPendulumDelay);
		allStop();
	}
	else if (bridgeSide == LEFT_SIDE) {
		drive(-50, 0, 0);
		wait1Msec(100);
		while (USreadDist(sonarSensor) < cratesPassedDist)
		{
			if (USreadDist(sonarSensor) > bridgeMovementInitialDist) {
				drive(-50, 20, 0);
			}
			else if (USreadDist(sonarSensor) < bridgeMovementInitialDist) {
				drive(-50, -20, 0);
			}
			else if (USreadDist(sonarSensor) == bridgeMovementInitialDist) {
				drive(-50, 0, 0);
			}
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
			drive(-100, 0, 0);
		}
		allStop();
	}
	else if (bridgeSide == LEFT_SIDE) {
		ClearTimer(T3);
		while (time1[T3] < bridgeParkTime)
		{
			drive(100, 0, 0);
		}
		allStop();
	}
}
