/*
*
*  The output of the SBUS receiver goes into one of the inputs on an inverter (74HC14).
*  The output from that input goes into the serial port.
*  The output of the serial port you are using goes into the inverter and the output will drive SBUS servos.
*  You must have a common ground to all the devices. It is best to run the servos from a different power supply than the arduino.
*
*  http://forum.arduino.cc/index.php?PHPSESSID=eoc1g2c2rf7lq1jl5legq7fij0&topic=99708.15
*/

#include <FUTABA_SBUS.h>
#include <Streaming.h>

#define SERVO_LOW 500
#define SERVO_MID 1000
#define SERVO_HIGH 1500

#define FLIPPER_ENABLE 10
#define FLIPPER_DIRECTION 9

#define FLOWER_FAN 8
#define FLOWER_DISPENSER 7

#define CANNON 6


FUTABA_SBUS sBus;


//define "port" in FUTABA_SBUS.h refers to which serial port we are using to read the SBUS signal

void setup()
{
  sBus.begin();            //setup serial port, intialize arrays and variables
  sBus.mSbusPassthrough = true;  //enabled by default, disable to send own data using UpdateServos() instead
 // Serial.begin(115200);

  //pinMode(CH5_DOWN, OUTPUT);
  //pinMode(CH5_UP, OUTPUT);
  pinMode(FLIPPER_DIRECTION, OUTPUT);
  pinMode(FLIPPER_ENABLE, OUTPUT);
  pinMode(FLOWER_FAN, OUTPUT);
  pinMode(FLOWER_DISPENSER, OUTPUT);
  pinMode(CANNON, OUTPUT);

  //digitalWrite(CH5_DOWN, 0);
  //digitalWrite(CH5_UP, 0);
  digitalWrite(FLIPPER_DIRECTION, 1);
  digitalWrite(FLIPPER_ENABLE, 1);
  digitalWrite(FLOWER_FAN, 1);
  digitalWrite(FLOWER_DISPENSER, 1);
  digitalWrite(CANNON, 1);
}

void loop()
{
  sBus.FeedLine();            //check for a full packet (>24bytes) available to read from port's rx buffer - if there, read it in, validate and store packet
                              //if not enough bytes waiting, do nothing right now

  if (sBus.mToChannels == 1)   //mToChannels = 1 indicates a new packet was received and stored in sBus.sbusData[]
  {
    sBus.UpdateServos();      //echo sBus data back out on port's tx line
    sBus.UpdateChannels();    //process data in sBus.sbusData[] and update sBus.mChannels[]
    sBus.mToChannels = 0;

    /*
    *  Now we can use the data in sBus.mChannels[]
    *
    */

    /*
        //Set outputs for Channel 5
    if(sBus.mChannels[4] < SERVO_LOW)
    {
      digitalWrite(CH5_DOWN, 0);
      digitalWrite(CH5_UP, 1);
    }
    else if(sBus.mChannels[4] > SERVO_HIGH)
    {
      digitalWrite(CH5_DOWN, 1);
      digitalWrite(CH5_UP, 0);
    }
    else
    {
      digitalWrite(CH5_DOWN, 1);
      digitalWrite(CH5_UP, 1);
    }
    */

    if(sBus.Channel(5) > SERVO_HIGH)
    {
      digitalWrite(FLOWER_FAN, 0);
      digitalWrite(FLOWER_DISPENSER, 0);
    }
    else
    {
      digitalWrite(FLOWER_FAN, 1);
      digitalWrite(FLOWER_DISPENSER, 1);
    }


    //Set outputs for Channel 6
    if(sBus.Channel(6) < SERVO_LOW)
    {
      digitalWrite(FLIPPER_DIRECTION, 1);
      digitalWrite(FLIPPER_ENABLE, 0);
    }
    else if(sBus.Channel(6) > SERVO_HIGH)
    {
      digitalWrite(FLIPPER_DIRECTION, 0);
      digitalWrite(FLIPPER_ENABLE, 0);
    }
    else
    {
      digitalWrite(FLIPPER_DIRECTION, 1);
      digitalWrite(FLIPPER_ENABLE, 1);
    }


    //Set output for Channel 7
    if(sBus.Channel(7) > SERVO_MID)
    {
      digitalWrite(CANNON, 0);
    }
    else
    {
      digitalWrite(CANNON, 1);
    }

  }
}
