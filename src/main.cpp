#include <Arduino.h>
#include <Wire.h>

#include <YETI_YUKON.h>
#include <ROBOT.h>

YETI_YUKON Yukon("YOURROBOTNAME", "aa1b8985-1aa3-488f-987f-67aed4d5cf38");
ROBOT Robot(Yukon);

void WatchdogTask(void *pvParameters);
void DriveTask(void *pvParameters);
void LiftTask(void *pvParameters);
void ClawTask(void *pvParameters);
void BuddyBotTask(void *pvParameters);
void AutonTask(void *pvParameters);

void setup()
{
    Serial.begin(115200);

    Wire.begin(4, 15, 400000);

    Yukon.Setup();
    Robot.Setup();

    Serial.print("MainLoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    xTaskCreatePinnedToCore(WatchdogTask, "WatchdogTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(DriveTask, "DriveTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(LiftTask, "LiftTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(ClawTask, "ClawTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(BuddyBotTask, "BuddyBotTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(AutonTask, "AutonTask", 10000, NULL, 1, NULL, 1);
}

void loop()
{
    Yukon.Loop(); 
    Robot.Loop();

    delay(1);
    yield();
}

void WatchdogTask(void *pvParameters)
{
    Serial.print("WatchdogTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        Yukon.EnableWatchdog();
        while (true)
        {
            Yukon.WatchdogLoop();
            delay(100);
        }
    }

void DriveTask(void *pvParameters)
{
    Serial.print("DriveTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.Drive.Loop();
        }
    }
    
void LiftTask(void *pvParameters)
{
    Serial.print("LiftTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.Lift.Loop();
        }
    }
    
void ClawTask(void *pvParameters)
{
    Serial.print("ClawTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.Claw.Loop();
        }
    }
    
void BuddyBotTask(void *pvParameters)
{
    Serial.print("BuddyBotTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.BuddyBot.Loop();
        }
    }
    

void AutonTask(void *pvParameters)
{
    Serial.print("AutonTask: Executing on core ");
    Serial.println(xPortGetCoreID());
    Robot.Auton.Setup();

    while(true)
    {
        Robot.Auton.Loop();
    }
}