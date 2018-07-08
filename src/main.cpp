#include <Arduino.h>
#include <Motor.h>
#include <TimerOne.h>

Motor MotorLeft(5, 6, 7, true, 2, 24);
int state = 0, prevState = 0, prevRunState;

double speed = 100;
unsigned long begintime = 0;       // time in millisecond [ms]
unsigned long duration = 5000;     // time in millisecond [ms]
unsigned long durationStop = 4000; // time in millisecond [ms]

unsigned long time0;
double angle0;
double currentSpeed;

bool firstCycle = false;
double oldAngle = 0.0;

int samplingTime = 5000; // micros

void calculateSpeed();

void countEncoderLeft()
{

  MotorLeft.enc->count();
  /*
  //currentSpeed=(60.0*1000.0/360.0)*(MotorLeft.getLoadAngle() - angle0)/(double)(millis()-time0);
  currentSpeed=(pow(10,6)*60.0/360.0)*(MotorLeft.getLoadAngle() - angle0)/(double)(micros()-time0);

  Serial.println(currentSpeed);
  //Serial.println((micros()-time0)); 
  angle0 =  MotorLeft.getLoadAngle();
  time0= micros();
  */

  // Serial.println(micros() - time0);
  // time0 = micros();
}

void setup()
{
  Serial.begin(115200);
  MotorLeft.gearRatio = 30.0;
  MotorLeft.maxSpeed = 15000; // speed wheel 1500/30 = 500rpm

  attachInterrupt(digitalPinToInterrupt(2), countEncoderLeft, RISING);
  Timer1.initialize(samplingTime);
  Timer1.attachInterrupt(calculateSpeed);
}

void loop()
{

  switch (state)
  {
  // Stop
  case 1:
    if (!firstCycle)
    {
      begintime = millis();
      firstCycle = true;
      Serial.print("Stop ");
    }
    MotorLeft.stop();
    MotorLeft.enc->resetCounter();
    if ((millis() - begintime) >= durationStop)
    {
      Serial.println(millis() - begintime);
      firstCycle = false;
      prevState = state;
      state = 2;
    }
    break;
  // Forward
  case 2:
    if (!firstCycle)
    {
      begintime = millis();
      firstCycle = true;
      Serial.print("Run ");
    }
    MotorLeft.setLoadSpeed(speed);
    if ((millis() - begintime) >= duration)
    {
      Serial.println(millis() - begintime);
      firstCycle = false;
      prevState = state;
      state = 1; // stop
      speed = -speed;
    }
    break;
    // default
  default:
    state = 1;
    prevState = 1;
    break;
  }
  //Serial.println(millis());
}

void calculateSpeed()
{
  double angle =  MotorLeft.getLoadAngle();
  double timeMin = (double)samplingTime*pow(10,-6)/60.0;
  currentSpeed = (angle - oldAngle) / (timeMin * 360.0);

  oldAngle = angle;

  Serial.println(currentSpeed);
}
