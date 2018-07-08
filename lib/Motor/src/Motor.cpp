
#include <Arduino.h>
#include <Motor.h>
//#define Debug

Motor::Motor(int pinA, int pinB, int pin_PWM, bool inv_Dir, int encA, int encB)
{
	enA = pinA;
	enB = pinB;
	pinPwm = pin_PWM;
	invDir = inv_Dir;

	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);

	enc = new Encoder(encA, encB);
}

void Motor::setLoadSpeed(double speed)
{
	setDirection(speed);
	int pwmValue;
	#ifdef Debug
		Serial.print("speed ");
		Serial.println(speed);
	#endif
	pwmValue = map(abs(speed) * gearRatio, 0, 15000, 0, 255);
	analogWrite(pinPwm, pwmValue);
	#ifdef Debug
		Serial.print("pwm value ");
		Serial.print(pwmValue);
		Serial.print(" , on pin ");
		Serial.println(pinPwm);
		Serial.println("+++++++++++++++++++");
	#endif
}

void Motor::setDirection(double speed)
{
	if ((speed > 0 & invDir == false) | (speed < 0 & invDir))
	{
		#ifdef Debug
			Serial.println("FW");
		#endif
		digitalWrite(enA, HIGH);
		digitalWrite(enB, LOW);
	}
	else if ((speed < 0 & invDir == false) | (speed > 0 & invDir))
	{
		#ifdef Debug
			Serial.println("Bck");
		#endif
		digitalWrite(enA, LOW);
		digitalWrite(enB, HIGH);
	}
}

void Motor::stop()
{
	#ifdef Debug
		Serial.println("Stop");
	#endif
	setLoadSpeed(0);
	digitalWrite(enA, HIGH);
	digitalWrite(enB, HIGH);
}

double Motor::getLoadAngle()
{
	return (double)(enc->getCounter() * 360.0) / (double)pulsePerLoadRound ;
}
