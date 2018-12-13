
#include "LIFT.h"
#include "ROBOT.h"

LIFT::LIFT(ROBOT &refRobot) : Robot(refRobot)
{
}

void LIFT::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.LiftMotorSpeed = _CmdLiftMotorSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.LiftMotorSpeed = _OILiftMotorSpeed;

    delay(20);
}

void LIFT::OISetSpeed(int16_t LiftMotorSpeed)
{
    _OILiftMotorSpeed = LiftMotorSpeed;
}

bool LIFT::ForAsync(long durationMS, int16_t LiftMotorSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, LiftMotorSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool LIFT::ForAsync(long durationMS, int16_t LiftMotorSpeed)
{
    _CmdLiftMotorSpeed = LiftMotorSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
