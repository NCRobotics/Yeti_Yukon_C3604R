
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class BUDDYBOT : public YUKON_COMMAND
{

    public:
        BUDDYBOT(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t BuddyBotLiftSpeed);

        bool ForAsync(long durationMS, int16_t BuddyBotLiftSpeed);
        bool ForAsync(long durationMS, int16_t BuddyBotLiftSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdBuddyBotLiftSpeed = 0;
        int16_t _OIBuddyBotLiftSpeed = 0;

};
