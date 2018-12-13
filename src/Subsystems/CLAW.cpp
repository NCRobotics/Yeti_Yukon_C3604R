
#include "CLAW.h"
#include "ROBOT.h"

CLAW::CLAW(ROBOT &refRobot) : Robot(refRobot)
{
}

void CLAW::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.ClawMotorSpeed = _CmdClawMotorSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.ClawMotorSpeed = _OIClawMotorSpeed;

    delay(20);
}

void CLAW::OISetSpeed(int16_t ClawMotorSpeed)
{
    _OIClawMotorSpeed = ClawMotorSpeed;
}

bool CLAW::ForAsync(long durationMS, int16_t ClawMotorSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, ClawMotorSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool CLAW::ForAsync(long durationMS, int16_t ClawMotorSpeed)
{
    _CmdClawMotorSpeed = ClawMotorSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
