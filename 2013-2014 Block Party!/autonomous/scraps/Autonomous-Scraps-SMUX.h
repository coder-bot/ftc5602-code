//holonomic autonomous for block party - header file containing functions for core/mech operations as well as bridge park procedure

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

int armMovementTime = 2250;
int blockPlacementDist = 40;
int cratesPassedDist = 100;
int bridgeMovementInitialDist = 48;
int bridgeAlignmentTime = 1500;
int bridgeParkTime = 2000;
int clearPendulumDelay = 350;

const tMUXSensor sonarSensor = msensor_S3_1;
const tMUXSensor lightSensor = msensor_S3_2;

void initializeRobot()
{
	LSsetActive(lightSensor);
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
	if (STARTING_SIDE == LEFT_SIDE) {
		while (SensorValue[irSensor] != 4)
		{
			drive(35, 0, 0);
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
	else if (STARTING_SIDE == RIGHT_SIDE)
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
	wait1Msec((irTimeRot/2) + 100);
	allStop();
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
	if  (STARTING_SIDE == LEFT_SIDE) {
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
	else if (STARTING_SIDE == RIGHT_SIDE) {
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
	if (STARTING_SIDE == LEFT_SIDE) {
		drive(50, 0, 0);
		wait1Msec(100);
		while (USreadDist(sonarSensor) < cratesPassedDist)
		{
			drive(50, 0, 0);
		}
		wait1Msec(clearPendulumDelay);
		allStop();
	}
	else if (STARTING_SIDE == RIGHT_SIDE) {
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
	if (STARTING_SIDE == LEFT_SIDE) {
		ClearTimer(T3);
		while (time1[T3] < bridgeParkTime)
		{
			drive(-75, 0, 0);
		}
		allStop();
	}
	else if (STARTING_SIDE == RIGHT_SIDE) {
		ClearTimer(T3);
		while (time1[T3] < bridgeParkTime)
		{
			drive(75, 0, 0);
		}
		allStop();
	}
}
