
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class CLAW : public YUKON_COMMAND
{

    public:
        CLAW(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t ClawMotorSpeed);

        bool ForAsync(long durationMS, int16_t ClawMotorSpeed);
        bool ForAsync(long durationMS, int16_t ClawMotorSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdClawMotorSpeed = 0;
        int16_t _OIClawMotorSpeed = 0;

};
