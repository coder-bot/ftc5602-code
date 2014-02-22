//holonomic autonomous for block party - header file containing functions for core/mech operations as well as bridge park procedure

//Timer Usage (Important):
//T1 - RESERVED - fail-safe timer that shuts down program if it is taking too long e.g. motors are burning out from ramming another robot unintentionally
//T2 - RESERVED - time taken for arm to move to place block
//T3 - RESERVED - time taken for robot to execute movements to park on the bridge
//T4 - RESERVED - timer used to precisely set IR beacon alignment

#include <JoystickDriver.c>

//#define DELTA_LEFT 0
//#define DELTA_RIGHT 1
//#define ALIGN_BRIDGE_LEFT -100
//#define ALIGN_BRIDGE_RIGHT 100
//#define WHITE 45
#define LEFT_SIDE 0
#define RIGHT_SIDE 1
//#define BRIDGE_PARK_S1_MAX 5000
//#define BRIDGE_PARK_S2_MAX 5000
//#define BEACON_ALIGN_S1_MAX 5000
//#define BEACON_RETREAT_MAX 5000

int armMovementTime = 2250;
//int beaconStatus, deltaAlignment, bridgeMovement;
int blockPlacementDist = 40;
int cratesPassedDist = 100;
int bridgeMovementInitialDist = 48;
//int whiteTapeDelay = 1000;
int bridgeAlignmentTime = 1500;
int bridgeParkTime = 2000;
int clearPendulumDelay = 350;
int alignmentRunCount = 0;

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

#if 0
void getBeaconStatus ()
{
	while (SensorValue [sonarSensor] > blockPlacementDist)
	{
		drive(0, 60, 0);
	}
	allStop();
	beaconStatus = SensorValue [irSensor];
}
#endif

void alignWithBeacon()
{
	alignmentRunCount++;
	//getBeaconStatus();
	//ClearTimer(T4);
	if (STARTING_SIDE == LEFT_SIDE) {
		while (SensorValue[irSensor] != 4)
		{
			drive(35, 0, 0);
		}
		/*if (time1[T4] < 750) {
		wait1Msec(250);
		}*/
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
		/*if (time1[T4] < 750) {
		wait1Msec(250);
		}*/
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
	if (alignmentRunCount >= 2) {
		return;
		} else {
		if (SensorValue[sonarSensor] < blockPlacementDist) {
			while (SensorValue[sonarSensor] < blockPlacementDist)
			{
				drive(0, -40, 0);
			}
			allStop();
		}
		else if (SensorValue[sonarSensor] > blockPlacementDist) {
			while (SensorValue[sonarSensor] > blockPlacementDist)
			{
				drive(0, 40, 0);
			}
			allStop();
		}
		//alignWithBeacon();
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
		//if (SensorValue[sonarSensor] < blockPlacementDist) {
		//	while (SensorValue[sonarSensor] < blockPlacementDist)
		//	{
		//		drive(0, -40, 0);
		//	}
		//	allStop();
		//}
		//else if (SensorValue[sonarSensor] > blockPlacementDist) {
		//	while (SensorValue[sonarSensor] > blockPlacementDist)
		//	{
		//		drive(0, 40, 0);
		//	}
		//	allStop();
		//}
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
	if (SensorValue[sonarSensor] < bridgeMovementInitialDist) {
		while (SensorValue [sonarSensor] < bridgeMovementInitialDist)
		{
			drive(0, -30, 0);
#if 0
			if (time1[T1] > BEACON_RETREAT_MAX) {
				return;
			}
#endif
		}
		allStop();
	}
	else if (SensorValue[sonarSensor] > bridgeMovementInitialDist) {
		while (SensorValue[sonarSensor] > bridgeMovementInitialDist)
		{
			drive(0, 30, 0);
#if 0
			if (time1[T1] > BEACON_RETREAT_MAX) {
				return;
			}
#endif
		}
		allStop();
	}
	//alignWithBeacon();
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
		while (SensorValue[sonarSensor] < cratesPassedDist)
		{
			drive(50, 0, 0);
		}
		wait1Msec(clearPendulumDelay);
		allStop();
	}
	else if (STARTING_SIDE == RIGHT_SIDE) {
		drive(-50, 0, 0);
		wait1Msec(100);
		while (SensorValue[sonarSensor] < cratesPassedDist)
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
