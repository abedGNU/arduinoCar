
#include <Arduino.h>

#include <Encoder.h>

//#define Debug

Encoder::Encoder(int intPinA, int pin_b, bool inv_dir)
{
	pinA = intPinA; // interrupt pin
	pinB = pin_b;
	invDir = inv_dir;
}

void Encoder::init()
{
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);
	// how to call the intterutp from the class
	int interNo = digitalPinToInterrupt(pinA);
	//attachInterrupt(interNo, count ,RISING);
}

void Encoder::count()
{
	bool encB = digitalRead(pinB); // read the input pin
	if (invDir)
	{
		counter -= encB ? -1 : +1;
	}
	else
	{
		counter += encB ? -1 : +1;
	}
}

long Encoder::getCounter()
{
	return counter;
}

void Encoder::resetCounter()
{
	counter =0;
	#ifdef Debug
		Serial.print("reset counter ");
		Serial.println(counter);
	#endif
}