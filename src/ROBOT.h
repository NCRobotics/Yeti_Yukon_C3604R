#ifndef ROBOT_h
#define ROBOT_h

#include <YETI_YUKON.h>
#include <STATE.h>
#include <XBOXRECV.h>

#include <YUKON_CytronMD10.h>

#include "Subsystems\Drive.h"
#include "Subsystems\Lift.h"
#include "Subsystems\Claw.h"
#include "Subsystems\BuddyBot.h"
#include "Subsystems\BALLTHROWER.h"
#include "Subsystems\BALLINTAKE.h"

#include "Autonomous\AUTONOMOUS.h"
#include "Preferences.h"
#include "Preferences.h"
#include "SPIFFS.h"
#include "FS.h"
#include "BluetoothSerial.h"
#include "YUKON_MPU6050.h"


class ROBOT
{
  public:
    ROBOT(YETI_YUKON &rYukon);

    void Setup();
    void Loop();

    YETI_YUKON &Yukon;

    STATE State;

    //Motors
    YUKON_CytronMD10 DriveRight;
    YUKON_CytronMD10 DriveLeft;
    YUKON_CytronMD10 LiftMotor;
    YUKON_CytronMD10 ClawMotor;
    YUKON_CytronMD10 BuddyBotLift;
    YUKON_CytronMD10 BallThrowerMotor;
    YUKON_CytronMD10 BallIntakeMotor;

    //Subsystems
    DRIVE Drive;
    LIFT Lift;
    CLAW Claw;
    BUDDYBOT BuddyBot;
    BALLTHROWER BallThrower;
    BALLINTAKE BallIntake;
    AUTONOMOUS Auton;

    //USB Items
    USB Usb;
    Preferences preferences;
    XBOXRECV Xbox;
    BluetoothSerial BTserial;
    YUKON_MPU6050 mpu;
    
    //Variables for different modes
    bool PrecisionMode = false;
    bool IsArcadeMode = false;
    bool IsNoLimits = false;
    bool IsDebugMode = false;
    bool BTActive = true;
    bool EmergencyStop = false;
    bool ReadingAuton =false;
    bool CapMode = true;
    //Vars for speed checks
    float _NextSpeedUpdateMillis = 0;
    //Misc vars from stuff I added
    int LeftHasBeenLimited = -10;
    int RightHasBeenLimited = -10;
    int DebugModeOutput = 0;
    //Array Definitions
    volatile int16_t DriveRightSpeeds [750];
    volatile int16_t DriveLeftSpeeds [750];
    volatile int16_t LiftSpeeds [750];
    volatile int16_t ClawSpeeds [750];
    volatile int16_t BuddyBotSpeeds [750];
    //Speed Variable Definitions   
    int16_t PreviousLeftSpeed = 0;
    int16_t PreviousRightSpeed = 0;
    int16_t CurrentRightSpeed = 0;
    int16_t CurrentLeftSpeed = 0;
    int16_t LiftSpeed = 0;
    int16_t ClawSpeed = 0;
    int16_t BuddyLiftSpeed = 0;
    int16_t BallThrowerSpeed = 0;
    int16_t BallIntakeSpeed = 0;
    volatile int16_t AutonDriveRightSpeed = 0;
    volatile int16_t AutonDriveLeftSpeed = 0;
    volatile int16_t AutonLiftSpeed = 0;
    volatile int16_t AutonClawSpeed = 0;
    volatile int16_t AutonBuddyBotSpeed = 0;
    //Pointer Definitions
    //Auton Recording
    const char *basepath = "/spiffs";
    const char *rightarraypath ="/spiifs/AutonRecording/DriveRightSpeeds";
    int ArrayPos = 0;
    int ArrayProg = 0;
    bool Recording = false;
    bool FirstTry = true;
    bool RecordMode = false;
    long _NextAutonMillis = 0;

    void YukonDisplay(int cursorX, int cursorY, double text_size, String screentext)
    {
      Yukon.OLED.clearDisplay();
      Yukon.OLED.setCursor(cursorX, cursorY);
      Yukon.OLED.setTextSize(text_size);
      Yukon.OLED.print(screentext);
      Yukon.OLED.display();
    }
    //Sets Cursor position and text size to default
    void YukonDisplay(String screentext)
    {
      Yukon.OLED.clearDisplay();
      Yukon.OLED.setCursor(1, 1);
      Yukon.OLED.setTextSize(1);
      Yukon.OLED.print(screentext);
      Yukon.OLED.display();
    }
    /*
    //This will record an auton when the back and start buttons are pressed in sequence. 
    //Simply start driving to record.
        void StoreAuton()
        {   if(FirstTry = true) 
            {
            SPIFFS.begin(false, basepath, 5);
            SPIFFS.format();   
            FirstTry = false;
            }
                    //This puts the current speed in an array
                    DriveRightSpeeds [ArrayPos] = CurrentRightSpeed; 
                    DriveLeftSpeeds  [ArrayPos] = CurrentLeftSpeed;
                    LiftSpeeds       [ArrayPos] = LiftSpeed;
                    ClawSpeeds       [ArrayPos] = ClawSpeed;
                    BuddyBotSpeeds   [ArrayPos] = BuddyLiftSpeed;
                    ArrayPos++;
                    //This will store those lines.
                    SPIFFS.open("/spiffs/RightDrive", "a").println(DriveRightSpeeds[ArrayPos]);
                    SPIFFS.open("/spiffs/LeftDrive", "a").println(DriveLeftSpeeds[ArrayPos]);
                    SPIFFS.open("/spiffs/LiftSpeeds", "a").println(LiftSpeeds[ArrayPos]);
                    SPIFFS.open("/spiffs/ClawSpeeds", "a").println(ClawSpeeds[ArrayPos]);
                    SPIFFS.open("/spiffs/BuddyBotSpeeds", "a").println(BuddyBotSpeeds[ArrayPos]);
                    //This makes the values line up with the motor controller write speeds.
                    SPIFFS.open("/spiffs/RightDrive", "a").close();
                    SPIFFS.open("/spiffs/LeftDrive", "a").close();
                    SPIFFS.open("/spiffs/LiftSpeeds", "a").close();
                    SPIFFS.open("/spiffs/ClawSpeeds", "a").close();
                    SPIFFS.open("/spiffs/BuddyBotSpeeds", "a").close();

        }
        void AutonRead()
        { 
          ReadingAuton = true;
          SPIFFS.begin(false, basepath, 5);
          for (int i = 0; i < 750; i++)
          {
            SPIFFS.open("/spiffs/RightDrive", "r") >> DriveRightSpeeds[i];
            AutonDriveRightSpeed = DriveRightSpeeds[i];
            SPIFFS.open("/spiffs/LeftDrive", "r") >> DriveLeftSpeeds[i];
            AutonDriveLeftSpeed = DriveLeftSpeeds[i];
            SPIFFS.open("/spiffs/LiftSpeeds", "r") >> LiftSpeeds[i];
            AutonLiftSpeed = LiftSpeeds[i];
            SPIFFS.open("/spiffs/ClawSpeeds", "r") >> ClawSpeeds[i];
            AutonClawSpeed = ClawSpeeds[i];
            SPIFFS.open("/spiffs/BuddyBotSpeeds", "r") >> BuddyBotSpeeds[i]; 
            AutonBuddyBotSpeed = BuddyBotSpeeds[i];
            DriveRight.SetMotorSpeed(AutonDriveRightSpeed);
            DriveLeft.SetMotorSpeed(AutonDriveLeftSpeed);
            LiftMotor.SetMotorSpeed(AutonLiftSpeed);
            ClawMotor.SetMotorSpeed(AutonClawSpeed);
            BuddyBotLift.SetMotorSpeed(AutonBuddyBotSpeed);
            
          } 
          ReadingAuton = false;
          SPIFFS.end();
        }*/
        void ToggleBt()
        {
          BTActive = !BTActive;
          if(!BTActive)
          {
            BTserial.end();
          }
          if(BTActive)
          {
            BTserial.begin("C3604R");
          }
        }
    
   

    //PIN Declarations
    static const int _DriveRightPWM = 0;
    static const int _DriveRightDir = 17; //14;
    static const bool _DriveRightReversed = true;
        
    static const int _DriveLeftPWM = 1;
    static const int _DriveLeftDir = 14;//17;
    static const bool _DriveLeftReversed = false;
        
    static const int _LiftMotorPWM = 4;//2;
    static const int _LiftMotorDir = 26;//22;
    static const bool _LiftMotorReversed = false;
        
    static const int _ClawMotorPWM = 3;
    static const int _ClawMotorDir = 21;
    static const bool _ClawMotorReversed = false;
        
    static const int _BuddyBotLiftPWM = 3;//4;
    static const int _BuddyBotLiftDir = 22;//26;
    static const bool _BuddyBotLiftReversed = false;

    static const int _BallThrowerPWM = 0;
    static const int _BallThrowerDir = 0;
    static const bool _BallThrowerReversed = false;

    static const int _BallIntakePWM = 0;
    static const int _BallIntakeDir = 0;
    static const bool _BallIntakeReversed = false;

        

    static const uint8_t _Button0 = 0;
    static const uint8_t _LEDBuiltIn = 25;
    static const uint8_t _AutonLightSensor = 1;

    static const uint16_t _AutonLightSensorThreshold = 3000; //Value 0 - 4095

  private:
      long _NextDisplayMillis = 0;
      long _NextMotorControllerWriteMillis = 0;
      long _NextGetPrevSpeed = 0;
};
#endif