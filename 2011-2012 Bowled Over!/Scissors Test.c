#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorlaurel,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                         - Moving Forward -                                             *|
|*                                       ROBOTC on NXT + TETRIX                                           *|
|*                                                                                                        *|
|*  This program runs your TETRIX robot forward for a designated amount of time.                          *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  Remember to use 'Robot -> Motors and Sensors Setup'to set up your motor configuration.          *|
|*    2)  If using kit TETRIX bot, remember to reverse Motor E in 'Motor and Sensor Setup'.               *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port 1                  none                TETRIX Controller   TETRIX                              *|
|*    Port 1 - Motor 1        motorD              12V                 Right motor                         *|
|*    Port 1 - Motor 2        motorE              12V                 Left motor                          *|
\*---------------------------------------------------------------------------------------------------4246-*/
#include "JoystickDriver.c"
task main()
{
  while(true)                            // Infinite loop:
  {
    getJoystickSettings(joystick);
   motor[motorlaurel] = joystick.joy1_y2*.2;   // Motor D is run at a power level of 25.

   }
 }