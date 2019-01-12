#include "ROBOT.h"

ROBOT::ROBOT(YETI_YUKON &rYukon) : Yukon(rYukon),
     DriveRight(_DriveRightPWM, &Yukon.PWM, _DriveRightDir, _DriveRightReversed), 
     DriveLeft(_DriveLeftPWM, &Yukon.PWM, _DriveLeftDir, _DriveLeftReversed), 
     LiftMotor(_LiftMotorPWM, &Yukon.PWM, _LiftMotorDir, _LiftMotorReversed), 
     ClawMotor(_ClawMotorPWM, &Yukon.PWM, _ClawMotorDir, _ClawMotorReversed), 
     BuddyBotLift(_BuddyBotLiftPWM, &Yukon.PWM, _BuddyBotLiftDir, _BuddyBotLiftReversed), 
    Drive(*this),
    Lift(*this),
    Claw(*this),
    BuddyBot(*this),
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

    pinMode(_Button0, INPUT_PULLUP);
    pinMode(_LEDBuiltIn, OUTPUT);
    digitalWrite(_LEDBuiltIn, LOW);
}
bool PrecisionMode = false;
bool IsArcadeMode = false;
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
        int16_t LeftSpeed =  (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
        int16_t RightSpeed = (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(RightHatY, i), 7500));
        if(IsArcadeMode)
        {
            LeftSpeed = (Xbox.getAnalogHat(LeftHatY, i), 7500) - (Xbox.getAnalogHat(LeftHatX, i), 7500);
            RightSpeed = (Xbox.getAnalogHat(LeftHatY, i), 7500) + (Xbox.getAnalogHat(LeftHatX, i), 7500);
        }
        
        if(PrecisionMode)
        {
            LeftSpeed = LeftSpeed * .5;
            RightSpeed = RightSpeed  * .5;
        }



        Drive.OISetSpeed(RightSpeed, LeftSpeed);
        
        //To switch to arcade mode, remove the slash marks from line 48 and add the in the front of line 46
        // Drive.OISetSpeed(Xbox.getAnalogHat(LeftHatX, i), 7500),Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500)+Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatX, i), 7500));
        Lift.OISetSpeed(Xbox.getButtonPress(R2, i) - Xbox.getButtonPress(L2, i));
        Claw.OISetSpeed(Xbox.getButtonPress(A));
        BuddyBot.OISetSpeed((Xbox.getButtonPress(R1, i)*255) - (Xbox.getButtonPress(L1, i)*255));
    
        if (Xbox.getButtonClick(LEFT))
        Auton.QueuePrev();
        if (Xbox.getButtonClick(RIGHT))
        Auton.QueueNext();
        if (Xbox.getButtonClick(DOWN))
        Auton.ToggleArmed();
        if (Xbox.getButtonClick(Y))
        PrecisionMode = !PrecisionMode;

        if (Xbox.getButtonClick(X))
        Auton.LaunchQueued();

        if (Xbox.getButtonClick(B))
        IsArcadeMode = !IsArcadeMode;
        

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
    //Serial.println(LightSensorVal); 
    State.AutonLightSensorActive = (LightSensorVal <= _AutonLightSensorThreshold);

    uint16_t EncoderRevolutions = analogRead(32);
    Serial.println(EncoderRevolutions);

    //Write To Motor Controllers
    if (_NextMotorControllerWriteMillis < millis())
    {
        _NextMotorControllerWriteMillis = millis() + 20; 
    DriveRight.SetMotorSpeed(State.DriveRightSpeed);
    DriveLeft.SetMotorSpeed(State.DriveLeftSpeed);
    LiftMotor.SetMotorSpeed(State.LiftMotorSpeed);
    ClawMotor.SetMotorSpeed(State.ClawMotorSpeed);
    BuddyBotLift.SetMotorSpeed(State.BuddyBotLiftSpeed);
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
        else if(PrecisionMode)
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.print("Precsion Mode");
            Yukon.OLED.display();
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
