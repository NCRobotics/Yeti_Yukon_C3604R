
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>
#include <Encoder.h>

class ROBOT;

class DRIVE : public YUKON_COMMAND
{

    public:
        DRIVE(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t DriveRightSpeed,int16_t DriveLeftSpeed);
        int EighthTurnsWent = 0;
        bool ForAsync(long durationMS, int16_t DriveRightSpeed,int16_t DriveLeftSpeed);
        bool ForAsync(long durationMS, int16_t DriveRightSpeed,int16_t DriveLeftSpeed, uint8_t HoldPercent);
        bool ForSensor(int EighthTurnsWent, int16_t DriveRightSpeed,int16_t DriveLeftSpeed, uint8_t HoldPercent);
long EncReport() 
{
        long oldPosition = 0;
        Encoder myEnc(26, 27);
        long NewLeftPos = myEnc.read();
    if (NewLeftPos != oldPosition) 
        oldPosition = NewLeftPos;
    if (NewLeftPos == 45)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 90)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 135)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 180)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 225)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 270)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 315)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
    if (NewLeftPos == 360)
    {
        EighthTurnsWent = EighthTurnsWent + 1;
    }
        while (true)
        {
            EncReport();
        }
}


    private:
        int16_t _CmdDriveRightSpeed = 0;
        int16_t _OIDriveRightSpeed = 0;
        int16_t _CmdDriveLeftSpeed = 0;
        int16_t _OIDriveLeftSpeed = 0;
        

};
