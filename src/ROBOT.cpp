 #include "ROBOT.h"
ROBOT::ROBOT(YETI_YUKON &rYukon) : Yukon(rYukon),
    DriveRight(_DriveRightPWM, &Yukon.PWM, _DriveRightDir, _DriveRightReversed), 
    DriveLeft(_DriveLeftPWM, &Yukon.PWM, _DriveLeftDir, _DriveLeftReversed), 
    LiftMotor(_LiftMotorPWM, &Yukon.PWM, _LiftMotorDir, _LiftMotorReversed), 
    ClawMotor(_ClawMotorPWM, &Yukon.PWM, _ClawMotorDir, _ClawMotorReversed), 
    BuddyBotLift(_BuddyBotLiftPWM, &Yukon.PWM, _BuddyBotLiftDir, _BuddyBotLiftReversed),
    BallThrowerMotor(_BallThrowerPWM, &Yukon.PWM, _BallThrowerDir, _BallThrowerReversed), 
    BallIntakeMotor(_BallIntakePWM, &Yukon.PWM, _BallIntakeDir, _BallIntakeReversed),
    Drive(*this),
    Lift(*this),
    Claw(*this),
    BuddyBot(*this),
    BallThrower(*this),
    BallIntake(*this),
    Auton(*this),
    Xbox(&Usb)
    

{
}

void ROBOT::Setup()
{
    Usb.Init();
    DriveRight.Init();
    DriveLeft.Init();
    LiftMotor.Init();
    ClawMotor.Init();
    BuddyBotLift.Init();
    BallThrowerMotor.Init();
    BTserial.begin("C3604R");
    pinMode(_Button0, INPUT_PULLUP);
    pinMode(_LEDBuiltIn, OUTPUT);
    digitalWrite(_LEDBuiltIn, LOW);
}

void ROBOT::Loop()
{
     //Read The Controller
    Usb.Task();
    
        if (Xbox.XboxReceiverConnected)
        {
        for (uint8_t i = 0; i < 4; i++)
        {
        if (Xbox.Xbox360Connected[i])
        {
        CurrentRightSpeed  = (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
        CurrentLeftSpeed = (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(RightHatY, i), 7500));
        if(CapMode == true)
        {
         LiftSpeed = (Xbox.getButtonPress(R2, i) - Xbox.getButtonPress(L2, i));
         ClawSpeed = (Xbox.getButtonPress(A))*255;
         BuddyLiftSpeed = ((Xbox.getButtonPress(R1, i)*255) - (Xbox.getButtonPress(L1, i)*255));
        }
        if(!CapMode)
        {
         BallThrowerSpeed = ((Xbox.getButtonPress(R1, i)*255) - (Xbox.getButtonPress(L1, i)*255));
         BallIntakeSpeed = (Xbox.getButtonPress(R2, i) - Xbox.getButtonPress(L2, i));
         
        }
        //This will get and store the previous speed
       if (_NextGetPrevSpeed < millis())
        {
        _NextGetPrevSpeed = millis() + 30;
        CurrentLeftSpeed = PreviousLeftSpeed;
        CurrentRightSpeed = PreviousRightSpeed;
        }

        //This changes the drive mode from 2 joysticks to 1
        if(IsArcadeMode)
        {
            CurrentRightSpeed =  (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatX, i), 7500)) + (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
            CurrentLeftSpeed =   (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500)) -  (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatX, i), 7500));
        }
        //This cuts all drive inputs by half for more precise movement
        if(PrecisionMode)
        {
            CurrentLeftSpeed = CurrentLeftSpeed * .5;
            CurrentRightSpeed = CurrentRightSpeed  * .5;
        }
        //This will put the serial monitor straight into the bluetooth serial monitor 
        if (Serial.available()) 
        {
        BTserial.write(Serial.read());
        }
        //Press L3 button to engage Debug Mode. 
        //Press R3 to toggle the output to the display. 
        if(IsDebugMode)
        {
            
            if (DebugModeOutput == 0)
            Yukon.OLED.clearDisplay();

            if (DebugModeOutput == 1)
            { Yukon.OLED.print("Current Right Speed");
             Yukon.OLED.println (CurrentRightSpeed);}
           
           if (DebugModeOutput == 2)
           {Yukon.OLED.print("Current Left Speed");
            Yukon.OLED.println(CurrentLeftSpeed);}

            if (DebugModeOutput == 3)
            {Yukon.OLED.print("Previous Right Speed");
            Yukon.OLED.println (PreviousRightSpeed);}

            if (DebugModeOutput == 4)
            {Yukon.OLED.print("Previous Left Speed");
            Yukon.OLED.println(PreviousLeftSpeed);}

            if (DebugModeOutput == 5)
            {Yukon.OLED.print ("Light Sensor Threshold");
             Yukon.OLED.println (_AutonLightSensorThreshold);}

            if (DebugModeOutput == 7)
            {
                DebugModeOutput = 0;
            }
        }

        Drive.OISetSpeed(CurrentRightSpeed, CurrentLeftSpeed);
        Lift.OISetSpeed(LiftSpeed*0.5);
        Claw.OISetSpeed(ClawSpeed);
        BuddyBot.OISetSpeed(BuddyLiftSpeed);
        BallThrower.OISetSpeed(BallThrowerSpeed);

        //Controller Mapping
        //Be sure to note the diiference between buttonclick and buttonpress!!!
        if (Xbox.getButtonClick(LEFT))
        Auton.QueuePrev();
        
        if (Xbox.getButtonClick(RIGHT))
        Auton.QueueNext();

        if (Xbox.getButtonClick(DOWN))
        Auton.ToggleArmed();
        
        if (Xbox.getButtonClick(R3))
        EmergencyStop = !EmergencyStop;

        if (Xbox.getButtonClick(Y))
        PrecisionMode = !PrecisionMode;

        if (Xbox.getButtonClick(X))
        Auton.LaunchQueued();

        if (Xbox.getButtonClick(B))
        IsArcadeMode = !IsArcadeMode;
        
        if (Xbox.getButtonClick(BACK))
        ToggleBt();

        if (Xbox.getButtonClick(START))
        CapMode = !CapMode;
        
        if (Xbox.getButtonClick(L3))
        BuddyBot.ForAsync(1600, -255);

        if (Xbox.getButtonClick(XBOX)) 
        Auton.ToggleLockArmed();
        }
        }
        }

        if(digitalRead(_Button0) == LOW)
        {
            digitalWrite(_LEDBuiltIn, HIGH);
            Yukon.SetupWIFI();
            delay(1000);
        }

    //Read The Sensors 
    uint16_t LightSensorVal = analogRead(33);
    State.AutonLightSensorActive = (LightSensorVal <= _AutonLightSensorThreshold);
    //BTserial.println(LightSensorVal);
    //BTserial.println(mpu.Heading());
    Serial.println(LightSensorVal); 

    //Write To Motor Controllers
    if (_NextMotorControllerWriteMillis < millis() && !EmergencyStop)
    {
    //It will not write to the motor controllers more than once every 20 milliseconds
    _NextMotorControllerWriteMillis = millis() + 20; 
    DriveRight.SetMotorSpeed(State.DriveRightSpeed);
    DriveLeft.SetMotorSpeed(State.DriveLeftSpeed);
    LiftMotor.SetMotorSpeed(State.LiftMotorSpeed);
    ClawMotor.SetMotorSpeed(State.ClawMotorSpeed);
    BuddyBotLift.SetMotorSpeed(State.BuddyBotLiftSpeed); 
    BallThrowerMotor.SetMotorSpeed(State.BallThrowerMotorSpeed);
    BallIntakeMotor.SetMotorSpeed(State.BallIntakeMotorSpeed);
    }
    if(Recording)
    {
        if(FirstTry == true) 
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

    //Write the Display
    if (_NextDisplayMillis < millis())
    {
        _NextDisplayMillis = millis() + 250;

        if(Auton.IsArmLocked())
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.println("LOCKED! ");
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print(Auton.QueuedProgramName());
            Yukon.OLED.display();
        }
        else if (Auton.IsArmed())
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.print("ARMED ");
            Yukon.OLED.println(LightSensorVal);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print(Auton.QueuedProgramName());

            Yukon.OLED.display();
        }
        else if(Auton.QueuedProgramName() != "")
        {   
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.print(Auton.QueuedProgramName());
            Yukon.OLED.display();
        }
        else if (RecordMode)
        {
            YukonDisplay(0, 0, 1, "Record Mode Armed!");
        }
        
        else if (Recording)
        {
            YukonDisplay(0, 0, 1, "Recording Auton!");
        }
        else if(PrecisionMode)
        {
            YukonDisplay(0, 0, 1, "Precision Mode!");
        }
        
        else if(IsArcadeMode)
        {
            YukonDisplay(0, 0, 1, "Arcade Mode!");
        }
    
        else
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.println("NC Robotics!");
            Yukon.OLED.println("C3604R");
            Yukon.OLED.display();
        }
    }
}

