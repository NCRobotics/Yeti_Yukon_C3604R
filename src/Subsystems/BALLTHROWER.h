#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class BALLTHROWER : public YUKON_COMMAND
{

    public:
        BALLTHROWER(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t BallThrowerSpeed);

        bool ForAsync(long durationMS, int16_t BallThrowerSpeed);
        bool ForAsync(long durationMS, int16_t BallThrowerSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdBallThrowerSpeed = 0;
        int16_t _OIBallThrowerSpeed = 0;

};
