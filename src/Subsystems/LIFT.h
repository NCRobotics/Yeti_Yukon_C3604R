
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class LIFT : public YUKON_COMMAND
{

    public:
        LIFT(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t LiftMotorSpeed);

        bool ForAsync(long durationMS, int16_t LiftMotorSpeed);
        bool ForAsync(long durationMS, int16_t LiftMotorSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdLiftMotorSpeed = 0;
        int16_t _OILiftMotorSpeed = 0;

};
