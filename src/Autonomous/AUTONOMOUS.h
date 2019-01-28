#pragma once

#include <Arduino.h>
#include <YUKON_AUTON.h>
#include <Encoder.h>

    class ROBOT;
    class EncRead;

    class AUTONOMOUS : public YUKON_AUTON
    {

    public:
    AUTONOMOUS(ROBOT &refRobot);
    void Loop();


    private:
    ROBOT &Robot;

    void ExecAuton1();
    void ExecAuton2();
    void ExecAuton3();
    void ExecAuton4();

    };


