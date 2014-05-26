//holonomic autonomous for 2014 flashback scrimmage - header file containing functions for core/mech operations

//Timer Usage (Important):
//T1 - RESERVED - fail-safe timer that shuts down program if it is taking too long e.g. motors are burning out from ramming another robot unintentionally
//T2 - RESERVED - time taken for arm to move to place block
//T3 - RESERVED - time taken for robot to execute movements to park on the bridge and to set horizontal IR beacon alignment
//T4 - RESERVED - timer used to precisely set IR beacon rotational alignment


#include <JoystickDriver.c> //for waitforstart and diagnostic display control

//constants for starting sides and whether or not to place the block
#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define PLACE_BLOCK_NO 0
#define PLACE_BLOCK_YES 1

int armMovementTime = 2250; //duration of time arm to move to place block
int blockPlacementDist = 51; //distance robot places itself from the crates prior to block placement

void initializeRobot()
{
	servo [scoopCover] = 230;
	servo [leftLatch] = 252;
	servo [rightLatch] = 10;
	servo [batonManipulator] = 135;
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
}
