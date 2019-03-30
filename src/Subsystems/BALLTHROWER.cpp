#include "BALLTHROWER.h"
#include "ROBOT.h"

BALLTHROWER::BALLTHROWER(ROBOT &refRobot) : Robot(refRobot)
{
}

void BALLTHROWER::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallThrowerMotorSpeed = _CmdBallThrowerSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BallThrowerMotorSpeed = _OIBallThrowerSpeed;

    delay(20);
}

void BALLTHROWER::OISetSpeed(int16_t BallThrowerSpeed)
{
     _OIBallThrowerSpeed = BallThrowerSpeed;
}

bool BALLTHROWER::ForAsync(long durationMS, int16_t BallThrowerSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, BallThrowerSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool BALLTHROWER::ForAsync(long durationMS, int16_t BallThrowerSpeed)
{
    _CmdBallThrowerSpeed = BallThrowerSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
