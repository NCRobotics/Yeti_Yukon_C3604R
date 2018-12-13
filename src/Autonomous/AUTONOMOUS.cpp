#include "AUTONOMOUS.h"
#include "ROBOT.h"

AUTONOMOUS::AUTONOMOUS(ROBOT &refRobot) : Robot(refRobot)
{
    _MaxProgramNumber = 4;
}

void AUTONOMOUS::Loop()
{
    if (_AutonARMED)
    {
        if (Robot.State.AutonLightSensorActive)
        {
            LaunchQueued();
        }
    }

    if (_RunningAuton == "Auton1") ExecAuton1();
    else if(_RunningAuton == "Auton2") ExecAuton2();
    else if(_RunningAuton == "Auton3") ExecAuton3();
    else if(_RunningAuton == "Auton4") ExecAuton4();

     _RunningAuton = "";
    delay(20);
}
// (3000,127,127,50) 3000 is the time (3 sec), 127 is speed, 50% is delay until it starts the next command

// The Auton1 Drives forward for 3 seconds, and engages the lift at 1.5 seconds.
void AUTONOMOUS::ExecAuton1()
{
    Robot.Drive.ForAsync(3000, 127, 127, 50);
    Robot.Lift.ForAsync(500, 127, 100);
}
// The Auton2 Drives forward for half a second.
void AUTONOMOUS::ExecAuton2()
{
    Robot.Lift.ForAsync(500, 127, 100);
}
//Auton3 drives forward for 3 seconds.
void AUTONOMOUS::ExecAuton3()
{
    Robot.Drive.ForAsync(3000, 127, 127, 100);
}
//Auton4 drives forward for 3 seconds.
void AUTONOMOUS::ExecAuton4()
{
    Robot.Drive.ForAsync(3000, 127, 127, 100);
}
