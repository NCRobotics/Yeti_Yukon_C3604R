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

void AUTONOMOUS::ExecAuton1()
{
    Robot.Drive.ForAsync(2000, 127, 127, 10);
    Robot.Lift.ForAsync(250, 127, 100); 

}
void AUTONOMOUS::ExecAuton2()
{
    Robot.Lift.ForAsync(500, 127, 100);
}
void AUTONOMOUS::ExecAuton3()
{
    Robot.Drive.ForAsync(3000, 127, 127, 100);
}
void AUTONOMOUS::ExecAuton4()
{
    Robot.Drive.ForAsync(3000, 127, 127, 100);
}