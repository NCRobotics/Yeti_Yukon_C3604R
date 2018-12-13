
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class DRIVE : public YUKON_COMMAND
{

    public:
        DRIVE(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t DriveRightSpeed,int16_t DriveLeftSpeed);

        bool ForAsync(long durationMS, int16_t DriveRightSpeed,int16_t DriveLeftSpeed);
        bool ForAsync(long durationMS, int16_t DriveRightSpeed,int16_t DriveLeftSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdDriveRightSpeed = 0;
        int16_t _OIDriveRightSpeed = 0;
        int16_t _CmdDriveLeftSpeed = 0;
        int16_t _OIDriveLeftSpeed = 0;

};
