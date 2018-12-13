
#include "DRIVE.h"
#include "ROBOT.h"

DRIVE::DRIVE(ROBOT &refRobot) : Robot(refRobot)
{
}

void DRIVE::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.DriveRightSpeed = _CmdDriveRightSpeed;
            Robot.State.DriveLeftSpeed = _CmdDriveLeftSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.DriveRightSpeed = _OIDriveRightSpeed;
    Robot.State.DriveLeftSpeed = _OIDriveLeftSpeed;

    delay(20);
}

void DRIVE::OISetSpeed(int16_t DriveRightSpeed,int16_t DriveLeftSpeed)
{
    _OIDriveRightSpeed = DriveRightSpeed;
    _OIDriveLeftSpeed = DriveLeftSpeed;
}

bool DRIVE::ForAsync(long durationMS, int16_t DriveRightSpeed,int16_t DriveLeftSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, DriveRightSpeed,DriveLeftSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool DRIVE::ForAsync(long durationMS, int16_t DriveRightSpeed,int16_t DriveLeftSpeed)
{
    _CmdDriveRightSpeed = DriveRightSpeed;
    _CmdDriveLeftSpeed = DriveLeftSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
