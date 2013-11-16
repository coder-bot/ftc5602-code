#define HTSMUX_STAT_NORMAL 0x00
#define HTSMUX_STAT_BATT 0x01
#define HTSMUX_STAT_BUSY 0x02
#define HTSMUX_STAT_HALT 0x04
#define HTSMUX_STAT_ERROR 0x08

// #include "drivers/hitechnic-sensormux.h"


byte HTSMUXreadStatus(tSensors smux) {
	ubyte sendMsg[3];
	ubyte readMsg[1];
	sendMsg[0] = 2; // size of I2C message
	sendMsg[1] = 0x10; // Address of SMUX
	sendMsg[2] = 0x21; // Status register
	// Query the SMUX and read the response
	sendI2CMsg(smux, sendMsg, 1);
	wait1Msec(10);
	readI2CReply(smux, readMsg, 1);
	return readMsg[0];
}
task main () {
	byte status = 0;
	SetSensorType(S1, sensorLowSpeed);
	wait1Msec (100);
	while (true) {
		eraseDisplay();
		status = HTSMUXreadStatus(S1);
		nxtDisplayTextLine(1, "Status: %d",
		status);
		if(status & HTSMUX_STAT_BATT ==
			HTSMUX_STAT_BATT)
		nxtDisplayTextLine (3, "No battery");
		wait1Msec (100);
	}
}
