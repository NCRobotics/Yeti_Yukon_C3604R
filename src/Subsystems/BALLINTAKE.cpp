#include "BALLINTAKE.h"
#include "ROBOT.h"

BALLINTAKE::BALLINTAKE(ROBOT &refRobot) : Robot(refRobot)
{
}

void BALLINTAKE::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallIntakeMotorSpeed = _CmdBallIntakeSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BallIntakeMotorSpeed = _OIBallIntakeSpeed;

    delay(20);
}

void BALLINTAKE::OISetSpeed(int16_t BallIntakeSpeed)
{
     _OIBallIntakeSpeed = BallIntakeSpeed;
}

bool BALLINTAKE::ForAsync(long durationMS, int16_t BallIntakeSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, BallIntakeSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool BALLINTAKE::ForAsync(long durationMS, int16_t BallIntakeSpeed)
{
    _CmdBallIntakeSpeed = BallIntakeSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}