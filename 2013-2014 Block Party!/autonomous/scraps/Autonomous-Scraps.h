//holonomic autonomous for block party - header file containing functions for core/mech operations as well as bridge park procedure

//Timer Usage (Important):
//T1 - RESERVED - fail-safe timer that shuts down program if it is taking too long e.g. motors are burning out from ramming another robot unintentionally
//T2 - RESERVED - time taken for arm to move to place block AND time taken for robot to align into proper position for bridge-parking
//T3 - RESERVED - time taken for robot to make parallel movement onto bridge
//T4 - AVAILIBLE

#include <JoystickDriver.c>

#define DELTA_LEFT 0
#define DELTA_RIGHT 1
#define ALIGN_BRIDGE_LEFT -100
#define ALIGN_BRIDGE_RIGHT 100
#define WHITE 45
#define BRIDGE_PARK_S1_MAX 5000
#define BRIDGE_PARK_S2_MAX 5000
#define BEACON_ALIGN_S1_MAX 5000
#define BEACON_RETREAT_MAX 5000

int armMovementTime = 2000;
int beaconStatus, deltaAlignment, bridgeMovement;
int blockPlacementDist = 25;
int cratesPassedDist = 40;
int bridgeMovementInitialDist = 35;
//int whiteTapeDelay = 1000;
int bridgeAlignmentTime = 1000;
int bridgeParkTime = 1800;
int clearPendulumDelay = 1000;

void drive(int x1, int y1, int x2)
{
	motor[frontLeft] = (x1 + y1 + x2);
	motor[frontRight] = (- x1 + y1 - x2);
	motor[rearLeft] = (- x1 + y1 + x2);
	motor[rearRight] = (x1 + y1 - x2);
}

void allStop()
{
	drive(0, 0, 0);
}

void getBeaconStatus ()
{
	while (SensorValue [sonarSensor] > blockPlacementDist)
	{
		drive(0, 100, 0);
	}
	allStop();
	beaconStatus = SensorValue [irSensor];
}

void alignWithBeacon()
{
	getBeaconStatus();
	if (beaconStatus > 5) {
		deltaAlignment = DELTA_RIGHT;
		while (SensorValue [irSensor] != 5)
		{
			drive(80, 0, 0);
			if (time1[T1] > BEACON_ALIGN_S1_MAX) {
				return;
			}
		}
		allStop();
	}
	else if (beaconStatus < 5) {
		deltaAlignment = DELTA_LEFT;
		while (SensorValue [irSensor] != 5)
		{
			drive(-80, 0, 0);
			if (time1[T1] > BEACON_ALIGN_S1_MAX) {
				return;
			}
		}
		allStop();
	}
	if (SensorValue[sonarSensor] < blockPlacementDist) {
		while (SensorValue[sonarSensor] < blockPlacementDist)
		{
			drive(0, 75, 0);
		}
		allStop();
	}
	else if (SensorValue[sonarSensor] > blockPlacementDist) {
		while (SensorValue[sonarSensor] > blockPlacementDist)
		{
			drive(0, -75, 0);
		}
		allStop();
	}
}

void placeBlock()
{
	ClearTimer(T2);
	while (time1[T2] < armMovementTime)
	{
		motor [grabberArm] = 100;
	}
	motor [grabberArm] = 0;
	wait1Msec(1000);
	ClearTimer(T2);
	while (time1[T2] < armMovementTime)
	{
		motor [grabberArm] = -100;
	}
	motor [grabberArm] = 0;
	while (SensorValue [sonarSensor] < bridgeMovementInitialDist)
	{
		drive(0, -100, 0);
		if (time1[T1] > BEACON_RETREAT_MAX) {
			return;
		}
	}
	allStop();
}

void parkOnBridge()
{
	if (deltaAlignment == DELTA_LEFT) {
		bridgeMovement = ALIGN_BRIDGE_LEFT;
	}
	else if (deltaAlignment == DELTA_RIGHT) {
		bridgeMovement = ALIGN_BRIDGE_RIGHT;
	}
	ClearTimer(T1);
	while(SensorValue [sonarSensor] < cratesPassedDist)
	{
		drive(bridgeMovement, 0, 0);
		if (time1[T1] > BRIDGE_PARK_S1_MAX) {
			return;
		}
	}
	wait1Msec(clearPendulumDelay);
	allStop();

	//can't use line sensor because only the sonar can be run through the SMUX and only 2 ports are availible
#if 0
	//pretend the sonar sensor is the line sensor here
	ClearTimer(T1);
	while (SensorValue [sonarSensor] < WHITE)
	{
		drive(0, 80, 0);
		if (time1[T1] > BRIDGE_PARK_S2_MAX) {
			return;
		}
	}
	wait1Msec(whiteTapeDelay);
	allStop();
	ClearTimer(T3);
	while (time1[T3] < bridgeParkTime)
	{
		drive(-(bridgeMovement), 0, 0);
	}
	allStop();
#endif
	ClearTimer(T1);
	ClearTimer(T2);
	while (time1[T2] < bridgeAlignmentTime)
	{
		drive(0, 80, 0);
		if (time1[T1] > BRIDGE_PARK_S2_MAX) {
			return;
		}
	}
	allStop();
	ClearTimer(T3);
	while (time1[T3] < bridgeParkTime)
	{
		drive(-(bridgeMovement), 0, 0);
	}
	allStop();
}
