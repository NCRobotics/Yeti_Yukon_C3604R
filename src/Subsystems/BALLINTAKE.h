#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class BALLINTAKE : public YUKON_COMMAND
{

    public:
        BALLINTAKE(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t BallIntakeSpeed);

        bool ForAsync(long durationMS, int16_t BallIntakeSpeed);
        bool ForAsync(long durationMS, int16_t BallIntakeSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdBallIntakeSpeed = 0;
        int16_t _OIBallIntakeSpeed = 0;

};
