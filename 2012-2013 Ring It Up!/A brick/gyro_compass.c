#pragma config(Sensor, S2,     compass,             sensorI2CHiTechnicCompass)

int nNewHeading;
int nOldHeading = 999;

const tSensors kGyroSensor = S3;      // Connect to port 3. Adjust as appropriate.

#include "GyroDriver.c"

float fOldAngle = -1;

task main()
{
	fGyroAngle = SensorValue[compass];

	while (!bIsGyroInitialized())
	{
		wait1Msec(250);// Wait for the gyro to initialize. This takes a couple of seconds.
	}

	while (true)
	{
		nNewHeading = SensorValue[compass];
		if (abs(nNewHeading - nOldHeading) > 1)
		{
			// Only update when changed to avoid LCD screen flicker
			nxtDisplayCenteredTextLine(2, "Compass: %d", nNewHeading);
			nOldHeading = nNewHeading;
		}
		if (fGyroAngle != fOldAngle)
		{
			nxtDisplayCenteredTextLine(5, "Gyro: %3d", (long) fGyroAngle);
			fOldAngle = fGyroAngle;
		}
		wait1Msec(3);
	}
}
