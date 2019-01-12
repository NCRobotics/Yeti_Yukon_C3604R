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
//You need to travel about 1140 ms to go a whole tile
void AUTONOMOUS::ExecAuton1()
{
    Robot.Drive.ForAsync(3500, 100, 100, 100);
    Robot.Drive.ForAsync(3500, -100, -100, 100);
    Robot.Drive.ForAsync(1140, 100, 100, 100);
    Robot.DriveLeft.ForAsync(1139, 100, 100, 0);
    Robot.DriveRight.ForAsync(1139, -100, -100, 100);
    Robot.Drive.ForAsync(300, 255, 255, 100);

  
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