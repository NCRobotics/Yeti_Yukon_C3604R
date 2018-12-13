
#include "BUDDYBOT.h"
#include "ROBOT.h"

BUDDYBOT::BUDDYBOT(ROBOT &refRobot) : Robot(refRobot)
{
}

void BUDDYBOT::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BuddyBotLiftSpeed = _CmdBuddyBotLiftSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BuddyBotLiftSpeed = _OIBuddyBotLiftSpeed;

    delay(20);
}

void BUDDYBOT::OISetSpeed(int16_t BuddyBotLiftSpeed)
{
    _OIBuddyBotLiftSpeed = BuddyBotLiftSpeed;
}

bool BUDDYBOT::ForAsync(long durationMS, int16_t BuddyBotLiftSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, BuddyBotLiftSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool BUDDYBOT::ForAsync(long durationMS, int16_t BuddyBotLiftSpeed)
{
    _CmdBuddyBotLiftSpeed = BuddyBotLiftSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
